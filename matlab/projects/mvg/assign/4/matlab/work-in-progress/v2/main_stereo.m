clear all; pause(0.5); clc; 

im1 = imread('left.jpg');
im2 = imread('right.jpg');

im1 = uint8(rgb2gray(im1));
im2 = uint8(rgb2gray(im2));

% load intrinsic matrix.
load('cameraCalibrator.mat')
K = cameraParams.IntrinsicMatrix';

figure(1); clf; pause(0.1);
imshow(im1); pause(0.1);
hold on;

figure(2); clf; pause(0.1);
imshow(im2); pause(0.1);
hold on;

% extract surf features.
blobs1 = detectSURFFeatures(im1, 'MetricThreshold', 2000);
blobs2 = detectSURFFeatures(im2, 'MetricThreshold', 2000);
[features1, validBlobs1] = extractFeatures(im1, blobs1);
[features2, validBlobs2] = extractFeatures(im2, blobs2);
indexPairs = matchFeatures(features1, features2, 'Metric', 'SAD', 'MatchThreshold', 5);
surf1 = validBlobs1(indexPairs(:,1),:);
surf2 = validBlobs2(indexPairs(:,2),:);
x1 = surf1.Location;
x2 = surf2.Location;

% x1=[
%     244,56;
%     167,492;
%     740,431;
%     583,41;
%     545,63;
%     535,75;
%     554,87;
%     567,72;
%     422,106;
%     423,113;
%     530,108;
%     529,101;
%     370,54;
%     388,177;
%     480,175;
%     497,274;
%     465,279;
%     460,248;
%     363,363;
%     364,474;
%     ];
% x2=[
%     330,53;
%     122,438;
%     674,482;
%     657,75;
%     612,91;
%     593,102;
%     611,114;
%     629,103;
%     476,118;
%     474,126;
%     580,134;
%     581,127
%     444,64;
%     418,184;
%     507,194;
%     490,289;
%     457,291;
%     463,260;
%     330,355;
%     294,455;
%     ];
% x1 = x1.*4;
% x2 = x2.*4;

n = size(x1, 1);
bestInNum = 0;
bestIdx = [];

ransac_thr = 1;
ransac_iter = 1000;
for i = 1:ransac_iter
	% We need 8 points to calculate fundamental matrix.
	idx = randperm(n, 8);    % 8x1
	x1_sampled = x1(idx, :); % 8x2
	x2_sampled = x2(idx, :); % 8x2
    x1_sampled = transpose([x1_sampled, ones(8, 1)])'; % 8x3
    x2_sampled = transpose([x2_sampled, ones(8, 1)])'; % 8x3

	% Compute fundamental matrix using the four sampled points
    F = calculate_fundamental_matrix(x1_sampled', x2_sampled');

	% Calculate inliers
	diff = setdiff(1:n, idx);
	x1_unsampled = x1(diff, :); % (n-8)x2
	x2_unsampled = x2(diff, :); % (n-8)x2

	x1_unsampled_padded = [x1_unsampled ones(n-8, 1)]; % (n-8)x3
	x2_unsampled_padded = [x2_unsampled ones(n-8, 1)]; % (n-8)x3

	Lu = transpose(F * transpose(x1_unsampled_padded)); % Dim.: (n-8)x3

	distance = abs(sum(Lu .* x2_unsampled_padded, 2)) ./ sqrt(sum(Lu(:, 1:2) .* Lu(:, 1:2), 2));

	inlierIdx = find(distance <= ransac_thr);
	inlierNum = length(inlierIdx);

	% Update best sample points
	if inlierNum >= bestInNum
		bestInNum = inlierNum;
		bestIdx = idx;
	end
end

x1_best = x1(bestIdx, :); % 8x2
x2_best = x2(bestIdx, :); % 8x2
x1_best = transpose([x1_best, ones(8, 1)])'; % 8x3
x2_best = transpose([x2_best, ones(8, 1)])'; % 8x3
F = calculate_fundamental_matrix(x1_best', x2_best');

% [F, epi_inliers, ~] = estimateFundamentalMatrix(...
%     x1, x2, 'Method', 'RANSAC', 'NumTrials', 10000, 'DistanceThreshold', 0.1, 'Confidence', 99.99);

% visualize epipolar lines.
n = size(x1_best, 1);
colors = ['r', 'g', 'b', 'c', 'y', 'm', 'k', 'w'];
for iIter = 1:n
	color = colors(mod(iIter, 8)+1);
	figure(1);
	p1 = plot(x1_best(iIter, 1), x1_best(iIter, 2));
	set(p1, 'LineStyle', 'None', 'color', color,...
		'Marker', 'o', 'MarkerFaceColor', color);

	Lv = transpose(F' * transpose([x2_best(iIter, :)]));
	a = Lv(:, 1); 
	b = Lv(:, 2); 
	c = Lv(:, 3);

	x = 1:4032; 
	y = round((- a * x - c)/b);
	plot(x, y, 'color', color, 'LineWidth', 1.5);

	%         epiLines = epipolarLine(F',x2);
	%         %Compute the intersection points of the lines and the image border.
	%         points = lineToBorderPoints(epiLines,[2268,4032]);
	%         %Show the epipolar lines in the first image
	%         line(points(:,[1,3])',points(:,[2,4])');


	figure(2);
	p2 = plot(x2_best(iIter, 1), x2_best(iIter, 2));
	set(p2, 'LineStyle', 'None', 'color', color,...
		'Marker', 'o', 'MarkerFaceColor', color);

	Lu = transpose(F * transpose([x1_best(iIter, :)]));
	a = Lu(:, 1); 
	b = Lu(:, 2); 
	c = Lu(:, 3);

	x = 1:4032; 
	y = round((- a * x - c)/b);
	plot(x, y, 'color', color, 'LineWidth', 1.5);

	%         epiLines2 = epipolarLine(F,x1);
	%         %Compute the intersection points of the lines and the image border.
	%         points2 = lineToBorderPoints(epiLines2,[2268,4032]);
	%         %Show the epipolar lines in the first image
	%         line(points2(:,[1,3])',points2(:,[2,4])');
end

% Compute four configurations of camera pose given F
E = K'*F*K;

[Ue, ~, Ve] = svd(E);

W = [0 -1 0;
	1 0 0;
	0 0 1];

t1 = Ue(:,3);
R1 = Ue * W * Ve';
if det(R1) < 0
	t1 = -t1;  R1 = -R1;
end
C1 = -R1'*t1;

t2 = -Ue(:,3);
R2 = Ue * W * Ve';
if det(R2) < 0
	t2 = -t2;  R2 = -R2;
end
C2 = -R2'*t2;

t3 = Ue(:,3);
R3 = Ue * W' * Ve';
if det(R3) < 0
	t3 = -t3;  R3 = -R3;
end
C3 = -R3'*t3;

t4 = -Ue(:,3);
R4 = Ue * W' * Ve';
if det(R4) < 0
	t4 = -t4;  R4 = -R4;
end
C4 = -R4'*t4;

P1 = K*[eye(3) zeros(3,1)];

P2 = K*R1*[eye(3) -C1];
X1 = Triangulation(P1, P2, x1, x2);

P2 = K*R2*[eye(3) -C2];
X2 = Triangulation(P1, P2, x1, x2);

P2 = K*R3*[eye(3) -C3];
X3 = Triangulation(P1, P2, x1, x2);

P2 = K*R4*[eye(3) -C4];
X4 = Triangulation(P1, P2, x1, x2);

%%
% Disambiguate camera pose
RMatrix = {R1 R2 R3 R4};
CMatrix = {C1 C2 C3 C4};
XMatrix = {X1 X2 X3 X4};
nValids = zeros(4, 1);

for iIter = 1:4
	R = RMatrix{iIter};
	X = XMatrix{iIter};
	C = CMatrix{iIter};
	nValids(iIter) = sum(R(3, :) * (X - C')' > 0 & X(:, 3)' > 0);
end

[~, maxIdx] = max(nValids);
R = RMatrix{maxIdx};
C = CMatrix{maxIdx};
X = XMatrix{maxIdx};

% Stereo rectification
    rx = C / norm(C);
    rz_tilde = [0; 0; 1];
    rz = (rz_tilde - dot(rz_tilde, rx) .* rx) ...
        / norm(rz_tilde - dot(rz_tilde, rx) .* rx);
    ry = cross(rz, rx);
    R_rect = [rx'; ry'; rz'];
    H1 = K * R_rect * inv(K);
    H2 = K * R_rect * R' * inv(K);
    
im1_w = WarpImage(im1, H1);
im2_w = WarpImage(im2, H2);

% [t1, t2] = estimateUncalibratedRectification(F, x1(epi_inliers,:), x2(epi_inliers,:), size(im2));
% tform1 = projective2d(t1);
% tform2 = projective2d(t2);
% [im1_w2, im2_w2] = rectifyStereoImages(im1, im2, tform1, tform2);

% [R_,t_] = relativeCameraPose(F,cameraParams, x1_best, x2_best);
% [H3, H4] = ComputeRectification(K, R_r, t_');
% im1_w3 = WarpImage(im1, H3);
% im2_w3 = WarpImage(im2, H4);

subplot(3,2,1);
% figure(3);  clf; pause(0.1);
imshow(im1_w);  pause(0.1);

subplot(3,2,2);
% figure(4); clf; pause(0.1);
imshow(im2_w);  pause(0.1);

% subplot(3,2,3);
% % figure(5); clf; pause(0.1);
% imshow(im1_w2);  pause(0.1);
% 
% subplot(3,2,4);
% % figure(6); clf; pause(0.1);
% imshow(im2_w2);  pause(0.1);

% subplot(3,2,5);
% % figure(5); clf; pause(0.1);
% imshow(im1_w3);  pause(0.1);
% 
% subplot(3,2,6);
% % figure(6); clf; pause(0.1);
% imshow(im2_w3);  pause(0.1);

%file_name = 'stereo.mat';
%save(file_name, 'x1', 'x2', 'F', 'X', 'H1', 'H2', 'im1_w', 'im2_w', 'disparity');
clear all; pause(0.5); clc; 

im1 = imread('left.jpg');
im2 = imread('right.jpg');

im1 = uint8(rgb2gray(im1));
im2 = uint8(rgb2gray(im2));

[height width] = size(im1);

% load intrinsic matrix.
load('cameraCalibrator.mat')
K = cameraParams.IntrinsicMatrix';

% extract surf features.
blobs1 = detectSURFFeatures(im1, 'MetricThreshold', 2000);
blobs2 = detectSURFFeatures(im2, 'MetricThreshold', 2000);
[features1, valid_blobs1] = extractFeatures(im1, blobs1);
[features2, valid_blobs2] = extractFeatures(im2, blobs2);
index_pairs = matchFeatures(features1, features2, 'Metric', 'SAD', 'MatchThreshold', 5);
surf1 = valid_blobs1(index_pairs(:,1),:);
surf2 = valid_blobs2(index_pairs(:,2),:);
x1 = surf1.Location;
x2 = surf2.Location;

n = size(x1, 1);
best_inlier = 0;
best_idx = [];

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
	inlier_ = find(distance <= ransac_thr);
	inlier = length(inlier_);

	% Update best sample points
	if inlier >= best_inlier
		best_inlier = inlier;
		best_idx = idx;
	end
end

x1_best = x1(best_idx, :);                   % 8x2
x2_best = x2(best_idx, :);                   % 8x2
x1_best = transpose([x1_best, ones(8, 1)])'; % 8x3
x2_best = transpose([x2_best, ones(8, 1)])'; % 8x3
F = calculate_fundamental_matrix(x1_best', x2_best');

% visualize epipolar lines in left image.
figure(1);
imshow(im1);
figure(1);
epipolar_lines = epipolarLine(F',x2);
points = lineToBorderPoints(epipolar_lines,[height,width]);
line(points(:,[1,3])',points(:,[2,4])');

% visualize epipolar lines in right image.
figure(2);
imshow(im2);
figure(2);
epipolar_lines2 = epipolarLine(F,x1);
points2 = lineToBorderPoints(epipolar_lines2,[height,width]);
line(points2(:,[1,3])',points2(:,[2,4])');

% extract four solutions from the essential matrix.
E = K'*F*K;
[U, ~, V] = svd(E);

W = [0 -1 0;
	1 0 0;
	0 0 1];

t1 = U(:,3);
R1 = U * W * V';
if det(R1) < 0
	t1 = -t1;  R1 = -R1;
end
C1 = -R1'*t1;

t2 = -U(:,3);
R2 = U * W * V';
if det(R2) < 0
	t2 = -t2;  R2 = -R2;
end
C2 = -R2'*t2;

t3 = U(:,3);
R3 = U * W' * V';
if det(R3) < 0
	t3 = -t3;  R3 = -R3;
end
C3 = -R3'*t3;

t4 = -U(:,3);
R4 = U * W' * V';
if det(R4) < 0
	t4 = -t4;  R4 = -R4;
end
C4 = -R4'*t4;

% extract four possible 3d points X1,X2,X3,X4.
P1 = K*[eye(3) zeros(3,1)];

P2 = K*R1*[eye(3) -C1]; 
X1 = triangulate(P1, P2, x1, x2);

P2 = K*R2*[eye(3) -C2];
X2 = triangulate(P1, P2, x1, x2);

P2 = K*R3*[eye(3) -C3];
X3 = triangulate(P1, P2, x1, x2);

P2 = K*R4*[eye(3) -C4];
X4 = triangulate(P1, P2, x1, x2);

Rvec = {R1 R2 R3 R4};
Cvec = {C1 C2 C3 C4};
Xvec = {X1 X2 X3 X4};
num_valid = zeros(4, 1);

for i = 1:4
	R = Rvec{i};
	X = Xvec{i};
	C = Cvec{i};
	num_valid(i) = sum(R(3, :) * (X - C')' > 0 & X(:, 3)' > 0);
end

% extract only one solution R,C.
[~, max_idx] = max(num_valid);
R = Rvec{max_idx};
C = Cvec{max_idx};

% stereo rectification.
rx = C / norm(C);
rz_tilde = [0; 0; 1];
rz = (rz_tilde - dot(rz_tilde, rx) .* rx) ...
	/ norm(rz_tilde - dot(rz_tilde, rx) .* rx);
ry = cross(rz, rx);

R_horiz = [rx'; ry'; rz'];

H1 = K * R_horiz * inv(K);
H2 = K * R_horiz * R' * inv(K);

im1_warped = warp_image(im1, H1);
im2_warped = warp_image(im2, H2);

[R_,t_] = relativeCameraPose(F,cameraParams, x1_best(:,1:2), x2_best(:,1:2));
rx = t_' / norm(t_');
rz_tilde = [0; 0; 1];
rz = (rz_tilde - dot(rz_tilde, rx) .* rx) / norm(rz_tilde - dot(rz_tilde, rx) .* rx);
ry = cross(rz, rx);

R_horiz = [rx'; ry'; rz'];

H3 = K * R_horiz * inv(K);
H4 = K * R_horiz * R_' * inv(K);

im1_w3 = warp_image(im1, H3);
im2_w3 = warp_image(im2, H4);

figure(3);
subplot(2,2,1);
imshow(im1_warped);  pause(0.1);

figure(3);
subplot(2,2,2);
imshow(im2_warped);  pause(0.1);

subplot(2,2,3);
imshow(im1_w3);  pause(0.1);

subplot(2,2,4);
imshow(im2_w3);  pause(0.1);

%file_name = 'stereo.mat';
%save(file_name, 'x1', 'x2', 'F', 'X', 'H1', 'H2', 'im1_w', 'im2_w', 'disparity');

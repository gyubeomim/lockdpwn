clear all;
clc; 

% load stereo images.
im1 = imread('left.jpg');
im2 = imread('right.jpg');

% turn stereo images to grayscale.
im1 = uint8(rgb2gray(im1));
im2 = uint8(rgb2gray(im2));

[height, width] = size(im1);

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

% ransac-based best 8-points extraction method.
n = size(x1, 1);
best_inlier = 0;
best_idx = [];
for i = 1:1000
    % pick random 8 points.
	idx = randperm(n, 8);                        % 8x1
	x1_rand = x1(idx, :);                        % 8x2
	x2_rand = x2(idx, :);                        % 8x2
	x1_rand = transpose([x1_rand, ones(8, 1)])'; % 8x3
	x2_rand = transpose([x2_rand, ones(8, 1)])'; % 8x3

	F = calculate_fundamental_matrix(x1_rand', x2_rand');

	% pick the other (n-8) points and calculate inliers.
	others = setdiff(1:n, idx);
	x1_others = x1(others, :);             % (n-8)x2
	x2_others = x2(others, :);             % (n-8)x2
	x1_others_ = [x1_others ones(n-8, 1)]; % (n-8)x3
	x2_others_ = [x2_others ones(n-8, 1)]; % (n-8)x3

	epipolar_line_est = transpose(F * transpose(x1_others_)); % (n-8)x3

    % calculate distance.
	distance = abs(sum(epipolar_line_est .* x2_others_, 2)) ./ sqrt(sum(epipolar_line_est(:, 1:2) .* epipolar_line_est(:, 1:2), 2));
           
    % if distance is less than threshold.
	inlier_idx = find(distance <= 1); 
	inlier = length(inlier_idx);

	% update best sample points.
	if inlier >= best_inlier
		best_inlier = inlier;
		best_idx = idx;
	end
end

x1_best = x1(best_idx, :);                   % 8x2
x2_best = x2(best_idx, :);                   % 8x2
x1_best = transpose([x1_best, ones(8, 1)])'; % 8x3
x2_best = transpose([x2_best, ones(8, 1)])'; % 8x3

% calculate fundamental matrix.
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

% extract R,t from the essential matrix.
E = K'*F*K;
[R_,t_] = relativeCameraPose(E,cameraParams, x1_best(:,1:2), x2_best(:,1:2));
rx = t_' / norm(t_');
rz_tilde = [0; 0; 1];
rz = (rz_tilde - dot(rz_tilde, rx) .* rx) / norm(rz_tilde - dot(rz_tilde, rx) .* rx);
ry = cross(rz, rx);

R_rect = [rx'; ry'; rz'];
H_left = K * R_rect * inv(K);
H_right = K * R_rect * R_' * inv(K);

% recover the rectified image.
% left image.
im1 = double(im1);
H_left = inv(H_left);

[u_x, u_y] = meshgrid(1:(size(im1,2)), 1:(size(im1,1)));
v_x = H_left(1,1)*u_x + H_left(1,2)*u_y + H_left(1,3);
v_y = H_left(2,1)*u_x + H_left(2,2)*u_y + H_left(2,3);
v_z = H_left(3,1)*u_x + H_left(3,2)*u_y + H_left(3,3);
v_x = v_x./v_z;
v_y = v_y./v_z;

im1_warped(:,:,1) = reshape(interp2(im1(:,:,1), v_x(:), v_y(:)), [height, width]);
im1_warped = uint8(im1_warped);

% right image.
im2 = double(im2);
H_right = inv(H_right);

[u_x, u_y] = meshgrid(1:(size(im2,2)), 1:(size(im2,1)));
v_x = H_right(1,1)*u_x + H_right(1,2)*u_y + H_right(1,3);
v_y = H_right(2,1)*u_x + H_right(2,2)*u_y + H_right(2,3);
v_z = H_right(3,1)*u_x + H_right(3,2)*u_y + H_right(3,3);
v_x = v_x./v_z;
v_y = v_y./v_z;

im2_warped(:,:,1) = reshape(interp2(im2(:,:,1), v_x(:), v_y(:)), [height, width]);
im2_warped = uint8(im2_warped);

% visualize rectified image.
figure(3);
subplot(1,2,1);
imshow(im1_warped);  

figure(3);
subplot(1,2,2);
imshow(im2_warped);  
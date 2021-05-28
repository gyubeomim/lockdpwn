%% ORIGINAL
% im1 = imread('left.bmp');
% im2 = imread('right.bmp');
% 
% im1 = uint8(rgb2gray(im1));
% im2 = uint8(rgb2gray(im2));
% 
% K = [350 0 960/2;
%      0 350 540/2;
%      0 0 1];
%  
% % Visualize matches
% figure(1); clf; pause(0.1);
% imshow(im1); pause(0.1);
% hold on;
% 
% figure(2); clf; pause(0.1);
% imshow(im2); pause(0.1);
% hold on;
%  
% [x1, x2] = FindMatch(im1, im2);
% [F] = ComputeF(x1, x2);
% 
% % Compute four configurations of camera pose given F
% [R1, C1, R2, C2, R3, C3, R4, C4] = ComputeCameraPose(F, K);
%% CUSTOM
clear all; clc; pause(0.1);

im1 = imread('left2.jpg');
im2 = imread('right2.jpg');

im1 = uint8(rgb2gray(im1));
im2 = uint8(rgb2gray(im2));

load('cameraCalibrator.mat')
K = cameraParams.IntrinsicMatrix';
K(1,3) = K(1,3)/1;
K(2,3) = K(2,3)/1;
 
% Visualize matches
figure(1); clf; pause(0.1);
imshow(im1); pause(0.1);
hold on;

figure(2); clf; pause(0.1);
imshow(im2); pause(0.1);
hold on;
 
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
% 
% x1 = x1.*4;
% x2 = x2.*4;

%[x1, x2] = FindMatch(im1, im2);

blobs1 = detectSURFFeatures(im1, 'MetricThreshold', 2000);
blobs2 = detectSURFFeatures(im2, 'MetricThreshold', 2000);
[features1, validBlobs1] = extractFeatures(im1, blobs1);
[features2, validBlobs2] = extractFeatures(im2, blobs2);
indexPairs = matchFeatures(features1, features2, 'Metric', 'SAD', 'MatchThreshold', 5);
p1 = validBlobs1(indexPairs(:,1),:);
p2 = validBlobs2(indexPairs(:,2),:);

x1 = p1.Location;
x2 = p2.Location;

customIdx = [18,19,20,12,11,10,9,8];
[F, x1_best, x2_best, epi_inliers] = ComputeF(x1, x2, customIdx);

% Compute four configurations of camera pose given F
[R1, C1, R2, C2, R3, C3, R4, C4] = ComputeCameraPose(F, K);
%% Fill your code here
% Triangulate Points using four configurations
% e.g., P1: reference camera projection matrix at origin, P2: relative
% camera projection matrix with respect to P1

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
[R,C,X] = DisambiguatePose(R1,C1,X1,R2,C2,X2,R3,C3,X3,R4,C4,X4);

% Stereo rectification
[H1, H2] = ComputeRectification(K, R, C);
im1_w = WarpImage(im1, H1);
im2_w = WarpImage(im2, H2);

[t1, t2] = estimateUncalibratedRectification(F, x1(epi_inliers,:), x2(epi_inliers,:), size(im2));
tform1 = projective2d(t1);
tform2 = projective2d(t2);
[im1_w2, im2_w2] = rectifyStereoImages(im1, im2, tform1, tform2);

[R_,t_] = relativeCameraPose(F,cameraParams, x1_best, x2_best);
[H3, H4] = ComputeRectification(K, R_, t_');
im1_w3 = WarpImage(im1, H3);
im2_w3 = WarpImage(im2, H4);

subplot(3,2,1);
% figure(3);  clf; pause(0.1);
imshow(im1_w);  pause(0.1);

subplot(3,2,2);
% figure(4); clf; pause(0.1);
imshow(im2_w);  pause(0.1);

subplot(3,2,3);
% figure(5); clf; pause(0.1);
imshow(im1_w2);  pause(0.1);

subplot(3,2,4);
% figure(6); clf; pause(0.1);
imshow(im2_w2);  pause(0.1);

subplot(3,2,5);
% figure(5); clf; pause(0.1);
imshow(im1_w3);  pause(0.1);

subplot(3,2,6);
% figure(6); clf; pause(0.1);
imshow(im2_w3);  pause(0.1);

%im1_w = imresize(im1_w, 0.5);
%im2_w = imresize(im2_w, 0.5);
%[disparity] = DenseMatch(im1_w, im2_w);

%file_name = 'stereo.mat';
%save(file_name, 'x1', 'x2', 'F', 'X', 'H1', 'H2', 'im1_w', 'im2_w', 'disparity');

%figure(5)
%clf;
%imagesc(disparity);
%axis equal
%axis off
%colormap(jet);


%% ORIGINAL
im1 = imread('left.bmp');
im2 = imread('right.bmp');

im1 = uint8(rgb2gray(im1));
im2 = uint8(rgb2gray(im2));

K = [350 0 960/2;
     0 350 540/2;
     0 0 1];
 
% Visualize matches
figure(1); clf; pause(0.1);
imshow(im1); pause(0.1);
hold on;

figure(2); clf; pause(0.1);
imshow(im2); pause(0.1);
hold on;
 
[x1, x2] = FindMatch(im1, im2);
[F] = ComputeF(x1, x2);

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

figure(3); clf; pause(0.1);
imshow(im1_w);  pause(0.1);

figure(4); clf; pause(0.1);
imshow(im2_w);  pause(0.1);

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


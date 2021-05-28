%left:  (966,411), (1206,352), (1219,618), (1014,625) are coplanar and (889,360), (1567,487)  
%right: (711,445), (901,461), (957, 728), (776,649) are coplanar and (386,345), (1554,810)

x_left=[966 411 ; 1206 352; 1219 618; 1014 625];
x_right=[711 445 ; 901 461; 957 728; 776 649];

% compute four point-based homography of two view.
H = compute_homography_dlt(x_left', x_right');

x5_left=[889 360 1]';
x5_right=[386 345 1]';
x6_left=[1567 487 1]';
x6_right=[1554 810 1]';

Hx5_left = H*x5_left;
Hx6_left = H*x6_left;

% compute epipolar line l5 and l6.
l5 = cross(Hx5_left, x5_right);
l6 = cross(Hx6_left, x6_right);

% compute epipole by getting the intersection of l5 and l6.
e_r = cross(l5, l6);
skew_e_r = ...
   [0 -e_r(3) e_r(2); ...
    e_r(3) 0 -e_r(1); ...
    -e_r(2) e_r(1) 0];

% compute F = e'^H
F = skew_e_r*H;
format long g;
disp(F)

% load images.
im_left = imread('left.jpg');
im_right = imread('right.jpg');

% visualize epipolar lines in left image.
figure(1);
imshow(im_left);
figure(1);
epipolar_lines = epipolarLine(F',x_right);
points = lineToBorderPoints(epipolar_lines,size(im_left));
line(points(:,[1,3])',points(:,[2,4])','LineWidth',2);

% visualize epipolar lines in right image.
figure(2);
imshow(im_right);
figure(2);
epipolar_lines2 = epipolarLine(F,x_left);
points2 = lineToBorderPoints(epipolar_lines2,size(im_right));
line(points2(:,[1,3])',points2(:,[2,4])','LineWidth',2);
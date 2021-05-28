image =  imread('test.jpg');

% four points
p1 = [1032,50,1];
p2 = [2678,876,1];
p3 = [928,2119,1];
p4 = [2791,2003,1];

% four lines
L1 = cross(p1,p2);
L2 = cross(p3,p4);
L3 = cross(p1,p3);
L4 = cross(p2,p4);

%v1 = vanishing point of lines #1 and #2
v1 = transpose(null([L1; L2]));
v1=[v1(1)/v1(3), v1(2)/v1(3),1];

%v2 = vanishing point of lines #3 and #4
v2 = transpose(null([L3; L4]));
v2=[v2(1)/v2(3), v2(2)/v2(3),1];

% vanishing line of v1 and v2
vanishing_line = null([v1; v2]);
vanishing_line = vanishing_line / vanishing_line(3);

% find projective transform
H = [1 0 0 ; 
    0 1 0 ; 
    transpose(vanishing_line)];

Hv1 = (H*v1')';
Hv1 = Hv1 / sqrt(Hv1(1)*Hv1(1) + Hv1(2)*Hv1(2));

Hv2 = (H*v2')';
Hv2 = Hv2 / sqrt(Hv2(1)*Hv2(1) + Hv2(2)*Hv2(2));

% find directions corresponding to vanishing points.
dir = [Hv1(1), -Hv1(1), Hv2(1), -Hv2(1) ; 
       Hv1(2), -Hv1(2), Hv2(2), -Hv2(2)];
          
thetas = [atan2(dir(1,1),dir(2,1)), 
          atan2(dir(1,2),dir(2,2)), 
          atan2(dir(1,3),dir(2,3)), 
          atan2(dir(1,4),dir(2,4))];

% find direction closest to vertical axis.
% and find the positive angle the rest for the horizontal axis.
[none,vidx] = max([thetas(1), thetas(2)]);
[none,hidx] = min([thetas(3), thetas(4)]);
hidx = hidx + 2;
      
Hmetric = [dir(1,vidx), dir(1,hidx), 0 ; 
           dir(2,vidx), dir(2,hidx), 0 ; 
           0 0 1];
  
% remove reflection
if det(Hmetric) < 0 
    Hmetric(:,1) = -Hmetric(:,1);
end

load cameraCalibrator.mat;
K = cameraParams.IntrinsicMatrix';

% apply homography and crop.
metric_img = applyHomography(image, inv(Hmetric)*H);
metric_img_crop = imcrop(metric_img, [0 1500 1000 1000]);
imshow(metric_img_crop)

% save image.
imwrite(metric_img_crop, 'test_warped.jpg');
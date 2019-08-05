<<<<<<< HEAD
close all, clear all, clc
% 

% %-----------------------------------------------% 
%%%% Cardinal Spline 3D Interpolation %%%%%%%%%%
% % We have 3D data (control points)
%  Px=[35  35  16 15 25 40 65 50 60 80 80];	
%  Py=[47  47  40 15 36 15 25 40 42 27 27];	
%  Pz=[-17 -17 20 15 36 15 25 20 25 -7 -7];	

 % forward_final_before_dense
% load space_camull.txt;
load forward_final_before_dense.txt;

map = forward_final_before_dense;

n =1000; % n �� ���ö��� ����

forward_num = 91;
backward_num = 203;

% Px = map(:,1);
% Py = map(:,2);
% Pz = map(:,3);

% �켱, ��� ��θ� ����
% % Px = map(1:1:forward_num,1); % x 
% % Py = map(1:1:forward_num,2); % y
% % Pz = map(1:1:forward_num,3); % heading 

Px = map(:,1); % x 
Py = map(:,2); % y
Pz = map(:,3); % heading 


% Note first and last points are repeated so that spline curve passes
% through all points

figure, hold on
Tension=0; 

XiYiZi=[];
for k=1:length(Px)-3
    
    tmp=crdatnplusoneval([Px(k),Py(k),Pz(k)],[Px(k+1),Py(k+1),Pz(k+1)],[Px(k+2),Py(k+2),Pz(k+2)],[Px(k+3),Py(k+3),Pz(k+3)],Tension,n);
    % % XiYiZi is 3D interpolated data
    XiYiZi=[XiYiZi tmp];
    
end
% Between each pair of control points plotting n+1 values of first three rows of MatOut 
plot3(XiYiZi(1,:),XiYiZi(2,:),XiYiZi(3,:),'b','linewidth',2)
plot3(Px,Py,Pz,'ro','linewidth',2)

title('\bf 3D Cardinal Spline')
xlabel('\bf X-axis')
ylabel('\bf Y-axis')
zlabel('\bf Z-axis')
legend('\bf Interpolated Data','\bf Control Points','Location','NorthEast')
grid on

view(3);
box;
% %-----------------------------------------------% 

% % Using similar approach you can do Cardinal Spline interpolation for
% % N-Dimensional data


% % --------------------------------
% % This program or any other program(s) supplied with it does not provide any
% % warranty direct or implied.
% % This program is free to use/share for non-commerical purpose only. 
% % Kindly reference the author.
% % Author: Dr. Murtaza Khan
% % Author Reference : http://www.linkedin.com/pub/dr-murtaza-khan/19/680/3b3
% % Research Reference: http://dx.doi.org/10.1007/978-3-642-25483-3_14
% % --------------------------------


% for k=1:length(Px)-3
%     
%     [XiYi]=crdatnplusoneval([Px(k),Py(k)],[Px(k+1),Py(k+1)],[Px(k+2),Py(k+2)],[Px(k+3),Py(k+3)],Tension,n);
%     
%     % % XiYi is 2D interpolated data
%     
%     % Between each pair of control points plotting n+1 values of first two rows of XiYi 
%     plot(XiYi(1,:),XiYi(2,:),'b','linewidth',2) % interpolated data
%     plot(Px,Py,'ro','linewidth',2)          % control points
% end
% title('\bf 2D Cardinal Spline')
% xlabel('\bf X-axis')
% ylabel('\bf Y-axis')
% legend('\bf Interpolated Data','\bf Control Points','Location','NorthEast')
% grid on

=======
close all, clear all, clc
% 

% %-----------------------------------------------% 
%%%% Cardinal Spline 3D Interpolation %%%%%%%%%%
% % We have 3D data (control points)
%  Px=[35  35  16 15 25 40 65 50 60 80 80];	
%  Py=[47  47  40 15 36 15 25 40 42 27 27];	
%  Pz=[-17 -17 20 15 36 15 25 20 25 -7 -7];	

 % forward_final_before_dense
% load space_camull.txt;
load forward_final_before_dense.txt;

map = forward_final_before_dense;

n =1000; % n �� ���ö��� ����

forward_num = 91;
backward_num = 203;

% Px = map(:,1);
% Py = map(:,2);
% Pz = map(:,3);

% �켱, ��� ��θ� ����
% % Px = map(1:1:forward_num,1); % x 
% % Py = map(1:1:forward_num,2); % y
% % Pz = map(1:1:forward_num,3); % heading 

Px = map(:,1); % x 
Py = map(:,2); % y
Pz = map(:,3); % heading 


% Note first and last points are repeated so that spline curve passes
% through all points

figure, hold on
Tension=0; 

XiYiZi=[];
for k=1:length(Px)-3
    
    tmp=crdatnplusoneval([Px(k),Py(k),Pz(k)],[Px(k+1),Py(k+1),Pz(k+1)],[Px(k+2),Py(k+2),Pz(k+2)],[Px(k+3),Py(k+3),Pz(k+3)],Tension,n);
    % % XiYiZi is 3D interpolated data
    XiYiZi=[XiYiZi tmp];
    
end
% Between each pair of control points plotting n+1 values of first three rows of MatOut 
plot3(XiYiZi(1,:),XiYiZi(2,:),XiYiZi(3,:),'b','linewidth',2)
plot3(Px,Py,Pz,'ro','linewidth',2)

title('\bf 3D Cardinal Spline')
xlabel('\bf X-axis')
ylabel('\bf Y-axis')
zlabel('\bf Z-axis')
legend('\bf Interpolated Data','\bf Control Points','Location','NorthEast')
grid on

view(3);
box;
% %-----------------------------------------------% 

% % Using similar approach you can do Cardinal Spline interpolation for
% % N-Dimensional data


% % --------------------------------
% % This program or any other program(s) supplied with it does not provide any
% % warranty direct or implied.
% % This program is free to use/share for non-commerical purpose only. 
% % Kindly reference the author.
% % Author: Dr. Murtaza Khan
% % Author Reference : http://www.linkedin.com/pub/dr-murtaza-khan/19/680/3b3
% % Research Reference: http://dx.doi.org/10.1007/978-3-642-25483-3_14
% % --------------------------------


% for k=1:length(Px)-3
%     
%     [XiYi]=crdatnplusoneval([Px(k),Py(k)],[Px(k+1),Py(k+1)],[Px(k+2),Py(k+2)],[Px(k+3),Py(k+3)],Tension,n);
%     
%     % % XiYi is 2D interpolated data
%     
%     % Between each pair of control points plotting n+1 values of first two rows of XiYi 
%     plot(XiYi(1,:),XiYi(2,:),'b','linewidth',2) % interpolated data
%     plot(Px,Py,'ro','linewidth',2)          % control points
% end
% title('\bf 2D Cardinal Spline')
% xlabel('\bf X-axis')
% ylabel('\bf Y-axis')
% legend('\bf Interpolated Data','\bf Control Points','Location','NorthEast')
% grid on

>>>>>>> 9ccb631ae6dc38c6d8d32c4ccfaeff98646438c0

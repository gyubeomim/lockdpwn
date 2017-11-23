% Load matfile %
load('Matrix.mat')

% Tuning Parameter %
Vx = 100;
Q1 = 15;
Q2 = 25;
R = 500;
Ts = 0.01;
GearRatio = 17.25;

[K,Ad,Bd,Cd,Dd] = dLKS_LQR(Q1,Q2,R,Ts);

% 차량의 초기 위치 및 속도 설정 %
Vx0 = 200;            % 초기 속도 [km/h]
X0 = 0;               % 초기 X좌표 [m]
Y0 = 0;               % 초기 Y좌표 [m]
psi0 = 2 * (pi/180);  % 초기 각도 [rad]

sim('LKS_My')

% Animate %
X = yout(:,1);
Y = yout(:,2);
psi = yout(:,3);
steerangle = yout(:,4);
nframe = 100;
imanual = 0;
t = tout;
scale = 5;

anim_tracking_ESC(X,Y,psi,t,scale,steerangle,nframe,imanual)
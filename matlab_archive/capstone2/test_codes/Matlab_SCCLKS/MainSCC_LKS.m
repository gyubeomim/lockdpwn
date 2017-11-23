% Load matfile %
load('Matrix.mat')
load('PathData.mat')

% 차량의 초기 위치 및 속도 설정 %
X0 = 25;            % 초기 X좌표 [m]
Y0 = 0.00138;       % 초기 Y좌표 [m]
psi0 = -0.6*pi/180; % 초기 각도 [rad]
Vx0 = 60;          % 초기 속도 [km/h]
tf = 30;            % 시뮬레이션 시간 [s]

% % 제어기 설정 %
Q1 = 5;        % Lateral Offset 의 가중치
Q2 = 30;        % Drift Angle의 가중치
R =  250;       % Steering Angle의 가중치
PL = [-50-50i,-50+50i,-30,-20]; % Observer 극점

[K,L] = sfGain(Q1,Q2,R,PL);

% 시뮬레이션 %
[tout,xout,yout] = sim('Bicycle_SCC_LKS.slx');

% 결과 Plot %
Vx =yout(:,1);                      % 종방향 속도 [m/s]
Vy =yout(:,2);                      % 횡방향 속도 [m/s]
gamma =yout(:,3);                   % 요레이트 [rad/s]
X =yout(:,4);                       % X좌표 [m]
Y =yout(:,5);                       % Y좌표 [m]
psi =yout(:,6);                     % 헤딩각 [rad]
deltaf =yout(:,7);                  % 전륜의 조향각 [rad]
scale = 5;                       % Animate의 차량 크기
nframe = 100;                    % Animate의 frame수
imanual = 0;                     % Auto = 0 / manual = 1

anim_tracking_SCC_LKS(P,Vx,X,Y,psi,tout,scale,deltaf,nframe,imanual)
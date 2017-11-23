% Load matfile %
load('Matrix.mat')

% 차량의 초기 위치 및 속도 설정 %
X0 = 0;            % 초기 X좌표 [m]
Y0 = 1;       % 초기 Y좌표 [m]
psi0 = 0 * (pi/180); % 초기 각도 [rad]

% % 제어기 설정 %
Q1 = 10;        % Lateral Offset 의 가중치
Q2 = 30;        % Drift Angle의 가중치
R =  5000;       % Steering Angle의 가중치
PL = [-50-50i,-50+50i,-30,-20]; % Observer 극점

[K,L] = sfGain(Q1,Q2,R,PL);

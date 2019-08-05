%{
    matlab ==> 캡스톤2, LKAS + State Feedback 시스템을 구현을 위해 참고한 코드
                        LQR를 사용해 K와 L 값을 구해야한다 
%}
%% Load matfile %
load('Matrix.mat')
load('PathData.mat')

%% 차량의 초기 위치 및 속도 설정 %
X0 = 25;            % 초기 X좌표 [m]
Y0 = 0.00138;       % 초기 Y좌표 [m]
psi0 = -0.6*pi/180; % 초기 각도 [rad]
Vx0 = 100;          % 초기 속도 [km/h]
tf = 30;            % 시뮬레이션 시간 [s]

%% LQR 제어기 설정 %
Q1 = 5;        % Lateral Offset 의 가중치
Q2 = 30;        % Drift Angle의 가중치
R =  250;       % Steering Angle의 가중치
% 위 Q1,Q2로 대각행렬 Q를 만들고 R과 합해서 LQR을 사용해 State Feedback K 행렬을 구하는듯하다

PL = [-50-50i,-50+50i,-30,-20]; % Observer 극점

[K,L] = state_feedback_Gain(Q1,Q2,R,PL);

% K = [ 0.1414    0.0116    0.7936    0.0449 ]         이 나오고
% L = 1e+03 * [ 0.1060    5.4698    1.3335    0.9096 ] 이 나온다





% Load matfile %
load('Matrix.mat')

% % 제어기 설정 %
Q1 = 10;        % Lateral Offset 의 가중치
Q2 = 30;        % Drift Angle의 가중치
R =  50;       % Steering Angle의 가중치
PL = [-50-50i,-50+50i,-30,-20]; % Observer 극점

[K,L] = sfGain(Q1,Q2,R,PL);
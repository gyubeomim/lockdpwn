% 디지털제어 수업 Assignment3 레포트용 코드
%{
        설계목표
        Tr = 0.016s  <==> Wn = 112.5 rad/s
        Ts = 0.06s   <==> sigma = 76.6
        Mp = 4%     <==> zeta = 0.71
        ess = 0.001 for a ramp input
%}

% =============== 이산등가 (Discrete Equivalent) 설계  ======================
clear,clc;

s = tf('s');

J = 52E-7;        % 질량관성모멘트 [ kg * m^2 ]
b = 3.1831E-4;   % 점성마찰계수 [ Nm*s/rad ]  % pdf에 Speed Regulation Constant로 부터 얻는다 % 3.141e-03
K = 0.0245;       % Kt ,토크상수 [ Nm/A ] 
                      % Ke ,역기전력상수 [ V*s/rad ] 둘은 통상 같은 값으로 한다 
R = 1.8;           % 전기자 직렬저항 [ Ohm ]
L = 0.0024;       % 전기자 인덕턴스 [ H ]

% 원래는 분모가 2차방정식이나 
% 각속도(theta') ==> 각도(theta)로 output이 바뀌면서 적분형태로 1/s가 추가되어 3차방정식 형태가 된다.
my_motor = K/(s*((J*s+b)*(L*s+R)+K^2));  
Gs = my_motor;

% 자세한 설계의 확인은 시뮬링크에 저장해놨다
Ds = pid(4,2.5,0.012);
DGs = Ds * Gs;

% 적절한 Ts를 찾는다 (Wcpm의 2배가 Wbw이고 Wbw의 25배가 안정한 Ts이므로
% Ts는 Wcpm의 50배 정도로 볼 수 있다.
[Gm,Pm,Wcg,Wcp] = margin(Gs)
Ws = 25*2 * Wcp;
fs = Ws / 2 / pi;
Ts = 1/fs;
Dz = c2d(Ds,Ts,'tustin');









% =============== 이산설계 (Discrete Design) 주파수응답 설계  ======================
%{
        Tr <= 0.016s  <==> Wn >= 112.5 rad/s  <==>  Wcpm >= 112.5 rad/s
        Ts <= 0.06s   <==> sigma >= 76.6           
        Mp <= 4%     <==> zeta >= 0.71         <==>  PM >= 71'
        ess = 0.001 for a ramp input                <==>   Kv >= 1000  
%}
clear all, clc;

s = tf('s');

J = 52E-7;        % 질량관성모멘트 [ kg * m^2 ]
b = 3.1831E-4;   % 점성마찰계수 [ Nm*s/rad ]  % pdf에 Speed Regulation Constant로 부터 얻는다 % 3.141e-03
K = 0.0245;       % Kt ,토크상수 [ Nm/A ] 
                      % Ke ,역기전력상수 [ V*s/rad ] 둘은 통상 같은 값으로 한다 
R = 1.8;           % 전기자 직렬저항 [ Ohm ]
L = 0.0024;       % 전기자 인덕턴스 [ H ]


% 원래는 분모가 2차방정식이나 
% 각속도(theta') ==> 각도(theta)로 output이 바뀌면서 적분형태로 1/s가 추가되어 3차방정식 형태가 된다.
my_motor = K/(s*((J*s+b)*(L*s+R)+K^2));  
Gs = my_motor;

% Samplng Time 계산 Wcp의 2배가 Wbw이고 Ws는 Wbw의 25배이다 (곧 50배)
[Gm,Pm,Wcg,Wcp] = margin(Gs);
Ws = 25 * 2 * Wcp;
fs = Ws / 2 / pi;
Ts = 1/fs;

z = tf('z',Ts);

Gz = c2d(Gs,Ts,'zoh');
bode(Gz)
[Gm,Pm,Wcg,Wcp] = margin(Gz)


% (skip해도됨) Gs의 ess(for a ramp input)를 구하기 위한 코드
syms y;
Gy= (1.248e-8*y^3 + 1.012e-5*y^2 + 0.001173*y)/(1.248e-8*y^3 + 1.012e-5*y^2 + 0.001173*y + 0.0245);
double(limit(y/y^2*Gy,y,0));
% Gs의 ess(ramp)는 0.0479인 것을 확인했고 K=100을 넣어 ess를 0에 수렴하게 했다
K = 100;
double(limit(y/y^2*Gy/K,y,0));



%{ 
    DGz의 ess(ramp)를 구하기 위한 코드
    ess = 0.001, r(t) = t 일 경우 Kv >= 1000 이어야 한다
    Gz = ((z+1.4903)*(z+0.0627))/((z-1)*(z-0.4263)*(z-0.0168)) 이다.
    Dz는 Bode plot으로 계속 구해본다
%} 


% 1차 시도 Dz --------------------------------
Dz = (z-0.9048)/(z-0.3679);
DGz = Dz * Gz;

% Kv 값 계산 >= 1000 
syms x;
Dx = (x-0.9048)/(x-0.3679);
Gx = ((x+1.4903)*(x+0.0627))/((x-1)*(x-0.4263)*(x-0.0168));
K = 1;
double(limit(((x-1)/Ts)*K*Dx*Gx,x,1))

K = 8.6207;
bode(K*DGz)
[Gm,Pm,Wcg,Wcp] = margin(K*DGz)
% result : PM = 63 , Wcpm = 117.16



% 2차 시도 Dz --------------------------------
Dz2 = (z-0.9048)/(z);
DGz2 = Dz2 * Gz;

% Kv 값 계산 >= 1000 
syms x;
Dx = (x-0.9048)/(x);
Gx = ((x+1.4903)*(x+0.0627))/((x-1)*(x-0.4263)*(x-0.0168));
K = 1;
double(limit(((x-1)/Ts)*K*Dx*Gx,x,1))

K = 13.62;
bode(K*DGz2)
[Gm,Pm,Wcg,Wcp] = margin(K*DGz2)
% result : PM = 59.3' , Wcpm = 154.95 rad/s




% 3차 시도 Dz --------------------------------
Dz3 = (z-0.88)/(z+0.5);
DGz3 = Dz3 * Gz;

% Kv 값 계산 >= 1000 
syms x;
Dx = (x-0.88)/(x+0.5);
Gx = ((x+1.4903)*(x+0.0627))/((x-1)*(x-0.4263)*(x-0.0168));
K = 1;
double(limit(((x-1)/Ts)*K*Dx*Gx,x,1))

K = 16.21;
bode(K*DGz3)
[Gm,Pm,Wcg,Wcp] = margin(K*DGz3)
% result : PM = 92.59', Wcpm = 117.79 rad/s






% =============== 이산설계 (Discrete Design) 근궤적법 설계  ======================
%{
        Tr <= 0.016s  <==> Wn >= 112.5 rad/s
        Ts <= 0.06s   <==> sigma >= 76.6
        Mp <= 4%     <==> zeta >= 0.71
        ess = 0.001 for a ramp input
        
        r = exp(-sigma*Ts)
 %}
clear all,clc;

s = tf('s');

J = 52E-7;        % 질량관성모멘트 [ kg * m^2 ]
b = 3.1831E-4;   % 점성마찰계수 [ Nm*s/rad ]  % pdf에 Speed Regulation Constant로 부터 얻는다 % 3.141e-03
K = 0.0245;       % Kt ,토크상수 [ Nm/A ] 
                      % Ke ,역기전력상수 [ V*s/rad ] 둘은 통상 같은 값으로 한다 
R = 1.8;           % 전기자 직렬저항 [ Ohm ]
L = 0.0024;       % 전기자 인덕턴스 [ H ]

% 원래는 분모가 2차방정식이나 
% 각속도(theta') ==> 각도(theta)로 output이 바뀌면서 적분형태로 1/s가 추가되어 3차방정식 형태가 된다.
my_motor = K/(s*((J*s+b)*(L*s+R)+K^2));  
Gs = my_motor;


% Samplng Time 계산 Wcp의 2배가 Wbw이고 Ws는 Wbw의 25배이다 (곧 50배)
[Gm,Pm,Wcg,Wcp] = margin(Gs);
Ws = 25 * 2 * Wcp;
fs = Ws / 2 / pi;
Ts = 1/fs;

z = tf('z',Ts);

Gz = c2d(Gs,Ts,'zoh');

rlocus(Gz)
zgrid(0.71, 112.5*Ts)
r = exp(-76.6 * Ts);










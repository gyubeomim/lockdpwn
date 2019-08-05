% 디지털제어 수업 Assignment2 레포트용 코드
%{
        설계목표
        Tr = 0.016s  <==> Wn = 112.5 rad/s
        Ts = 0.06s   <==> sigma = 76.6
        Mp = 4%     <==> zeta = 0.71
        ess = 0%
%}
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
%step(my_motor)

%{ 
pdf에 나온 reference motor의 값들
http://ctms.engin.umich.edu/CTMS/index.php?example=MotorPosition&section=ControlPID
위 홈페이지 값을 그대로 인용했다고 한다

Jrefer = 0.01;
brefer = 0.1;
Lrefer =  0.5;
Rrefer =  1;
Krefer = 0.01;

refer_motor = Krefer/(s*((Jrefer*s+brefer)*(Lrefer*s+Rrefer)+Krefer^2));  
step(refer_motor)
%}

%==============================================================
% P 제어기 : Kp 찾기 ----------------------------------------------
Kp = 3;
for i = 1:3
    C(:,:,i) = pid(Kp);
    Kp = Kp +0.5;
end
sys_cl = feedback(C*my_motor,1);

t = 0:0.001:0.2;
step(sys_cl(:,:,1), sys_cl(:,:,2), sys_cl(:,:,3), t)
ylabel('Position, \theta (radians)')
title('Response to a Step Reference with Different Values of K_p','fontsize',20)
legend('K_p = 3',  'K_p = 3.5',  'K_p =4')

% 외란 구하기
dist_cl = feedback(my_motor,C);
step(dist_cl(:,:,1), dist_cl(:,:,2), dist_cl(:,:,3), t)
ylabel('Position, \theta (radians)')
title('Response to a Step Disturbance with Different Values of K_p','fontsize',20)
legend('K_p = 3', 'K_p = 3.5','K_p = 4')


%==============================================================
% PI 제어기 : Ki 찾기 ----------------------------------------------
Kp = 4;
Ki = 2.5;
for i = 1:3
    C(:,:,i) = pid(Kp,Ki);
    Ki = Ki + 5;
end
sys_cl = feedback(C*my_motor,1);
t = 0:0.001:8;
step(sys_cl(:,:,1), sys_cl(:,:,2), sys_cl(:,:,3), t)
ylabel('Position, \theta (radians)')
title('Response to a Step Reference with K_p = 4 and Different Values of K_i','fontsize',20)
legend('K_i = 2.5', 'K_i = 7.5', 'K_i = 12.5')

% 외란 구하기
dist_cl = feedback(my_motor,C);
t = 0:0.001:8;
step(dist_cl(:,:,1), dist_cl(:,:,2), dist_cl(:,:,3), t)
ylabel('Position, \theta (radians)')
title('Response to a Step Disturbance with K_p = 4 and Different Values of K_i','fontsize',20)
legend('K_i = 2.5', 'K_i = 7.5', 'K_i = 12.5')




%==============================================================
% PID 제어기 : Kd 찾기 ----------------------------------------------
Kp = 4;
Ki = 2.5;
Kd = 0.012;
for i = 1:3
    C(:,:,i) = pid(Kp,Ki,Kd);
    Kd = Kd + 0.5;
end

sys_cl = feedback(C*my_motor,1);
t = 0:0.001:.3;
step(sys_cl(:,:,1), sys_cl(:,:,2), sys_cl(:,:,3), t)
ylabel('Position, \theta (radians)')
title('Response to a Step Reference with K_p = 4, K_i = 2.5 and Different Values of K_d','fontsize',20)
legend('K_d = 0.012', 'K_d = 0.512', 'K_d = 1.012')

% 외란 구하기
dist_cl = feedback(my_motor,C);
t = 0:0.001:8;
step(dist_cl(:,:,1), dist_cl(:,:,2), dist_cl(:,:,3), t)
ylabel('Position, \theta (radians)')
title('Response to a Step Disturbance with K_p = 4, K_i = 2.5 and Different values of K_d','fontsize',20)
legend('K_d = 0.012', 'K_d = 0.512', 'K_d = 1.012')


stepinfo(sys_cl(:,:,2))

% 최종적인 PID 관련 코드
Ds = pid(4,2.5,0.012);
DGs = Ds * my_motor;
step(DGs);
clDGs = feedback(DGs,1);
step(clDGs)
distDGs = feedback(my_motor,Ds);
step(distDGs)
stepinfo(distDGs)


%==============================================================
% root locus -----------------------------------------------------

clear,clc

s = tf('s');

J = 52E-7;        % 질량관성모멘트 [ kg * m^2 ]
b = 3.1831E-4;   % 점성마찰계수 [ Nm*s/rad ]  % pdf에 Speed Regulation Constant로 부터 얻는다 % 3.141e-03
K = 0.0245;       % Kt ,토크상수 [ Nm/A ] 
                      % Ke ,역기전력상수 [ V*s/rad ] 둘은 통상 같은 값으로 한다 
R = 1.8;           % 전기자 직렬저항 [ Ohm ]
L = 0.0024;       % 전기자 인덕턴스 [ H ]

% 원래는 분모가 2차방정식이나 
% 각속도(theta') ==> 각도(theta)로 output이 바뀌면서 적분형태로 1/s가 추가되어 3차방정식 형태가 된다.
%Kp = 44.8;
my_motor = K/(s*((J*s+b)*(L*s+R)+K^2));
rlocus(my_motor)


% 최종적인 Root Locus 관련 코드 (외란에 대한 설계를 다시해야 한다)
K = 7.56;
Ds2 = (s+140.1)/(s+190);
Ds3 = (s+671.14)/(s+1000);
DGs2 = my_motor * K * Ds2 * Ds3;
clDGs2 = feedback(DGs2,1);
step(clDGs2)
stepinfo(clDGs2)
distDGs2 = feedback(my_motor,K*Ds2*Ds3);
step(distDGs2)



%==============================================================
% bode plot design -----------------------------------------------------

clear,clc

s = tf('s');

J = 52E-7;        % 질량관성모멘트 [ kg * m^2 ]
b = 3.1831E-4;   % 점성마찰계수 [ Nm*s/rad ]  % pdf에 Speed Regulation Constant로 부터 얻는다 % 3.141e-03
K = 0.0245;       % Kt ,토크상수 [ Nm/A ] 
                      % Ke ,역기전력상수 [ V*s/rad ] 둘은 통상 같은 값으로 한다 
R = 1.8;           % 전기자 직렬저항 [ Ohm ]
L = 0.0024;       % 전기자 인덕턴스 [ H ]

% 원래는 분모가 2차방정식이나 
% 각속도(theta') ==> 각도(theta)로 output이 바뀌면서 적분형태로 1/s가 추가되어 3차방정식 형태가 된다.
%Kp = 44.8;
my_motor = K/(s*((J*s+b)*(L*s+R)+K^2));


% Gain Margin, Phase Margin, Wcp,Wcg를 구한다
[Gm,Pm,Wcg,Wcp] = margin(my_motor);
% bode plot을 확인한다
bode(my_motor)


%{
 우리의 시스템목표는 
    ess = 0
    Mp = 4%  ==> zeta = 0.715 ==> PM = 71.5
    tr = 0.016s ==> Wn = 112.5 ==> Wcp = 112.5 가 되어야 한다


    우선 my_motor에 대한 Ramp 입력 ess를 구한 결과 0.0478 (4.78%) 가 나온다
    따라서 K 값을 100으로 놓고 ess 를 0으로 수렴하게 한다
    
%}

% 최종적인 Bode 설계 코드 (외란에 대한 설계를 다시해야 한다)

% Gs의 ess(ramp)를 구하기 위한 코드
clGs = feedback(my_motor,1);
E = (1-clGS);
syms s;
double(limit( s/s^2 *(1.248e-8*s^3 + 1.012e-5*s^2 + 0.001173*s)/(1.248e-8*s^3 + 1.012e-5*s^2 + 0.001173*s + 0.0245)  ,s,0))
% Gs의 ess(ramp)는 0.0479인 것을 확인했고 K=100을 넣어 ess를 0에 수렴하게 했다
K2 = 100;
double(limit( s/s^2 *(1.248e-8*s^3 + 1.012e-5*s^2 + 0.001173*s)/(1.248e-8*s^3 + 1.012e-5*s^2 + 0.001173*s + 0.0245* K2)  ,s,0))

Ds4 = (1+s/478.14)/(1+s/47814);
DGs3 = K2 * my_motor * Ds4 * Ds4;
clDGs3 = feedback(DGs3,1);
step(clDGs3)
distDGs3 = feedback(DGs3, K2 * Ds4 * Ds4);
step(distDGs3)



% 디지털제어 Discrete Equivalent Design 프린트 예제 코드

clear all, clc;

s = tf('s');

Gs = 1/(s*(s+1));
Ds = 10*(s/2 + 1)/(s/10+1);
DGs = Gs*Ds;

% Wbw (대역주파수)를 찾기 위한 코드
% Wbw는 통상 Wcpm의 2배로 한다고 한다
% Ws (샘플링주파수)는 Wbw의 25배 이상이 좋다고 한다

%bode(DGs);
CGs = feedback(Gs,1);
%bode(CGs);
bandwidth(CGs);

CDGs = feedback(DGs,1);
bandwidth(CDGs);
%bode(CDGs);

[Gm,Pm,Wcg,Wcp] = margin(DGs);

% Wbw = 2 * Wcpm으로 설정한다
% Ws를 25 * Wbw로 설정한다
250/2/pi;
Ts = 1/(250/2/pi);

% 이산등가 모델을 생성한다
tustinDd = c2d(Ds,Ts,'tustin')
zohDd = c2d(Ds,Ts,'zoh')


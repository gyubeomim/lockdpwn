%% 캡스톤 ==> state feedback

clear;clc

A = [0 1; -3 -1];
B = [0 1]';
C = [1 0];
D = 0;

P = [-2+2j, -2-2j];  % system의 극점, 켤레복소수이어야 한다. 극점인듯?
k = acker(A,B,P);   % acker() : A,B matrix를 받아서 P matrix를 참고하여 K matrix를 반환한다

P1 = [-20+20j, -20-20j];  % observer의 극점. 수렴속도가 빨라야하므로 <-- 좀더 LHP에 있어야 한다
L = acker(A',C',P1);



%% 

% 상태공간
ss_sys_b = ss(A,B,C,D);     % before
ss_sys_f = ss(A-B*k,B,C,D); % after

% 상태공간 ==> 전달함수
TF_B = tf(ss_sys_b)
TF_f = tf(ss_sys_f)

% step을 넣어보고 simulink 그래프와 같은지 확인
step(TF_f)


%%

ss_sys_o = ss(A-L'*C, B, C, D);

TF_O = tf(ss_sys_o)



%%

f = ctrb(A,B);   % controllability
rank(f)          % 2이면 controllability 만족한다

f = obsv(A,C);
rank(f)



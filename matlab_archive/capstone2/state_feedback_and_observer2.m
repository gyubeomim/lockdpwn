% % 
clc ; clear

A=[0 1;-3 -1];
B=[0 1]';
C=[1 0];
D=0;

P=[-2+2j,-2-2j];
P1=[-20+20j,-20-20j];
L=acker(A',C',P1);
k=acker(A,B,P);

%% Input이 있는 경우 
ss_sys_b=ss(A,B,C,D);
ss_sys_f=ss(A-B*k,B,C,D);
TF_b=tf(ss_sys_b);
TF_f=tf(ss_sys_f);


%% 옵저버 
ss_sys_o=ss(A-L'*C,B,C,D);
TF_o=tf(ss_sys_o);


% -- 검증 -- %
syms s l1 l2
A=[-l1 1;-3-l2,-1];
C*inv(s*eye(2,2)-(A))*B;
pretty(ans);
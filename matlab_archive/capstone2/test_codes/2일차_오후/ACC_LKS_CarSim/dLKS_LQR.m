function [K,Ad,Bd,Cd,Dd] = dLKS_LQR(Q1,Q2,R,Ts)

% Model Define
global A B
C = [1, 0, 0, 0];
D = 0;

sys = ss(A,B,C,D);

sys_d = c2d(sys,Ts);

Ad = sys_d.a;
Bd = sys_d.b;
Cd = sys_d.c;
Dd = sys_d.d;

Q = [Q1 0 0  0;
     0  1 0  0;
     0  0 Q2 0;
     0  0 0  1];
 
K = dlqr(Ad,Bd,Q,R);

end
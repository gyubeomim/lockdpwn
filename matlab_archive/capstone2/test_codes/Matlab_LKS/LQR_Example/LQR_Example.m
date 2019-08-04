clear all
close all
clc

% System Model Define %
A = [2 3;-1 4];
B = [0;1];
C = diag([1 1]);
D = [0;0];

subplot(1,2,1,'Fontsize',35)
sys_Origin = ss(A,B,C,D);
initial(sys_Origin,[10 10]);

subplot(1,2,2,'Fontsize',35)
for Q1 = 0 : 100 : 500
    Q = diag([Q1 1]);
    R = 1;
    K = lqr(A,B,Q,R);
    sys_lqr = ss(A-B*K,B,C,D);
    initial(sys_lqr,[10 10]);hold on;
end
legend('Q1=0','Q1=100','Q1=200','Q1=300','Q1=400','Q1=500');
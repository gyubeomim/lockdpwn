load('Matrix.mat')

Vx = 100;
Q1 = 10;
Q2 = 50;
R = 250;
Ts = 0.01;
GearRatio = 17.25;

[K,Ad,Bd,Cd,Dd] = dLKS_LQR(Q1,Q2,R,Ts);

sim('LKS_CarSim')
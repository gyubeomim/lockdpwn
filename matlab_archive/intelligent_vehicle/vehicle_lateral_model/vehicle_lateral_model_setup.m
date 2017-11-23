% Parameter initialization file for lateral vehicle model

% Simulation Time
Tfinal = 20;

% Tire Parameters
Calpha = 39000;
mu = 0.9;
K = 19;

% Vehicle parameters 
m = 2045;
Izz = 5428;
lf = 1.488;
lr = 1.712;
l = lf + lr;

% Initial Values
yaw_rate0 = 0;
Vy0 = 0;
Yaw0 = 0;
X0 = 0;
Y0 = 0;

% Constant Values
SteerAngle = 3*pi/180;
Vx_const =   80/3.6;

% Controller Parameters
Ke = 6000;
Cf = 38925;
Cr = 38255;

Tc = 0.1;
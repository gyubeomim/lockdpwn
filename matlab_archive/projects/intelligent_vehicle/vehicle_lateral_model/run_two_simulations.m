close all
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
Ke = 5000;
Cf = 38925;
Cr = 38255;

Tc = 0.1;

% Run the First Simulation

sim('vehicle_lateral_model',Tfinal);

% Plot First Results

figure(1)

subplot(2,2,1), plot(tout, Vy);
xlabel('time[sec]');
ylabel('speed[m/s]');
title('Vehicle lateral speed');
grid on
hold on

subplot(2,2,3), plot(tout, YawRate*180/pi);
xlabel('time[sec]');
ylabel('Yaw rate[degree/s]');
title('Yaw rate');
grid on
hold on

subplot(1,2,2), plot(X, Y, '*');

xlabel('X[meter]');
ylabel('Y[meter]');
title('Vehicle Trajectory');
grid on
hold on
axis equal 

% Run the Second Simulation

sim('vehicle_lateral_model_controller',Tfinal);

% Plot Second Results

figure(1)

subplot(2,2,1), plot(sim_time, Vy, 'r');
xlabel('time[sec]');
ylabel('speed[m/s]');
title('Vehicle lateral speed');
grid on
legend('without ESP', 'with ESP');

subplot(2,2,3), plot(sim_time, YawRate*180/pi, 'r');
xlabel('time[sec]');
ylabel('Yaw rate[degree/s]');
title('Yaw rate');
grid on
legend('without ESP', 'with ESP');

subplot(1,2,2), plot(X, Y, 'r*');
hold on
xlabel('X[meter]');
ylabel('Y[meter]');
grid on
title('Vehicle Trajectory');
axis equal 
legend('without ESP', 'with ESP');
clear variables
clear global
close all

global Kx Ky Ktheta

t_final = 20;

% Vehicle Model Parameters

x0 = 0;
y0 = 0;
psi0 = 0;      % From x0 axis in CCW direction
u0 = 1;

vx_disturb = 0;
vy_disturb = 0;
tau_u = 1;
w_max = 0.25;
w_min = -w_max;
w0 = 0.1;

w_disturb_mean = 0.05;
w_disturb_var = 0.01;

% Control Parameters
Kx = 1;
Ky = 1;
Ktheta = 1;

sim('robot_controller.mdl', t_final);  % 스크립트상에서 simulink를 돌릴 수 있다 굳굳


% Plot Result 1
figure(1)

plot(x_r, y_r,'r:');
grid on
hold on
plot(x_global, y_global);
xlabel('x[meter]');
ylabel('y[meter]');

% Reset Control Parameters
Kx = 1;
Ky = 1;
Ktheta = 2;


sim('robot_controller.mdl', t_final);

% Plot Result 2
plot(x_global, y_global, '*');

legend('reference trajectory', 'Kx=1, Ky=1, Ktheta=1', 'Kx=1, Ky=1, Ktheta=2');
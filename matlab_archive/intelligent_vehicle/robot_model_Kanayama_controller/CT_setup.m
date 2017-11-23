clear variables
clear global
close all

global Kx Ky Ktheta

t_final = 15;


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

% Reference Trajectory Generation

time = 0:0.1:t_final; 

x_ref.time = time';
y_ref.time = time';
theta_ref.time = time';

x_ref.signals.values = time';
y_ref.signals.values = [0.01*time.*(time-5).*(time-10)]';
dx = diff(x_ref.signals.values);
dy = diff(y_ref.signals.values);
theta_ref.signals.values = atan2(dy, dx);
theta_ref.signals.values = [theta_ref.signals.values; theta_ref.signals.values(length(time)-1)];

% Control Parameters
Kx = 1;
Ky = 1;
Ktheta = 1;

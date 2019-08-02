clear
%	These Data are required mainly for the Vehicle_modle block
%           to specify the parameter value of the vehicle model.
%


% load engine data 
genmap
load enginemap;

% Sprung mass constants
mass = 2000;        % vehicle mass
mass_n = 2000;      % nominal vehicle mass
c_aero = 0.53;      % aerodynamic drag
c_aero_n = c_aero;
F_roll = 172;       % rolling resistance
F_roll_n = F_roll;
g_const = 9.81;     % gravitation coefficient
mw = 29.3;          % wheel mass
mc = mass - 4*mw;   % mass without wheel
lf = 1.36; 
lr = 1.62;   % length to the axis from the vehicle center of gravity
h_cg = 0.49;        % height to the center of gravity

%Engine constants
m2p = 19.2004; % convert mass of air (g) to manifold pressure (KPa)
I_e = 0.2630; % Engine inertia
we_max = max(we_table);
we_min = min(we_table);

%Torque Converter constants
Rdrive = 0.3058; % Final drive ratio

%Gear Shifting
gear_ratios = [0.3423,0.6378,1.0,1.4184];
shift_speeds = [15 32 67]; %shift speeds (mph)

% Brake Model coefficients
psi2kpa = 6.891; % convert psi to KPa
tau_brake = 0.1; % time constant for brake dynamics
KB = 0.9; % brake coefficent
P_po = 10.67; % push out pressure for wheel cylinders (KPa)
delay_brake = 0.2;
beta = [0.2 0.2 0.3 0.3];

%Throttle Actuator coefficients
tau_throttle = 0.01;
max_throttle = max(throttle_table);
min_throttle = min(throttle_table);
max_throttle_rate = 450;
alfa = [0 0 0.5 0.5];

% Wheel Set constants
I_wheel = 1.93; % Inertia of the wheel
I_w = I_wheel;
h_f = 0.33; h_r = 0.33; % wheel radius (m)
h_v = 0.5*(h_r+h_f);               % Average Wheel radius
h = h_v; 
he = 0.33;

Fz = mass*g_const/4;       % Normal force acting on one of the wheel(kN)

% Suspension coefficients (Toyota celica data)
Ks = 17000; Ds = 1500;


% Tire coefficients
mu_B = 22+(Fz-1940)/645; mu_C = 1.35-(Fz-1940)/16125;
mu_D = 2000+(Fz-1940)/0.956; mu_E = -3.6;
K_tire = 1/(6.61e-6);

%%%%% For the slippery road
%%%%% mu_D = 2*mu_D/3;

%Fz = mass*g_const/4/1000;      % Normal force acting on one of the wheel(kN)
%b0 = 1.7; b1 = -7; b2 = 1100; b3 = -0.0035; b4 = 130; b5 = -0.096; 
%b6 = -0.0075; b7 = 0.15; b8 = 0.062;    % Magic Formula Tyre Coefficient
%mu_xm = b1*Fz + b2;
%mu_D = mu_xm*Fz;
%mu_C = b0;
%mu_E = b6*Fz^2 + b7*Fz + b8;
%mu_B = (b3*Fz^2 + b4*Fz)*exp(-b5*Fz)/mu_C/mu_D;

%initial conditions
x_dot_o = 21;
x_o = 0;
we_o = x_dot_o/(he*Rdrive*gear_ratios(3));
w_wheel_o = x_dot_o/he;
throttle_o = 2;
Kt = 146000;

%% Friction-slip curve using Least square procedure.(Best fitting polynomial curve to MF)

s = 0.01:0.01:0.3;

k_mu = mu_B*mu_C*mu_D;

y = mu_D*sin(mu_C*atan(mu_B*s-mu_E*(mu_B*s-atan(mu_B*s))));

disp('maximum friction coefficient');

mu_max = max(y)/Fz;



A = [sum(s.^2)/k_mu sum(s)/k_mu; sum(s)/k_mu length(s)/k_mu];
B = [sum(s./y) - length(s)/k_mu; sum(1./y - 1./(k_mu*s))];

c = inv(A)*B;

u = -0.3:0.01:0.3;

y = mu_D*sin(mu_C*atan(mu_B*u-mu_E*(mu_B*u-atan(mu_B*u))));
y2 = sign(u).*(k_mu*abs(u)./(c(1)*abs(u).^2 + c(2)*abs(u) + 1));
y_prime = k_mu*(1 - c(1)*abs(u).^2)./( c(1)*abs(u).^2 + c(2)*abs(u) + 1 );

%figure(4)
%plot(u,y,u,y2,'r')
%grid on
%axis([-0.3 0.3 -7000 7000])

%figure(3)
%plot(u,y_prime)
%grid on
% v0 = 10;
% Kp = 1;
% Ki = 0.01;
% 
% rambda_dot = he^2*Kt*( mass + I_w)/mass/I_w/v0
% 
% r = rambda_dot;


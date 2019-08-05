function y = kanayama_control(u)

global Kx Ky Ktheta

% Input values
x_r = u(1);
y_r = u(2);
theta_r = u(3);

p_r = [x_r; y_r; theta_r];

x_c = u(4);
y_c = u(5);
theta_c = u(6);

p_c = [x_c; y_c; theta_c];

% Te computation
T_e = [cos(theta_c), sin(theta_c), 0;
    -sin(theta_c), cos(theta_c), 0;
    0, 0, 1];

p_e = T_e*(p_r - p_c);

x_e = p_e(1);
y_e = p_e(2);
theta_e = p_e(3);

% Control Input Computation
v_c = Kx*x_e;
w_c = Ky*y_e + Ktheta*sin(theta_e);

% output values
y(1) = v_c;  % v
y(2) = w_c;  % w

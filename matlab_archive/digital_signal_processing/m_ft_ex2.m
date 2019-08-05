<<<<<<< HEAD
% m_ft_ex2.m
%
% Draws FR of following system
% y[n]= 1.5y[n-1] -0.85 y[n-2] + x[n]

syms w
num = 1;
den = 1 - 1.5*exp(-1j*w) + 0.85*exp(-2j*w);
H = num / den;

% angle or atan2 is not defined for sym

w = 0 : pi/200 : pi;
HH = eval(H);

mH = abs(HH); % magnitude
aH = angle(HH); % angle

subplot(2,1,1); plot(w,mH); ylabel('magnitude'); grid
subplot(2,1,2); plot(w,aH*180/pi); ylabel('phase [deg]'); grid 
=======
% m_ft_ex2.m
%
% Draws FR of following system
% y[n]= 1.5y[n-1] -0.85 y[n-2] + x[n]

syms w
num = 1;
den = 1 - 1.5*exp(-1j*w) + 0.85*exp(-2j*w);
H = num / den;

% angle or atan2 is not defined for sym

w = 0 : pi/200 : pi;
HH = eval(H);

mH = abs(HH); % magnitude
aH = angle(HH); % angle

subplot(2,1,1); plot(w,mH); ylabel('magnitude'); grid
subplot(2,1,2); plot(w,aH*180/pi); ylabel('phase [deg]'); grid 
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

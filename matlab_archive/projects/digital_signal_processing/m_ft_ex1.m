<<<<<<< HEAD
% m_ft_ex1.m
%
% Draws FR of following system
% y[n]= -0.8y[n-1] + x[n] - x[n-1]

syms w
num = 1 - exp(-1j*w);
den = 1 + 0.8*exp(-1j*w);
H = num / den;

% angle or atan2 is not defined for sym

w = 0 : pi/200 : pi;
HH = eval(H);

mH = abs(HH); % magnitude
aH = angle(HH); % angle

subplot(2,1,1); plot(w,mH); ylabel('magnitude'); grid
subplot(2,1,2); plot(w,aH*180/pi); ylabel('phase [deg]'); grid
=======
% m_ft_ex1.m
%
% Draws FR of following system
% y[n]= -0.8y[n-1] + x[n] - x[n-1]

syms w
num = 1 - exp(-1j*w);
den = 1 + 0.8*exp(-1j*w);
H = num / den;

% angle or atan2 is not defined for sym

w = 0 : pi/200 : pi;
HH = eval(H);

mH = abs(HH); % magnitude
aH = angle(HH); % angle

subplot(2,1,1); plot(w,mH); ylabel('magnitude'); grid
subplot(2,1,2); plot(w,aH*180/pi); ylabel('phase [deg]'); grid
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

<<<<<<< HEAD

% m_fod.m
%
% This program plots:
%    input sinusoid
%    first order difference (f_fod)
%    exact differentiation  

fa = input('Type fa, freq [Hz] of analog sinusoid (0.1, 0.7) -->  ');
f  = input('Type f, freq [Hz] of sampling\n(Try different values of f for a given fa) -->  ');

T = 1/f;

tf = 1/fa * 3; % show 3 periods
t = 0 : T : tf;

x = sin(2*pi*fa*t);
yfod = f_fod(x,T);
yreal = 2*pi*fa*cos(2*pi*fa*t);

clf
subplot(2,1,2)
plot(t,x,'.-',t,yfod,'.-',t,yreal,'.-')
legend('input','FOD','exact');
xlabel('n')

% below shows FR of FOD

b = [1 -1]; % coef of numerator
a = 1; % coef of denominator

[H,W]=freqz(b,a);

subplot(2,2,1);
plot(W/pi,W,'g','LineWidth',5)
hold on; plot(W/pi,abs(H)); hold off
legend('ideal','FOD')
title(['f_{signal} = ',num2str(fa),' Hz'])
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('T \times | H(\Omega) |')

subplot(2,2,2);
plot(W/pi,90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal','FOD')
title(['f_{sample} = ',num2str(f),' Hz'])
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')
=======

% m_fod.m
%
% This program plots:
%    input sinusoid
%    first order difference (f_fod)
%    exact differentiation  

fa = input('Type fa, freq [Hz] of analog sinusoid (0.1, 0.7) -->  ');
f  = input('Type f, freq [Hz] of sampling\n(Try different values of f for a given fa) -->  ');

T = 1/f;

tf = 1/fa * 3; % show 3 periods
t = 0 : T : tf;

x = sin(2*pi*fa*t);
yfod = f_fod(x,T);
yreal = 2*pi*fa*cos(2*pi*fa*t);

clf
subplot(2,1,2)
plot(t,x,'.-',t,yfod,'.-',t,yreal,'.-')
legend('input','FOD','exact');
xlabel('n')

% below shows FR of FOD

b = [1 -1]; % coef of numerator
a = 1; % coef of denominator

[H,W]=freqz(b,a);

subplot(2,2,1);
plot(W/pi,W,'g','LineWidth',5)
hold on; plot(W/pi,abs(H)); hold off
legend('ideal','FOD')
title(['f_{signal} = ',num2str(fa),' Hz'])
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('T \times | H(\Omega) |')

subplot(2,2,2);
plot(W/pi,90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal','FOD')
title(['f_{sample} = ',num2str(f),' Hz'])
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

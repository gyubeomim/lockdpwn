<<<<<<< HEAD

% m_int.m
%
% This program plots:
%    input sinusoid
%    exact integration
%    outputs from ZOH, FOH, SOH

fa = input('Type fa, freq [Hz] of analog sinusoid (0.1, 0.3) -->  ');
f  = input('\nType  f, freq [Hz] of sampling\n(Try different values of f for a given fa) -->  ');

T = 1/f;

tf = 1/fa * 3; % show 3 periods
t = 0 : T : tf;

x = sin(2*pi*fa*t);
yreal = 1/(2*pi*fa)*(-cos(2*pi*fa*t) + 1); % 1 must be added since x starts at n=0

b0 = T*[1 0]; % numerator of ZOH
a0 = [1 -1]; % denominator of ZOH

b1 = T*[1 1]; % numerator of FOH
a1 = [2 -2]; % denominator of FOH

b2 = T*[1 4 1]; % numerator of SOH
a2 = [3 0 -3]; % denominator of SOH

y0 = filter(b0,a0,x);
y1 = filter(b1,a1,x);
y2 = filter(b2,a2,x);

clf

subplot(2,3,1)
plot(t,x,'.-',t,y0,'.-',t,yreal,'.-')
legend('input','ZOH','exact')

subplot(2,3,2)
plot(t,x,'.-',t,y1,'.-',t,yreal,'.-')
legend('input','FOH','exact')

subplot(2,3,3)
plot(t,x,'.-',t,y2,'.-',t,yreal,'.-')
legend('input','SOH','exact')

% below shows FR of integrators

% ZOH

[H,W]=freqz(b0/T,a0); % divide by T for normalization
HdB = 20*log10(abs(H));

subplot(4,3,7); 
plot(W/pi,20*log10(1 ./W),'g','LineWidth',5)
hold on; plot(W/pi,HdB); hold off
legend('ideal'); title('ZOH')
ylabel('| 1/T \times H(\Omega) |_{dB}')

subplot(4,3,10);
plot(W/pi,-90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal');
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')

% FOH

[H,W]=freqz(b1/T,a1); % divide by T for normalization
HdB = 20*log10(abs(H));

subplot(4,3,8);
plot(W/pi,20*log10(1./W),'g','LineWidth',5)
hold on; plot(W/pi,HdB); hold off
legend('ideal'); title('FOH')
ylabel('| 1/T \times H(\Omega) |_{dB}')

subplot(4,3,11);
plot(W/pi,-90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal');
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')

% SOH

[H,W]=freqz(b2/T,a2); % divide by T for normalization
HdB = 20*log10(abs(H));

subplot(4,3,9);
plot(W/pi,20*log10(1./W),'g','LineWidth',5)
hold on; plot(W/pi,HdB); hold off
legend('ideal'); title('SOH')
ylabel('| 1/T \times H(\Omega) |_{dB}')

subplot(4,3,12);
plot(W/pi,-90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal');
=======

% m_int.m
%
% This program plots:
%    input sinusoid
%    exact integration
%    outputs from ZOH, FOH, SOH

fa = input('Type fa, freq [Hz] of analog sinusoid (0.1, 0.3) -->  ');
f  = input('\nType  f, freq [Hz] of sampling\n(Try different values of f for a given fa) -->  ');

T = 1/f;

tf = 1/fa * 3; % show 3 periods
t = 0 : T : tf;

x = sin(2*pi*fa*t);
yreal = 1/(2*pi*fa)*(-cos(2*pi*fa*t) + 1); % 1 must be added since x starts at n=0

b0 = T*[1 0]; % numerator of ZOH
a0 = [1 -1]; % denominator of ZOH

b1 = T*[1 1]; % numerator of FOH
a1 = [2 -2]; % denominator of FOH

b2 = T*[1 4 1]; % numerator of SOH
a2 = [3 0 -3]; % denominator of SOH

y0 = filter(b0,a0,x);
y1 = filter(b1,a1,x);
y2 = filter(b2,a2,x);

clf

subplot(2,3,1)
plot(t,x,'.-',t,y0,'.-',t,yreal,'.-')
legend('input','ZOH','exact')

subplot(2,3,2)
plot(t,x,'.-',t,y1,'.-',t,yreal,'.-')
legend('input','FOH','exact')

subplot(2,3,3)
plot(t,x,'.-',t,y2,'.-',t,yreal,'.-')
legend('input','SOH','exact')

% below shows FR of integrators

% ZOH

[H,W]=freqz(b0/T,a0); % divide by T for normalization
HdB = 20*log10(abs(H));

subplot(4,3,7); 
plot(W/pi,20*log10(1 ./W),'g','LineWidth',5)
hold on; plot(W/pi,HdB); hold off
legend('ideal'); title('ZOH')
ylabel('| 1/T \times H(\Omega) |_{dB}')

subplot(4,3,10);
plot(W/pi,-90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal');
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')

% FOH

[H,W]=freqz(b1/T,a1); % divide by T for normalization
HdB = 20*log10(abs(H));

subplot(4,3,8);
plot(W/pi,20*log10(1./W),'g','LineWidth',5)
hold on; plot(W/pi,HdB); hold off
legend('ideal'); title('FOH')
ylabel('| 1/T \times H(\Omega) |_{dB}')

subplot(4,3,11);
plot(W/pi,-90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal');
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')

% SOH

[H,W]=freqz(b2/T,a2); % divide by T for normalization
HdB = 20*log10(abs(H));

subplot(4,3,9);
plot(W/pi,20*log10(1./W),'g','LineWidth',5)
hold on; plot(W/pi,HdB); hold off
legend('ideal'); title('SOH')
ylabel('| 1/T \times H(\Omega) |_{dB}')

subplot(4,3,12);
plot(W/pi,-90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal');
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')
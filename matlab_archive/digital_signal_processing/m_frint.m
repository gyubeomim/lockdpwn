<<<<<<< HEAD
%
% m_frint.m
%
% This program plots FR of 3 integrators (ZOH, FOH, SOH) when T = 1

% ZOH

b = 1; % coef of numerator
a = [1 -1]; % coef of denominator

[H,W]=freqz(b,a);
HdB = 20*log10(abs(H));

subplot(2,3,1); 
plot(W/pi,20*log10(1./W),'g','LineWidth',5)
hold on; plot(W/pi,HdB); hold off
legend('ideal','ZOH'); title('ZOH')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('| 1/T \times H(\Omega) |_{dB}')

subplot(2,3,4);
plot(W/pi,-90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal','ZOH'); title('ZOH')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')

% FOH

b = [1 1]; % coef of numerator
a = [2 -2]; % coef of denominator

[H,W]=freqz(b,a);
HdB = 20*log10(abs(H));

subplot(2,3,2);
plot(W/pi,20*log10(1./W),'g','LineWidth',5)
hold on; plot(W/pi,HdB); hold off
legend('ideal','FOH'); title('FOH')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('| 1/T \times H(\Omega) |_{dB}')

subplot(2,3,5);
plot(W/pi,-90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal','FOH'); title('FOH')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')

% SOH

b = [1 4 1]; % coef of numerator
a = [3 0 -3]; % coef of denominator

[H,W]=freqz(b,a);
HdB = 20*log10(abs(H));

subplot(2,3,3);
plot(W/pi,20*log10(1./W),'g','LineWidth',5)
hold on; plot(W/pi,HdB); hold off
legend('ideal','SOH'); title('SOH')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('| 1/T \times H(\Omega) |_{dB}')

subplot(2,3,6);
plot(W/pi,-90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal','SOH'); title('SOH')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')
=======
%
% m_frint.m
%
% This program plots FR of 3 integrators (ZOH, FOH, SOH) when T = 1

% ZOH

b = 1; % coef of numerator
a = [1 -1]; % coef of denominator

[H,W]=freqz(b,a);
HdB = 20*log10(abs(H));

subplot(2,3,1); 
plot(W/pi,20*log10(1./W),'g','LineWidth',5)
hold on; plot(W/pi,HdB); hold off
legend('ideal','ZOH'); title('ZOH')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('| 1/T \times H(\Omega) |_{dB}')

subplot(2,3,4);
plot(W/pi,-90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal','ZOH'); title('ZOH')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')

% FOH

b = [1 1]; % coef of numerator
a = [2 -2]; % coef of denominator

[H,W]=freqz(b,a);
HdB = 20*log10(abs(H));

subplot(2,3,2);
plot(W/pi,20*log10(1./W),'g','LineWidth',5)
hold on; plot(W/pi,HdB); hold off
legend('ideal','FOH'); title('FOH')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('| 1/T \times H(\Omega) |_{dB}')

subplot(2,3,5);
plot(W/pi,-90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal','FOH'); title('FOH')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')

% SOH

b = [1 4 1]; % coef of numerator
a = [3 0 -3]; % coef of denominator

[H,W]=freqz(b,a);
HdB = 20*log10(abs(H));

subplot(2,3,3);
plot(W/pi,20*log10(1./W),'g','LineWidth',5)
hold on; plot(W/pi,HdB); hold off
legend('ideal','SOH'); title('SOH')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('| 1/T \times H(\Omega) |_{dB}')

subplot(2,3,6);
plot(W/pi,-90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal','SOH'); title('SOH')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

<<<<<<< HEAD
%
% m_frfod.m
%
% This program plots FR of FOD differentiator when T = 1

b = [1 -1]; % coef of numerator
a = 1; % coef of denominator

[H,W]=freqz(b,a);

subplot(2,1,1);
plot(W/pi,W,'g','LineWidth',5)
hold on; plot(W/pi,abs(H)); hold off
legend('ideal','FOD')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('T \times | H(\Omega) |')

subplot(2,1,2);
plot(W/pi,90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal','FOD')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')
=======
%
% m_frfod.m
%
% This program plots FR of FOD differentiator when T = 1

b = [1 -1]; % coef of numerator
a = 1; % coef of denominator

[H,W]=freqz(b,a);

subplot(2,1,1);
plot(W/pi,W,'g','LineWidth',5)
hold on; plot(W/pi,abs(H)); hold off
legend('ideal','FOD')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('T \times | H(\Omega) |')

subplot(2,1,2);
plot(W/pi,90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); hold off
legend('ideal','FOD')
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

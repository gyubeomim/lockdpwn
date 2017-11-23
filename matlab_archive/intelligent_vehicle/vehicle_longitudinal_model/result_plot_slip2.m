close all
figure(2)

tt = linspace(0, 2.1, length(slip));

subplot(3,1,1), plot(tt, slip(:,1), 'LineWIdth',2);
hold on
subplot(3,1,1), plot(tt, slip(:,3), 'r:', 'LineWIdth',2);
xlabel('time[sec]');
ylabel('slip');
title('Wheel Slip');
grid on
% axis([0 0.8 -1 0]);
legend('Front Wheel', 'Rear Wheel')

axis([0 2.1 -1.3 0])
%xlim([0 3]);

%% Tractive Force
subplot(3,1,2), plot(tt, Tractive_Force(:,1), 'LineWIdth',2);
hold on
subplot(3,1,2), plot(tt, Tractive_Force(:,2), 'r:', 'LineWIdth',2);
xlabel('time[sec]');
ylabel('tractive force[N]');
title('Wheel Tractive Force');
grid on
legend('Front Wheel', 'Rear Wheel')
xlim([0 2.1]);


%% Wheel Speed


subplot(3,1,3), plot(tt, wheel_speed(:,1), 'LineWIdth',2);
hold on
subplot(3,1,3), plot(tt, wheel_speed(:,2), 'r:', 'LineWIdth',2);
xlabel('time[sec]');
ylabel('Wheel Speed[rad/sec]');
title('Wheel Speed');
grid on
legend('Front Wheel', 'Rear Wheel')
xlim([0 2.1]);





close all
figure(2)
tfinal = 207;

subplot(3,1,1), plot(tout(1:tfinal), slip(1:tfinal,1));
hold on
subplot(3,1,1), plot(tout(1:tfinal), slip(1:tfinal,3), 'r:');
xlabel('time[sec]');
ylabel('slip');
title('Wheel Slip');
grid on
% axis([0 0.8 -1 0]);
legend('Front Wheel', 'Rear Wheel')


xlim([0 3]);

subplot(3,1,2), plot(tout(1:tfinal), Tractive_Force(1:tfinal,1));
hold on
subplot(3,1,2), plot(tout(1:tfinal), Tractive_Force(1:tfinal,2), 'r:');
xlabel('time[sec]');
ylabel('tractive force[N]');
title('Wheel Tractive Force');
grid on
legend('Front Wheel', 'Rear Wheel')


subplot(3,1,3), plot(tout(1:tfinal), wheel_speed(1:tfinal,1));
hold on
subplot(3,1,3), plot(tout(1:tfinal), wheel_speed(1:tfinal,2), 'r:');
xlabel('time[sec]');
ylabel('Wheel Speed[rad/sec]');
title('Wheel Speed');
grid on
legend('Front Wheel', 'Rear Wheel')




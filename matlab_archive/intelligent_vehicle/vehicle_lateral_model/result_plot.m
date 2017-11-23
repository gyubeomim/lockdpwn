close all

figure(1)

subplot(2,2,1), plot(tout, Vy);
xlabel('time[sec]');
ylabel('speed[m/s]');
title('Vehicle lateral speed');
grid on

subplot(2,2,3), plot(tout, YawRate*180/pi);
xlabel('time[sec]');
ylabel('Yaw rate[degree/s]');
title('Yaw rate');
grid on

subplot(1,2,2), plot(X, Y, '*');
xlabel('X[meter]');
ylabel('Y[meter]');
grid on
hold on
title('Vehicle Trajectory');
axis equal 

figure(2)
subplot(2,1,1), plot(tout, Fyf)
hold on
plot(tout, Fyr, 'r')
xlabel('time[sec]');
ylabel('lateral tire force[N]');
title('Lateral Tire Force');
legend('Front tire force', 'Rear tire force');
grid on

subplot(2,1,2), plot(tout, alpha_f);
hold on
plot(tout, alpha_r,'r');
xlabel('time[sec]');
ylabel('tire slip angle');
title('Lateral Tire Slip Angle');
legend('Front slip angle', 'Rear slip angle');
grid on

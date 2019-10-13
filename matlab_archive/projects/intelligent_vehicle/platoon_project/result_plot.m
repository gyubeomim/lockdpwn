figure(1)

subplot(2,2,1), plot(tout, v);
xlabel('time[sec]');
ylabel('speed[m/s]');
title('Vehicle speed');
grid on

subplot(2,2,2), plot(tout, We);
xlabel('time[sec]');
ylabel('engine speed[rad/s]');
title('Engine speed');
grid on

subplot(2,2,3), plot(tout, a);
xlabel('time[sec]');
ylabel('acceleration[m/s2]');
title('Vehicle acceleration');
grid on

subplot(2,2,4), plot(tout, Pb);
xlabel('time[sec]');
ylabel('speed[m/s]');
title('Brake Pressure');
grid on


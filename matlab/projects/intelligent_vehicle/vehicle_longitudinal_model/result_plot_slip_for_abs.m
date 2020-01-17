%{
    matlab ==> 지능형자동차 HW2_2, ABS 제어기를 만들어서 성능을 테스트 해보기 위해 plot하는 코드
                slip ratio
                Tractive Force
                Wheel Speed
                Brake Torque
%}
close all
figure(2)



%% Road Condition

% lincoln model default
% mu_B = 26.5969 ; mu_C = 1.1661; mu_D = 5.1015e+03; mu_E = -3.6;

% dry
% mu_B = 10 ; mu_C = 1.9; mu_D = 1; mu_E = 0.97;

% wet
% mu_B = 12 ; mu_C = 2.3; mu_D = 0.82 ; mu_E = 1;

% snow
% mu_B = 5; mu_C = 2; mu_D = 0.3 ; mu_E = 1;

% ice
% mu_B = 4 ; mu_C = 2; mu_D = 0.1 ; mu_E = 1;


%% slip ratio

x_lim = 3.5;

% ed: tt의 간격을 임의로 계속 변경해줘야한다
%      length() 함수를 써서 자동으로 변경했다
tt = linspace(0, x_lim, length(slip));



subplot(2,2,1), plot(tt, slip(:,1), 'LineWIdth',2);
hold on
subplot(2,2,1), plot(tt, slip(:,3), 'r:', 'LineWIdth',2);
xlabel('time[sec]');
ylabel('slip');
title('Wheel Slip');
grid on
% axis([0 0.8 -1 0]);
legend('Front Wheel', 'Rear Wheel')

axis([0 x_lim -1.3 0])
%xlim([0 3]);

%% Tractive Force
subplot(2,2,2), plot(tt, Tractive_Force(:,1), 'LineWIdth',2);
hold on
subplot(2,2,2), plot(tt, Tractive_Force(:,2), 'r:', 'LineWIdth',2);
xlabel('time[sec]');
ylabel('tractive force[N]');
title('Wheel Tractive Force');
grid on
legend('Front Wheel', 'Rear Wheel')
xlim([0 x_lim]);


%% Wheel Speed


subplot(2,2,3), plot(tt, wheel_speed(:,1), 'LineWIdth',2);
hold on
subplot(2,2,3), plot(tt, wheel_speed(:,2), 'r:', 'LineWIdth',2);
xlabel('time[sec]');
ylabel('Wheel Speed[rad/sec]');
title('Wheel Speed');
grid on
legend('Front Wheel', 'Rear Wheel')
xlim([0 x_lim]);


%% Brake Torque
ttt = linspace(0,x_lim,length(Brake_Torque_RF));

subplot(2,2,4), plot(ttt, Brake_Torque_RF(:,1), 'LineWIdth',2);
hold on
subplot(2,2,4), plot(ttt, Brake_Torque_RR, 'r:', 'LineWIdth',2);
xlabel('time[sec]');
ylabel('Brake Torque');
title('Brake Torque modified by ABS');
grid on
legend('Right Front Wheel', 'Right Rear Wheel')
xlim([0 x_lim]);


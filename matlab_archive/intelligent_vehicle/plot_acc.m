%{
    matlab ==> 지능형자동차, HW1 acc 모델 만들어서 두 차량의 거리간격을 일정하게 하는 코드
                                      핵심 코드는 simulink acc_model_ed.mdl에 있고
                                      이 코드는 plot용 코드이다
%}

%% 앞차와 뒷차의 trajectory plot
plot(tout, x_rear,'r', tout, x_front,'b-', 'LineWidth', 2); grid;
title('Front, Rear Vehicles Trajectory', 'FontSize', 15);
xlabel('Time','FontSize', 15);
ylabel('Trajectory (m)','FontSize', 15);
legend({'Rear', 'Front'}, 'FontSize', 15);



%% 두 차의 거리차이 plot
plot(tout, -x, 'LineWIdth', 2); grid;
title('Diff Distance between Two Vehicles', 'FontSize', 15);
xlabel('Time','FontSize', 15);
ylabel('Diff Distance (m)','FontSize', 15);
legend({'diff distance'}, 'FontSize', 15);
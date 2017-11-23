%{
    matlab ==> 지능형자동차 HW2 1번 문제를 푼 코드
                       magic tire fomular를 사용해 slip ratio - tire friction
                       coeff 그래프를 그려본 코드
%}

%% Case 1 Dry

s = 0 : 0.01 : 1;
B = 10 ; C = 1.9; D = 1; E = 0.97;

tire_friction_coeff = D*sin(C*atan(B*s-E*(B*s-atan(B*s))));

hold on;

plot(s, tire_friction_coeff, 'LineWidth', 2); 
title('Tire Friction Coefficient - Slip Ratio ', 'FontSize', 15);
xlabel('Slip Ratio','FontSize', 15);
ylabel('Tire Friction Coefficient','FontSize', 15);

%% Case 2 Wet
B = 12 ; C = 2.3; D = 0.82 ; E = 1;

tire_friction_coeff = D*sin(C*atan(B*s-E*(B*s-atan(B*s))));

plot(s, tire_friction_coeff,'r', 'LineWidth', 2); 
title('Tire Friction Coefficient - Slip Ratio ', 'FontSize', 15);
xlabel('Slip Ratio','FontSize', 15);
ylabel('Tire Friction Coefficient','FontSize', 15);

%% Case 3 Snow
B = 5; C = 2; D = 0.3 ; E = 1;

tire_friction_coeff = D*sin(C*atan(B*s-E*(B*s-atan(B*s))));

plot(s, tire_friction_coeff,'k', 'LineWidth', 2); 
title('Tire Friction Coefficient - Slip Ratio ', 'FontSize', 15);
xlabel('Slip Ratio','FontSize', 15);
ylabel('Tire Friction Coefficient','FontSize', 15);

%% Case 4 Ice
B = 4 ; C = 2; D = 0.1 ; E = 1;

tire_friction_coeff = D*sin(C*atan(B*s-E*(B*s-atan(B*s))));

plot(s, tire_friction_coeff,'g', 'LineWidth', 2); 
title('Tire Friction Coefficient - Slip Ratio ', 'FontSize', 15);
xlabel('Slip Ratio','FontSize', 15);
ylabel('Tire Friction Coefficient','FontSize', 15);

grid;
legend('Dry', 'Wet', 'Snow', 'Ice');
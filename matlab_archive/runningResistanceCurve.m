% matlab ==> 차량주행곡선을 그리는 코드
clear,clc;

% 차량 제원
Mv = 1000;  % 차량질량 kg
M1 = 150;   % 적재물질량 kg
Ur = 0.015; % 구름저항계수
theta = atan(0.05); % 도로면기울기 (오르막 5%)

v1 = 60;      % 1단      % 차량속도 km/h
v2 = 130;     % 2단

Mf1 = 1.4;  % 질량계수
Mf2 = 1.23;
Mf3 = 1.1;

Af = 1.71;  % 전투영면적 m^2
Cd = 0.35;  % 공기저항계수
Rho = 1.2; % 공기밀도 kg/m^3
a = 0.5; % 일정가속도 m/s^2
g = 9.81;   % 중력가속도 m/s^2

% 초기조건 설정
v = 1:1:180;

% Rolling Resistance
Rr = Ur * (Mv + M1) * g * cos(theta) + v * 0;

% Gradient Resistance
Rg = (Mv + M1) * g * sin(theta) + v* 0;

% Drag Resistance
Rd = Cd * Af * Rho/2 * (v/3.6).^2;  %   .  <== 이걸 붙여줘야한다. 
                                                % 3.6은 km/h ==> m/s로 나누기 위해 사용한다
% Acceleration Resisntace
Ra =  zeros(1,180);

% 속도에 따라 질량계수를 다르게 계산해서 Ra 값을 구합니다
for vt = 1:1:180
    if vt < 60
        Ra(1,vt) = Mf1*(Mv + M1) * a;
    
    elseif 60 <= vt  && vt <= 130
        Ra(1,vt) = Mf2* (Mv + M1) *a;
        
    else
        Ra(1,vt) = Mf3 * (Mv + M1) *a;
    end
end

% 그래프를 동시에 4개 그리고 
hold on;
plot(v,Rr,'r','LineWidth',2);
plot(v,Rg + Rr,'g','LineWidth',2);
plot(v,Rd + Rg + Rr,'b','LineWidth',2);
plot(v,Ra + Rd + Rg + Rr,'c','LineWidth',2);

% 범주를 설정합니다
legend('Rr','Rr + Rg','Rr + Rg + Rd','Rr + Rg + Rd + Ra');

% 그래프 축의 이름을 설정합니다
grid;
title('Total Driving Resistance','fontsize',15);
xlabel('Velocity (m/s)','fontsize',15);
ylabel('Resistance (N)','fontsize',15);










% 자동차융합실험2 
% Powertrain 구조에서 동력단속을 위한 Wet Clutch의 Torque Transfer 거동 실험 코드

% 엑셀데이터로 부터 다음 변수들을 받는다

%{
        tt : 1.5초부터 1.9초까지 있는 28800개의 시간 데이터
        applyforce : 시간데이터에 따른 applyforce 데이터
        engageT : 시간데이터에 따른 engageT 데이터
        mu : 공식을 통해 구한 마찰력계수
        
        (아래는 보간이 필요한 변수들)
        t
        drivespeed
        t2
        drivenspeed
%}


%=========================== CASE 1 ==================================
% 그래프1 시간-토크
plot(tt,engageT,'linewidth',2),grid
xlabel('time [s]','fontsize',25);
ylabel('Engagement Torque [Nm]','fontsize',25);
title('Engagement Torque - Time [1500RPM, 20deg, 500cc, 4000N]','fontsize',25);

% drive,driven speed 보간을 하기위해 TT를 선언한다
TT = linspace(1.5,2.0,28801);
interpdrivespeed = interp1(t,drivespeed,TT,'pchip');
interpdrivenspeed = interp1(t2,drivenspeed,T,'pchip');

% 상대 RPM을 구한다
for i = 1:28801
relativeRPM(i) = interpdrivespeed(i) - interpdrivenspeed(i);
end

% 그래프2 시간에 따른 클러치의 RPM 
plot(TT,interpdrivespeed,TT,interpdrivenspeed,'linewidth',2)
xlabel('time [s]','fontsize',25);
ylabel('RPM [rev/min]','fontsize',25);
title('RPM - Time [1500RPM, 20deg, 500cc, 4000N]','fontsize',25);grid

% 그래프3 시간에 따른 상대 RPM
plot(TT, relativeRPM,'r','linewidth',2);grid
xlabel('time [s]','fontsize',25);
ylabel('Relative RPM [rev/min]','fontsize',25);
title('Relative RPM - Time [1500RPM, 20deg, 500cc, 4000N]','fontsize',25);

% 그래프4 상대 RPM에 따른 mu 값의 변화 그래프
plot(relativeRPM,mu,'c','linewidth',2);grid
xlabel('Relative RPM [rev/min]','fontsize',25);
ylabel('Friction Coefficient','fontsize',25);
title('Friction Coefficient - Relative RPM [1500RPM, 20deg, 500cc, 4000N]','fontsize',25);
axis([-10 100 -1 1])
















%=========================== CASE 2 ==================================
% 그래프1 시간-토크
plot(tt,engageT,'linewidth',2),grid
xlabel('time [s]','fontsize',25);
ylabel('Engagement Torque [Nm]','fontsize',25);
title('Engagement Torque - Time [900RPM, 20deg, 500cc, 4000N]','fontsize',25);

% drive,driven speed 보간을 하기위해 TT를 선언한다
TT = linspace(1.5,2.0,28801);
interpdrivespeed = interp1(t,drivespeed,TT,'pchip');
interpdrivenspeed = interp1(t2,drivenspeed,TT,'pchip');

% 상대 RPM을 구한다
for i = 1:28801
relativeRPM(i) = interpdrivespeed(i) - interpdrivenspeed(i);
end

% 그래프2 시간에 따른 클러치의 RPM 
plot(TT,interpdrivespeed,TT,interpdrivenspeed,'linewidth',2)
xlabel('time [s]','fontsize',25);
ylabel('RPM [rev/min]','fontsize',25);
title('RPM - Time [900RPM, 20deg, 500cc, 4000N]','fontsize',25);grid

% 그래프3 시간에 따른 상대 RPM
plot(TT, relativeRPM,'r','linewidth',2);grid
xlabel('time [s]','fontsize',25);
ylabel('Relative RPM [rev/min]','fontsize',25);
title('Relative RPM - Time [900RPM, 20deg, 500cc, 4000N]','fontsize',25);

% 그래프4 상대 RPM에 따른 mu 값의 변화 그래프
plot(relativeRPM,mu,'c','linewidth',2);grid
xlabel('Relative RPM [rev/min]','fontsize',25);
ylabel('Friction Coefficient','fontsize',25);
title('Friction Coefficient - Relative RPM [900RPM, 20deg, 500cc, 4000N]','fontsize',25);
axis([-10 100 -1 1])








%=========================== CASE 3 ==================================
% 그래프1 시간-토크
plot(tt,engageT,'linewidth',2),grid
xlabel('time [s]','fontsize',25);
ylabel('Engagement Torque [Nm]','fontsize',25);
title('Engagement Torque - Time [900RPM, 20deg, 500cc, 8000N]','fontsize',25);

% drive,driven speed 보간을 하기위해 TT를 선언한다
TT = linspace(1.3,1.7,28801);
interpdrivespeed = interp1(t,drivespeed,TT,'pchip');
interpdrivenspeed = interp1(t2,drivenspeed,TT,'pchip');

% 상대 RPM을 구한다
for i = 1:28801
relativeRPM(i) = interpdrivespeed(i) - interpdrivenspeed(i);
end

% 그래프2 시간에 따른 클러치의 RPM 
plot(TT,interpdrivespeed,TT,interpdrivenspeed,'linewidth',2)
xlabel('time [s]','fontsize',25);
ylabel('RPM [rev/min]','fontsize',25);
title('RPM - Time [900RPM, 20deg, 500cc, 8000N]','fontsize',25);grid

% 그래프3 시간에 따른 상대 RPM
plot(TT, relativeRPM,'r','linewidth',2);grid
xlabel('time [s]','fontsize',25);
ylabel('Relative RPM [rev/min]','fontsize',25);
title('Relative RPM - Time [900RPM, 20deg, 500cc, 8000N]','fontsize',25);

% 그래프4 상대 RPM에 따른 mu 값의 변화 그래프
plot(relativeRPM,mu,'c','linewidth',2);grid
xlabel('Relative RPM [rev/min]','fontsize',25);
ylabel('Friction Coefficient','fontsize',25);
title('Friction Coefficient - Relative RPM [900RPM, 20deg, 500cc, 8000N]','fontsize',25);
axis([-10 300 -1 1])
















% matlab ==> 공을 45각도로 던지는 상황을 plot으로 동영상처럼 보이게 한 코드
clc,clear all

% g 값과 초기 던지는 각도 theta값, 초기속도 값을 설정합니다
g = 9.81; 
theta0 = 45*pi/180; 
v0=5;

% 초기값을 설정합니다
t(1) = 0; 
x =0; 
y =0;

% 0초일때를 plot합니다
plot(x,y,'o','MarkerFaceColor','b','MarkerSize',8)
title('The orbital of thrown Ball','fontsize',15);
xlabel('Time (t)','fontsize',15);
ylabel('Height (m)','fontsize',15);
axis([0 3 0 0.8])
grid on
hold on

% dt의 값을 설정합니다
% 작게 설정할 수록 더 천천히 움직이는 동영상을 볼 수 있습니다
dt = 1/256;

for j = 2:1000
    
    % 루프를 돌면서 x,y 값을 받고
    t(j) = t(j-1) + dt;
    x = v0*cos(theta0)*t(j);
    y = v0*sin(theta0)*t(j)-0.5*g*t(j)^2;
    
    % 그래프를 그립니다
    plot(x,y,'o','MarkerFacecolor','b','MarkerSize',8)
    axis([0 3 0 0.8])
    
    M(j) = getframe;
    
    % 공이 땅에 떨어지면 프로그램이 종료됩니다
    if y<=0
        break
    end
end


% 굳이 필요없는 코드인듯.. 멈추고 엔터누르면 천천히 다시 시작한다
pause
movie(M,1)


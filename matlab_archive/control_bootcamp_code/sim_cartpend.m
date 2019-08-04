% matlab ==> 도립진자의 운동을 시뮬레이션 해보는 코드
%           code from https://www.youtube.com/watch?v=qjhAAQexzLg&t=475s
clear all, close all, clc

m = 1;
M = 5;
L = 2;
g = -10;
d = 1;

tspan = 0:.1:30;
y0 = [0; 0; pi; .5];
[t,y] = ode45(@(t,y)cartpend(y,m,M,L,g,d,0),tspan,y0);

for k=1:length(t)
    drawcartpend_bw(y(k,:),m,M,L);
end

% function dy = pendcart(y,m,M,L,g,d,u)
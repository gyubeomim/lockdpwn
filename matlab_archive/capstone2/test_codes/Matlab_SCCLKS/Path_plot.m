clear all
close all
clc

Scale = 1;
% Trajectory plot %
load('PathData.mat');
plot(X*Scale,Y*Scale,'g','Linewidth',3);hold on;

% Curve fitting %
P = polyfit(X*Scale,Y*Scale,4);
x = 0 : 0.01 : 350*Scale;
y = polyval(P,x);

plot(x,y,'b','Linewidth',1.5)
xlabel('X [m]');ylabel('Y [m]');
title('Road Model');legend('Actual Path','Polyfit');
axis equal
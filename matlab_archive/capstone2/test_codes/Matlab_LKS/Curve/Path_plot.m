clear all
close all
clc

% Trajectory plot %
load('PathData.mat');
plot(X,Y,'g','Linewidth',3);hold on;

% Curve fitting %
P = polyfit(X,Y,4);
x = 0 : 0.01 : 350;
y = polyval(P,x);

plot(x,y,'b','Linewidth',1.5)
xlabel('X [m]');ylabel('Y [m]');
title('Road Model');legend('Actual Path','Polyfit');
axis equal
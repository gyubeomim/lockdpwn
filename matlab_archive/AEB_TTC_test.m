%{
    matlab ==> AEB (TTC_min based)를 구현해 본 코드
               "A Study and Analysis for Calculating the Brake-application Time of AEB Systems Considering the Gradient" 논문의 공식을 수식화해봤다
                기존 간단한 TTC 코드가 아니라 TTC_min을 추가해서 TTC < TTC_min일 경우 AEB를 작동하는 방식이다 
%}
clear, clc;

t = 0:0.1:10; % 1~10초 [s]
a_max = -8;   % 최대감가속도 [m/s^2]
v0 = 10;      % 초기속도(=상대속도) [m/s]
vrel = 10;    % 상대속도 [m/s]
L = 10;       % 목표거리 [m]

Smin = v0*t + 0.5 * a_max * t.^2;  % Smin = Minimum Deceleration Distance
Srel = L - Smin;                   % Srel = L - Smin으로 계산

TTC_min = Smin / vrel;   % TTC_min 정의
TTC = Srel / vrel;       % TTC의 정의

plot(TTC - TTC_min)  % plot해본다 TTC < TTC_min 이어야하므로 TTC - TTC_min < 0 일때만 AEB가 동작한다
grid; axis([0 40 -10 10]);
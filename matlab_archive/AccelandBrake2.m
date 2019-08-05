clear all; clc; close all;

%% 차량제원

m = 1558;       % 차량질량 kg
m10 = 1558*0.9;	% 10 percent 줄어든 차량의 질량
ee = 0.95;       % 엔진전달효율
je = 0.16;      % 엔진 질량관성
ur = 0.015;     % 구름저항계수
cd = 0.33;      % 공기저항계수 
q = 1.206;      % 공기밀도 kg/m^3
A = 1.6;        % 전투영면적 m^2
u = 1.0;        % 노면마찰계수
h = 0.54;       % 무게중심높이 m
l = 2.578;      % 휠베이스 m
g = 9.81;       % 중력가속도


%% 감속기 데이터

it1 = 3.538; it2 = 2.06; it3 = 1.404; it4 = 1.00; it5 = 0.713; it6 = 0.582;	% 
jp1 = 0.037; jp2 = 0.034; jp3 = 0.042; jp4 = 0.04; jp5 = 0.04; jp6 = 0.04;	% 
ep1 = 0.9; ep2 = 0.92; ep3 = 0.95; ep4 = 0.95; ep5 = 0.98; ep6 =0.98;		% 


%% 종감속기어 데이터
jd= 0.013;
id= 4.1;
ed= 0.99;


 %% 휠데이터
jwf= 0.009;
jwr = 0.009;
r = 0.31;


%% 엔진토크의 특성
RPM = [86.6667 173.333 433.333 750 866.667 1300 1733.33 2166.67 2600 3033.33 3466.67 3900 4333.33 4766.67 5200 5633.33 6066.67 6500];
Te = [88.744 127.544 179.536 194.892 210.248 229.696 235.904 243.456 262.664 267.304 252.232 254.952 253.6 244.64 229.368 207.416 182.704 -61.6];


for n = 1:6;
	eval(['Traction',num2str(n),' = (Te *it',num2str(n),' *id* ee * ed * ep',num2str(n),')/(1000*r);'])
end


for n = 1:6;
	eval(['Velocity',num2str(n),' = (2*pi*r*60*RPM) / (1000*id*it',num2str(n),');']);
end


%% 구름저항
Rr = ur*m*g;


%% 공기저항 
v = [0:1:300]/3.6;
Rd = 0.5 * cd * q *A * v.^2;


%% 구배저항
for n = 0:18;
	eval(['Rg',num2str(n*5),' = g*m*sin(atan(',num2str(n*5),'/100));'])
end

%% 주행저항
for n = 0:18;
		eval(['Driving_Resistance',num2str(n*5),' = (Rr+Rd+Rg',num2str(n*5),')/1000;'])
end

%% 주행성능곡선
for n = 1:6
	eval(['plot(Velocity',num2str(n),',Traction',num2str(n),');hold on;'])
end

for n = 0:18;
	eval(['plot(v*3.6,Driving_Resistance',num2str(n*5),');hold on;'])
end










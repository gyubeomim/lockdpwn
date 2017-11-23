% matlab ==> excel 데이터를 읽어와 plot하는 코드2
%                  GSR gavalnic skin reflex
%                  PPI pulse to pulse inverval
clear,clc

% excel 데이터를 읽어옵니다
filename = 'data.xlsx';
sheet = 1;

xlRange = 'F2:F8500';
ylRange = 'G2:G8500';

% excel로부터 GSR, PPI 값을 넘겨받습니다
gsr = xlsread(filename,sheet,xlRange);
gsr = gsr';

ppi = xlsread(filename,sheet,ylRange);
ppi = ppi';

% 시간을 설정하고
t = 1:8499;

% 그래프를 그립니다
subplot(2,1,1);
plot(t,gsr,'r'),grid
title('GSR, Galvalnic Skin Reflex','fontsize',15);
xlabel('total time : 272.32s','fontsize',15);
ylabel('mV','fontsize',15);

subplot(2,1,2);
plot(t,ppi,'m'),grid
title('PPI, Pulse to Pulse Interval','fontsize',15);
xlabel('total time : 272.32s','fontsize',15);
ylabel('RR interval(s)','fontsize',15);
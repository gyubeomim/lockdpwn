% matlab ==> excel 데이터를 읽어와 plot하는 코드
%                   운전하면서 안구의 움직임을 데이터화 했다
clear,clc

% excel 데이터를 읽어옵니다
filename = 'data.xlsx';
sheet = 1;

% 오른쪽 눈의 움직임
xlRange = 'A2:A8500';
ylRange = 'B2:B8500';

% 데이터를 받아서
x = xlsread(filename,sheet,xlRange);
x = -x';
y = xlsread(filename,sheet,ylRange);
y =y';

% 그래프를 그립니다
subplot(1,2,2);
plot(x,y,'bo'),grid
title('Right eye tracking','fontsize',15);
xlabel('m','fontsize',15);
ylabel('m','fontsize',15);

% 왼쪽 눈의 움직임
xlRange2 = 'C2:C8500';
ylRange2 = 'D2:D8500';

% 데이터를 받아서
a = xlsread(filename,sheet,xlRange2);
a = -a';
b = xlsread(filename,sheet,ylRange2);
b =b';

% 그래프를 그립니다
subplot(1,2,1);
plot(a,b,'ro'),grid
title('Left eye tracking','fontsize',15);
xlabel('m','fontsize',15);
ylabel('m','fontsize',15);
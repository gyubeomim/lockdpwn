% 데이터를 받아옵니다
lat = LATITUDE';
long = LONGITUDE';
speed = SPEED';
h = HEIGHT';
t = linspace(1,132,132);

h(1) = [];
speed(1) = [];
lat(1) = [];
long(1) = [];

% 각 데이터의 평균, 최대최소값, 표준편차를 구합니다.
mean(h)
max(h)
min(h)
std(h,1)

mean(speed)
max(speed)
min(speed)
std(speed,1)

mean(lat)
max(lat)
min(lat)
std(lat,1)

mean(long)
max(long)
min(long)
std(long,1)

% 각 데이터를 plot합니다.
subplot(2,2,1)
plot(t,lat,'r','linewidth',3),grid
xlabel('Time flow','fontsize',15)
ylabel('LATITUDE','fontsize',15)
title('GPS Data1','fontsize',15)

subplot(2,2,2)
plot(t,long,'g','linewidth',3),grid
xlabel('Time flow','fontsize',15)
ylabel('LONGITUDE','fontsize',15)
title('GPS Data2','fontsize',15)

subplot(2,2,3)
plot(t,speed,'b','linewidth',3),grid
xlabel('Time flow','fontsize',15)
ylabel('SPEED (km/h)','fontsize',15)
title('GPS Data3','fontsize',15)

subplot(2,2,4)
plot(t,h,'c','linewidth',3),grid
xlabel('Time flow','fontsize',15)
ylabel('HEIGHT (m)','fontsize',15)
title('GPS Data4','fontsize',15)
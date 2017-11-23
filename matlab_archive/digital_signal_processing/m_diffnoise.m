<<<<<<< HEAD
t = 0:15/1000 :15;

f1 = 0.1; % slow freq
f2 = 5; % fast freq

x1 = cos(2*pi*f1*t);
x2 = 0.2*cos(2*pi*f2*t);
x = x1 + x2;

dx1 = -2*pi*f1*sin(2*pi*f1*t);
dx2 = -2*pi*f2*0.2*cos(2*pi*f2*t);
dx = dx1 + dx2;

close all
subplot(2,2,1)
plot(t,x), ylabel('x1 + x2')

subplot(4,2,5)
plot(t,x1), ylabel('x1')

subplot(4,2,7)
plot(t,x2), ylabel('x2')
axis([-inf inf -0.3 0.3])

subplot(2,2,2)
plot(t,dx), ylabel('dx1 + dx2')

subplot(4,2,6)
plot(t,dx1), ylabel('dx1')

subplot(4,2,8)
plot(t,dx2), ylabel('dx2')

=======
t = 0:15/1000 :15;

f1 = 0.1; % slow freq
f2 = 5; % fast freq

x1 = cos(2*pi*f1*t);
x2 = 0.2*cos(2*pi*f2*t);
x = x1 + x2;

dx1 = -2*pi*f1*sin(2*pi*f1*t);
dx2 = -2*pi*f2*0.2*cos(2*pi*f2*t);
dx = dx1 + dx2;

close all
subplot(2,2,1)
plot(t,x), ylabel('x1 + x2')

subplot(4,2,5)
plot(t,x1), ylabel('x1')

subplot(4,2,7)
plot(t,x2), ylabel('x2')
axis([-inf inf -0.3 0.3])

subplot(2,2,2)
plot(t,dx), ylabel('dx1 + dx2')

subplot(4,2,6)
plot(t,dx1), ylabel('dx1')

subplot(4,2,8)
plot(t,dx2), ylabel('dx2')

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

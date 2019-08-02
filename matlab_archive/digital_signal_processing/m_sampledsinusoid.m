<<<<<<< HEAD
% m_sampledsinusoid.m

f  = input('sampling frequency [Hz] (10)     -->  ');
f1 = input('frequency of sinusoid 1 [Hz] (3) -->  ');
f2 = input('frequency of sinusoid 2 [Hz] (7) -->  ');

N = 15;   % total of N+1 points
n = 0:N; 

dt = 1/f;
t = dt*n; 

m = 30;   % multiple of points
nn = 0:N*m; 
dtt = dt/m;
tt = dtt*nn;

x1 = sin(2*pi*f1*t);
x2 = sin(2*pi*f2*t);

xx1 = sin(2*pi*f1*tt);
xx2 = sin(2*pi*f2*tt);

subplot(3,1,1); plot(tt,xx1,'b',t,x1,'bo'); title('sinusoid 1')
subplot(3,1,2); plot(tt,xx2,'r',t,x2,'ro'); title('sinusoid 2')

subplot(3,1,3); plot(tt,xx1,'b',t,x1,'bo',tt,xx2,'r',t,x2,'ro')
; title('sinusoid 1 & 2')
=======
% m_sampledsinusoid.m

f  = input('sampling frequency [Hz] (10)     -->  ');
f1 = input('frequency of sinusoid 1 [Hz] (3) -->  ');
f2 = input('frequency of sinusoid 2 [Hz] (7) -->  ');

N = 15; % total of N+1 points
n = 0:N; 

dt = 1/f;
t = dt*n; 

m = 30; % multiple of points
nn = 0:N*m; 
dtt = dt/m;
tt = dtt*nn;

x1 = sin(2*pi*f1*t);
x2 = sin(2*pi*f2*t);

xx1 = sin(2*pi*f1*tt);
xx2 = sin(2*pi*f2*tt);

subplot(3,1,1); plot(tt,xx1,'b',t,x1,'bo'); title('sinusoid 1')
subplot(3,1,2); plot(tt,xx2,'r',t,x2,'ro'); title('sinusoid 2')

subplot(3,1,3); plot(tt,xx1,'b',t,x1,'bo',tt,xx2,'r',t,x2,'ro')
; title('sinusoid 1 & 2')
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

<<<<<<< HEAD
%
% m_ccf12samples.m
%

N = 1000;
M = 50; % maximum delay for plotting
n = 0 : N-1;

% x: amplitude = random in [-0.2,0.8], freq = 12 samples per period
x = ( rand(size(n))-0.2 ) .* cos(2*pi/12*n);

% y1: amplitude = random in [-0.5,1.5], freq = 12 samples per period
% y2: amplitude = random in [-1,3], freq = 2 samples per period
y1 = ( 2*rand(size(n))-0.5 ) .* cos(2*pi/12*n + pi/3);
y2 = ( 4*rand(size(n))-1 ) .* cos(pi*n);
y = y1 + y2;

% compute CCF
ccf = xcorr( x , y , M , 'biased' );

close all

subplot(3,1,1)
bar(n,x)
xlabel('n'), ylabel('x[n]'), xlim([0,300])

subplot(3,1,2)
bar(n,y)
xlabel('n'), ylabel('y[n]'), xlim([0,300])

subplot(3,1,3)
stem( -M:M , ccf , '.-' )
xlabel('m'), ylabel('\phi_{ xy}[m]'), xlim([-M,M])
=======
%
% m_ccf12samples.m
%

N = 1000;
M = 50; % maximum delay for plotting
n = 0 : N-1;

% x: amplitude = random in [-0.2,0.8], freq = 12 samples per period
x = ( rand(size(n))-0.2 ) .* cos(2*pi/12*n);

% y1: amplitude = random in [-0.5,1.5], freq = 12 samples per period
% y2: amplitude = random in [-1,3], freq = 2 samples per period
y1 = ( 2*rand(size(n))-0.5 ) .* cos(2*pi/12*n + pi/3);
y2 = ( 4*rand(size(n))-1 ) .* cos(pi*n);
y = y1 + y2;

% compute CCF
ccf = xcorr( x , y , M , 'biased' );

close all

subplot(3,1,1)
bar(n,x)
xlabel('n'), ylabel('x[n]'), xlim([0,300])

subplot(3,1,2)
bar(n,y)
xlabel('n'), ylabel('y[n]'), xlim([0,300])

subplot(3,1,3)
stem( -M:M , ccf , '.-' )
xlabel('m'), ylabel('\phi_{ xy}[m]'), xlim([-M,M])
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

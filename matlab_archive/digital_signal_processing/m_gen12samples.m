<<<<<<< HEAD
% m_gen12samples.m
% 
% 이 프로그램은 CCF를 보기 위한 x1, x2 데이터를 만든다.
%

disp('12 samples per period의 성분이 강한 두 개의 신호 x1, x2를 만든다')

N = 1000;
n = [0 : N-1]';

% x1: amplitude = random in [-0.2,0.8], freq = 12 samples per period
x1 = ( rand(size(n))-0.2 ) .* cos(2*pi/12*n);

% x21: amplitude = random in [-0.5,1.5], freq = 12 samples per period
% x22: amplitude = random in [-1,3], freq = 2 samples per period
x21 = ( 2*rand(size(n))-0.5 ) .* cos(2*pi/12*n + pi/3);
x22 = ( 4*rand(size(n))-1 ) .* cos(pi*n);
x2 = x21 + x22;

clear N n x21 x22
=======
% m_gen12samples.m
% 
% 이 프로그램은 CCF를 보기 위한 x1, x2 데이터를 만든다.
%

disp('12 samples per period의 성분이 강한 두 개의 신호 x1, x2를 만든다')

N = 1000;
n = [0 : N-1]';

% x1: amplitude = random in [-0.2,0.8], freq = 12 samples per period
x1 = ( rand(size(n))-0.2 ) .* cos(2*pi/12*n);

% x21: amplitude = random in [-0.5,1.5], freq = 12 samples per period
% x22: amplitude = random in [-1,3], freq = 2 samples per period
x21 = ( 2*rand(size(n))-0.5 ) .* cos(2*pi/12*n + pi/3);
x22 = ( 4*rand(size(n))-1 ) .* cos(pi*n);
x2 = x21 + x22;

clear N n x21 x22
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

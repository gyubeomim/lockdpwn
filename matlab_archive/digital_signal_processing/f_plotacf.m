<<<<<<< HEAD
function [xacf,xacfM] = f_plotacf(x,M)

% 이 함수는 입력신호 x를 받아서, 이 신호의 ACF(Autocorrelation Function)을 구하고,
% 이를 plot해준다.
%
% Input
%   x: 입력 신호(길이 N)
%   M: ACF를 구할 때, m의 범위 즉, m = -M ~ M (보통 M은 N의 15%~20% 정도로 잡는 것이 적당함)
%
% Output
%   xacf: ACF of x (full length 즉 -(N-1) ~ (N-1)). 길이 2N-1
%   xacfM: ACF of x (-M ~ M 범위). 길이 2M+1

N = length(x);

n = 0 : N-1;
m = -M : M;

xacf = xcorr(x,'biased'); % full length, 즉 -(N-1) ~ (N-1)
xacfM = xcorr(x,M,'biased'); % -M to M

close all

% x를 그린다. 전 범위에 대해. n = 0 ~ N-1
subplot(2,2,1)
stem( n , x , '.-' )
xlabel('n (full range)'); ylabel('x[n]'); xlim([0 N]) 

% x를 그린다. 확대된 범위에 대해 (N이 300보다 큰 경우에만), n = 200 ~ 300
if ( N > 300 )
    subplot(2,2,3)
    stem( n , x , '.-' )
    xlabel('n (200~300)'); ylabel('x[n]'); xlim([200 300]) 
end

% ACF를 그린다. 전 범위에 대해. m = -(N-1) ~ (N-1)
subplot(2,2,2)
stem( -(N-1):(N-1) , xacf , '.-' )
xlabel('m (full range)'); ylabel('ACF, \phi_{ xx}[m]'); xlim([-N N]) 

% ACF를 그린다. 주어진 범위에 대해. m = -M ~ M
subplot(2,2,4)
stem( -M:M , xacfM , '.-' )
xlabel('m (-M ~ M)'); ylabel('ACF, \phi_{ xx}[m]'); xlim([-M M]) 
=======
function [xacf,xacfM] = f_plotacf(x,M)

% 이 함수는 입력신호 x를 받아서, 이 신호의 ACF(Autocorrelation Function)을 구하고,
% 이를 plot해준다.
%
% Input
%   x: 입력 신호(길이 N)
%   M: ACF를 구할 때, m의 범위 즉, m = -M ~ M (보통 M은 N의 15%~20% 정도로 잡는 것이 적당함)
%
% Output
%   xacf: ACF of x (full length 즉 -(N-1) ~ (N-1)). 길이 2N-1
%   xacfM: ACF of x (-M ~ M 범위). 길이 2M+1

N = length(x);

n = 0 : N-1;
m = -M : M;

xacf = xcorr(x,'biased'); % full length, 즉 -(N-1) ~ (N-1)
xacfM = xcorr(x,M,'biased'); % -M to M

close all

% x를 그린다. 전 범위에 대해. n = 0 ~ N-1
subplot(2,2,1)
stem( n , x , '.-' )
xlabel('n (full range)'); ylabel('x[n]'); xlim([0 N]) 

% x를 그린다. 확대된 범위에 대해 (N이 300보다 큰 경우에만), n = 200 ~ 300
if ( N > 300 )
    subplot(2,2,3)
    stem( n , x , '.-' )
    xlabel('n (200~300)'); ylabel('x[n]'); xlim([200 300]) 
end

% ACF를 그린다. 전 범위에 대해. m = -(N-1) ~ (N-1)
subplot(2,2,2)
stem( -(N-1):(N-1) , xacf , '.-' )
xlabel('m (full range)'); ylabel('ACF, \phi_{ xx}[m]'); xlim([-N N]) 

% ACF를 그린다. 주어진 범위에 대해. m = -M ~ M
subplot(2,2,4)
stem( -M:M , xacfM , '.-' )
xlabel('m (-M ~ M)'); ylabel('ACF, \phi_{ xx}[m]'); xlim([-M M]) 
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

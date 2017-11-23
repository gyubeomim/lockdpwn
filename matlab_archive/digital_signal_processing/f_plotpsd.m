<<<<<<< HEAD
function [xacf,Pxx] = f_plotpsd(x,M)

% 이 함수는 x[n], n=0,...,N-1 이 주어졌을 때, ACF와 PSD를 구하고,
% 이들을 plot해준다. Window는 사용되지 않는다.
%
% Input
%   x: input sequence (N-by-1)
%   M: autocorrelation구할 때, m의 범위 (-M ~ M)
%
% Output
%   xacf: autocorrelation of x (길이는 2M+1)
%   Pxx: PSD (길이는 2M+1). 길이는 2M+1이지만 M+1을 기준으로 양쪽이 대칭.

N = length(x);

% x에 대해 ACF를 구한다 (범위: -M ~ M)
xacf = xcorr(x,M,'biased');

% ACF의 DFT를 구한다.
Pxx = f_dft_center(xacf);

%%%% ACF 그래프 그린다 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all

stem( -M:M , xacf , '.-', 'filled' )
xlabel('m'); ylabel('ACF, \phi_{ xx}[m]'); xlim([ -M, M])

%%%% PSD 그래프 그린다 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure % 새로운 window를 연다

% 그림에 그릴 부분만 떼어낸다.
k = 0 : M;
Pxxk = Pxx(1:M+1); 

subplot(2,2,1)
stem(k,real(Pxxk),'fill'), ylabel('real( P_{xx}(k) )')
xlabel('k'); xlim([ 0, M])

subplot(2,2,3)
stem(k,imag(Pxxk),'fill'), ylabel('imag( P_{xx}(k) )')
xlabel([ 'k  (\Omega_k = 2\pik/(2M+1)  where  M=' , num2str(M) , ')' ]); xlim([ 0, M])

subplot(2,2,2)
stem(k,abs(Pxxk),'fill'), ylabel('| P_{xx}(k) |')
xlabel('k'); xlim([ 0, M])

subplot(2,2,4)
stem(k,angle(Pxxk)*180/pi,'fill'), ylabel('\angle P_{xx}(k) [deg]')
xlabel([ 'k  (\Omega_k = 2\pik/(2M+1)  where  M=' , num2str(M) , ')' ]); xlim([ 0, M])

=======
function [xacf,Pxx] = f_plotpsd(x,M)

% 이 함수는 x[n], n=0,...,N-1 이 주어졌을 때, ACF와 PSD를 구하고,
% 이들을 plot해준다. Window는 사용되지 않는다.
%
% Input
%   x: input sequence (N-by-1)
%   M: autocorrelation구할 때, m의 범위 (-M ~ M)
%
% Output
%   xacf: autocorrelation of x (길이는 2M+1)
%   Pxx: PSD (길이는 2M+1). 길이는 2M+1이지만 M+1을 기준으로 양쪽이 대칭.

N = length(x);

% x에 대해 ACF를 구한다 (범위: -M ~ M)
xacf = xcorr(x,M,'biased');

% ACF의 DFT를 구한다.
Pxx = f_dft_center(xacf);

%%%% ACF 그래프 그린다 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all

stem( -M:M , xacf , '.-', 'filled' )
xlabel('m'); ylabel('ACF, \phi_{ xx}[m]'); xlim([ -M, M])

%%%% PSD 그래프 그린다 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

figure % 새로운 window를 연다

% 그림에 그릴 부분만 떼어낸다.
k = 0 : M;
Pxxk = Pxx(1:M+1); 

subplot(2,2,1)
stem(k,real(Pxxk),'fill'), ylabel('real( P_{xx}(k) )')
xlabel('k'); xlim([ 0, M])

subplot(2,2,3)
stem(k,imag(Pxxk),'fill'), ylabel('imag( P_{xx}(k) )')
xlabel([ 'k  (\Omega_k = 2\pik/(2M+1)  where  M=' , num2str(M) , ')' ]); xlim([ 0, M])

subplot(2,2,2)
stem(k,abs(Pxxk),'fill'), ylabel('| P_{xx}(k) |')
xlabel('k'); xlim([ 0, M])

subplot(2,2,4)
stem(k,angle(Pxxk)*180/pi,'fill'), ylabel('\angle P_{xx}(k) [deg]')
xlabel([ 'k  (\Omega_k = 2\pik/(2M+1)  where  M=' , num2str(M) , ')' ]); xlim([ 0, M])

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

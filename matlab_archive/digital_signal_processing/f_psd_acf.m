<<<<<<< HEAD
function [xacf,Pxx] = f_psd_acf(x,M)

% 이 함수는 x[n], n=0,...,N-1 이 주어졌을 때, ACF와 PSD를 구한다.
% PSD를 구할 때 window는 사용되지 않는다.
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

=======
function [xacf,Pxx] = f_psd_acf(x,M)

% 이 함수는 x[n], n=0,...,N-1 이 주어졌을 때, ACF와 PSD를 구한다.
% PSD를 구할 때 window는 사용되지 않는다.
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

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

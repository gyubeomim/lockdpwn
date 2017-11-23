<<<<<<< HEAD
function [xacv,Pxx] = f_psd_acv(x,M)

% 이 함수는 기본적으로 f_psd와 동일함. 단 f_psd는 ACF를 이용하고,
% 이 함수는 autocovariance를 이용하여, PSD를 구함.
%
% Input
%   x: input sequence (N-by-1)
%   M: autocovariance구할 때, m의 범위 (-M ~ M)
%
% Output
%   xacv: autocovariance of x (길이는 2M+1)
%   Pxx: PSD (길이는 2M+1). 길이는 2M+1이지만 M+1을 기준으로 양쪽이 대칭.

N = length(x);

% x에 대해 ACV를 구한다 (범위: -M ~ M)
xacv = xcov(x,M,'biased');

% ACF의 DFT를 구한다.
Pxx = f_dft_center(xacv);
=======
function [xacv,Pxx] = f_psd_acv(x,M)

% 이 함수는 기본적으로 f_psd와 동일함. 단 f_psd는 ACF를 이용하고,
% 이 함수는 autocovariance를 이용하여, PSD를 구함.
%
% Input
%   x: input sequence (N-by-1)
%   M: autocovariance구할 때, m의 범위 (-M ~ M)
%
% Output
%   xacv: autocovariance of x (길이는 2M+1)
%   Pxx: PSD (길이는 2M+1). 길이는 2M+1이지만 M+1을 기준으로 양쪽이 대칭.

N = length(x);

% x에 대해 ACV를 구한다 (범위: -M ~ M)
xacv = xcov(x,M,'biased');

% ACF의 DFT를 구한다.
Pxx = f_dft_center(xacv);
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

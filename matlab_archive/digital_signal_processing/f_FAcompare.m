<<<<<<< HEAD
function f_FAcompare(x,M)

% 이 함수는 4가지의 주파수분석을 위한 값을 비교하고, 그림을 그려준다.
%  frequecny response (FT of x[n])
%  PSD 1 (autocorrelation 사용한 PSD)
%  PSD 2 (autocovariance 사용한 PSD)
%  periodogram
%
% Input
%   x: 입력 신호(길이 N)
%   M: ACF를 구할 때, m의 범위 즉, m = -M ~ M (보통 M은 N의 15%~20% 정도로 잡는 것이 적당함)

N = length(x);

%%  frequecny response (FT of x[n])
X = f_dft(x); % 복소수, 길이 N

% 그림을 위한 x축 (0부터 2pi 까지)
xX = [0 : N-1] / (N-1); 

%%  PSD 1 (autocorrelation 사용한 PSD)
[xacf1,Pxx1] = f_psd_acf(x,M); % 실수, 길이 2M+1

% 그림을 위한 x축 (0부터 2pi 까지)
xPxx1 = [0 : 2*M] / (2*M);

%%  PSD 2 (autocovariance 사용한 PSD)
[xacf2,Pxx2] = f_psd_acv(x,M); % 실수, 길이 2M+1

% 그림을 위한 x축 (0부터 2pi 까지)
xPxx2 = xPxx1;

%%  periodogram
Pxx3 = f_periodogram(x); % 실수, 길이 N

% 그림을 위한 x축 (0부터 2pi 까지)
xPxx3 = xX;

%% Plot

close all

subplot(2,2,1)
plot(xX,abs(X))
ylabel('| X(\Omega) |'), xlabel('\Omega ( x 2\pi )'), xlim([-0.02 1.02])
title('Frequency Spectrum')

subplot(2,2,3)
plot(xPxx1,Pxx1)
ylabel('| P_{xx} (\Omega) |'), xlabel('\Omega ( x 2\pi )'), xlim([-0.02 1.02])
title('PSD based on ACF')

subplot(2,2,2)
plot(xPxx3,Pxx3)
ylabel('| P''_{xx} (\Omega) |'), xlabel('\Omega ( x 2\pi )'), xlim([-0.02 1.02])
title('Periodogram')

subplot(2,2,4)
plot(xPxx2,Pxx2)
ylabel('| P_{xx} (\Omega) |'), xlabel('\Omega ( x 2\pi )'), xlim([-0.02 1.02])
title('PSD based on ACV')

% %% Plot
% 
% subplot(1,3,3)
% plot(xX,abs(X),xPxx1,Pxx1,xPxx2,Pxx2,xPxx3,Pxx3)
% xlabel('\Omega (x pi)')
% legend('Freq Spectrum','ACF-based PSD','ACV-based PSD','Periodogram')

=======
function f_FAcompare(x,M)

% 이 함수는 4가지의 주파수분석을 위한 값을 비교하고, 그림을 그려준다.
%  frequecny response (FT of x[n])
%  PSD 1 (autocorrelation 사용한 PSD)
%  PSD 2 (autocovariance 사용한 PSD)
%  periodogram
%
% Input
%   x: 입력 신호(길이 N)
%   M: ACF를 구할 때, m의 범위 즉, m = -M ~ M (보통 M은 N의 15%~20% 정도로 잡는 것이 적당함)

N = length(x);

%%  frequecny response (FT of x[n])
X = f_dft(x); % 복소수, 길이 N

% 그림을 위한 x축 (0부터 2pi 까지)
xX = [0 : N-1] / (N-1); 

%%  PSD 1 (autocorrelation 사용한 PSD)
[xacf1,Pxx1] = f_psd_acf(x,M); % 실수, 길이 2M+1

% 그림을 위한 x축 (0부터 2pi 까지)
xPxx1 = [0 : 2*M] / (2*M);

%%  PSD 2 (autocovariance 사용한 PSD)
[xacf2,Pxx2] = f_psd_acv(x,M); % 실수, 길이 2M+1

% 그림을 위한 x축 (0부터 2pi 까지)
xPxx2 = xPxx1;

%%  periodogram
Pxx3 = f_periodogram(x); % 실수, 길이 N

% 그림을 위한 x축 (0부터 2pi 까지)
xPxx3 = xX;

%% Plot

close all

subplot(2,2,1)
plot(xX,abs(X))
ylabel('| X(\Omega) |'), xlabel('\Omega ( x 2\pi )'), xlim([-0.02 1.02])
title('Frequency Spectrum')

subplot(2,2,3)
plot(xPxx1,Pxx1)
ylabel('| P_{xx} (\Omega) |'), xlabel('\Omega ( x 2\pi )'), xlim([-0.02 1.02])
title('PSD based on ACF')

subplot(2,2,2)
plot(xPxx3,Pxx3)
ylabel('| P''_{xx} (\Omega) |'), xlabel('\Omega ( x 2\pi )'), xlim([-0.02 1.02])
title('Periodogram')

subplot(2,2,4)
plot(xPxx2,Pxx2)
ylabel('| P_{xx} (\Omega) |'), xlabel('\Omega ( x 2\pi )'), xlim([-0.02 1.02])
title('PSD based on ACV')

% %% Plot
% 
% subplot(1,3,3)
% plot(xX,abs(X),xPxx1,Pxx1,xPxx2,Pxx2,xPxx3,Pxx3)
% xlabel('\Omega (x pi)')
% legend('Freq Spectrum','ACF-based PSD','ACV-based PSD','Periodogram')

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

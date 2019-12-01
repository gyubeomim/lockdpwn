<<<<<<< HEAD
function ccf = f_plotccf(x1,x2,M)

% 이 함수는 두 sequence x1, x2 의 cross-correlation function을 구하고, 그림을 그린다.
%
% Input
%   x1, x2: input sequences (N-by-1)
%   M: cross ocorrelation구할 때, m의 범위 (-M ~ M)
%
% Output
%   ccf: cross correlation of x (길이는 2M+1)

%% 초기화

N = length(x1);
n = 0 : N-1;

%% compute CCF
ccf = f_ccf(x1,x2,M);

%% 그림 그린다.

close all

subplot(3,1,1)
stem(n,x1,'.-')
xlabel('n'), ylabel('x_1[n]'), xlim([0, min(N-1,300)])

subplot(3,1,2)
stem(n,x2,'.-')
xlabel('n'), ylabel('x_2[n]'), xlim([0, min(N-1,300)])

subplot(3,1,3)
stem( -M:M , ccf , '.-' )
xlabel('m'), ylabel('\phi_{ xy}[m]'), xlim([-M,M])




=======
function ccf = f_plotccf(x1,x2,M)

% 이 함수는 두 sequence x1, x2 의 cross-correlation function을 구하고, 그림을 그린다.
%
% Input
%   x1, x2: input sequences (N-by-1)
%   M: cross ocorrelation구할 때, m의 범위 (-M ~ M)
%
% Output
%   ccf: cross correlation of x (길이는 2M+1)

%% 초기화

N = length(x1);
n = 0 : N-1;

%% compute CCF
ccf = f_ccf(x1,x2,M);

%% 그림 그린다.

close all

subplot(3,1,1)
stem(n,x1,'.-')
xlabel('n'), ylabel('x_1[n]'), xlim([0, min(N-1,300)])

subplot(3,1,2)
stem(n,x2,'.-')
xlabel('n'), ylabel('x_2[n]'), xlim([0, min(N-1,300)])

subplot(3,1,3)
stem( -M:M , ccf , '.-' )
xlabel('m'), ylabel('\phi_{ xy}[m]'), xlim([-M,M])




>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

<<<<<<< HEAD
function [X] = f_dft_center(x)

% 이 함수는 주어진 x(1:N)이 
% x[0] ~ x[N-1]로 주어진 것이 아니라
% x[-M], ... , x[0], ..., x[M]으로 주어진 경우, DFT를 구한다.
% x의 갯수는 반드시 홀수이어야 한다.
% x가 n=0일 중심으로 꼭 대칭일 필요는 없다.
%
% Input
%   x: input sequence with odd-number length (say, N)
%
% Output
%   X: DFT of X (length N). 
%      X는 N의 절반에 대해 대칭이기 때문에 사실은 이걸 다 볼 필요 없다

N = length(x);
if ( N/2 == floor(N/2) ) % x의 갯수가 짝수이면 error
    error('N must be an odd number')
end
M = (N-1) / 2;

X = [];
WN = exp(-1j*2*pi/N);

% 아래에서 구해지는 X는 -M ~ M의 범위가 아니고 0 ~ 2M+1 의 범위임.
% -M ~ M 범위로 구할 수도 있지만 FT를 볼 때 k=0 부터 보는 경우가 많으므로.
for k = 1 : N
    Xk = 0;
    for m = -M : M
        n = m + M + 1;
        pow = (k-1)*m;
        Xk = Xk + x(n)*WN^pow;
    end
    
    X = [X; Xk];
end

% change near-zero values to exactly zero to get correct phase
myzero = 1e-10;
Xr = real(X) .* (abs(real(X)) > myzero);
Xi = imag(X) .* (abs(imag(X)) > myzero);
=======
function [X] = f_dft_center(x)

% 이 함수는 주어진 x(1:N)이 
% x[0] ~ x[N-1]로 주어진 것이 아니라
% x[-M], ... , x[0], ..., x[M]으로 주어진 경우, DFT를 구한다.
% x의 갯수는 반드시 홀수이어야 한다.
% x가 n=0일 중심으로 꼭 대칭일 필요는 없다.
%
% Input
%   x: input sequence with odd-number length (say, N)
%
% Output
%   X: DFT of X (length N). 
%      X는 N의 절반에 대해 대칭이기 때문에 사실은 이걸 다 볼 필요 없다

N = length(x);
if ( N/2 == floor(N/2) ) % x의 갯수가 짝수이면 error
    error('N must be an odd number')
end
M = (N-1) / 2;

X = [];
WN = exp(-1j*2*pi/N);

% 아래에서 구해지는 X는 -M ~ M의 범위가 아니고 0 ~ 2M+1 의 범위임.
% -M ~ M 범위로 구할 수도 있지만 FT를 볼 때 k=0 부터 보는 경우가 많으므로.
for k = 1 : N
    Xk = 0;
    for m = -M : M
        n = m + M + 1;
        pow = (k-1)*m;
        Xk = Xk + x(n)*WN^pow;
    end
    
    X = [X; Xk];
end

% change near-zero values to exactly zero to get correct phase
myzero = 1e-10;
Xr = real(X) .* (abs(real(X)) > myzero);
Xi = imag(X) .* (abs(imag(X)) > myzero);
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
X = Xr + 1i*Xi;
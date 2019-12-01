<<<<<<< HEAD
function ccf = f_ccf(x1,x2,M)

% 이 함수는 두 sequence x1, x2 의 cross-correlation function을 구한다.
%
% Input
%   x1, x2: input sequences (N-by-1)
%   M: cross ocorrelation구할 때, m의 범위 (-M ~ M)
%
% Output
%   ccf: cross correlation of x (길이는 2M+1)

% compute CCF
ccf = xcorr( x1 , x2 , M , 'biased' );




=======
function ccf = f_ccf(x1,x2,M)

% 이 함수는 두 sequence x1, x2 의 cross-correlation function을 구한다.
%
% Input
%   x1, x2: input sequences (N-by-1)
%   M: cross ocorrelation구할 때, m의 범위 (-M ~ M)
%
% Output
%   ccf: cross correlation of x (길이는 2M+1)

% compute CCF
ccf = xcorr( x1 , x2 , M , 'biased' );




>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

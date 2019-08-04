<<<<<<< HEAD
function Pxx = f_periodogram(x)

N = length(x);

% 먼저 DFT를 한다.
X = f_dft(x); % 복소수로 값이 나옴.

=======
function Pxx = f_periodogram(x)

N = length(x);

% 먼저 DFT를 한다.
X = f_dft(x); % 복소수로 값이 나옴.

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
Pxx = (abs(X).^2)/N;
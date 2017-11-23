<<<<<<< HEAD
function ak = f_dfs(xn)
%
% function ak = dfs(xn)
%
% Input
%  xn: one period (N) of real signal
%
% Output
%  ak: coefficients (complex) of discrete fourier series of length N

N = length(xn);
n = 0 : N-1;

ak = [];

for k = 0 : N-1
    %a = 1/N * sum(xn .* exp(-2j*pi*k*n/N));
    a = 1/N * dot(xn,exp(-2j*pi*k*n/N)); % dot product
    ak = [ak; a];
end

% find small value and change it to 0 (otherwise you can get wrong angle)
ak_r = real(ak);
ak_i = imag(ak);
ak_mean = (sum(abs(ak_r)) + sum(abs(ak_i)))/2; % sum(ak_r) and sum(ak_i) are zero. Don't drop abs.
small = ak_mean * 1.e-8;

ak_r( abs(ak_r) <= small ) = 0;
ak_i( abs(ak_i) <= small ) = 0;
ak = ak_r + 1i*ak_i;
=======
function ak = f_dfs(xn)
%
% function ak = dfs(xn)
%
% Input
%  xn: one period (N) of real signal
%
% Output
%  ak: coefficients (complex) of discrete fourier series of length N

N = length(xn);
n = 0 : N-1;

ak = [];

for k = 0 : N-1
    %a = 1/N * sum(xn .* exp(-2j*pi*k*n/N));
    a = 1/N * dot(xn,exp(-2j*pi*k*n/N)); % dot product
    ak = [ak; a];
end

% find small value and change it to 0 (otherwise you can get wrong angle)
ak_r = real(ak);
ak_i = imag(ak);
ak_mean = (sum(abs(ak_r)) + sum(abs(ak_i)))/2; % sum(ak_r) and sum(ak_i) are zero. Don't drop abs.
small = ak_mean * 1.e-8;

ak_r( abs(ak_r) <= small ) = 0;
ak_i( abs(ak_i) <= small ) = 0;
ak = ak_r + 1i*ak_i;
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

<<<<<<< HEAD
function ak = f_dfs0(xn)
%
% function ak = f_dfs0(xn)
%
% Input
%  xn: one period (N) of real signal starting from n=0
%
% Output
%  ak: coefficients (complex) of discrete fourier series of length N

N = length(xn);
n = 0 : N-1;

ak = [];
for k = 0 : N-1
    %a = 1/N * sum(xn .* exp(-2j*pi*k*n/N));
    a = 1/N * dot(xn,exp(-2j*pi*k*n/N)); % allows any 1-D vector shape
    ak = [ak; a];
end
=======
function ak = f_dfs0(xn)
%
% function ak = f_dfs0(xn)
%
% Input
%  xn: one period (N) of real signal starting from n=0
%
% Output
%  ak: coefficients (complex) of discrete fourier series of length N

N = length(xn);
n = 0 : N-1;

ak = [];
for k = 0 : N-1
    %a = 1/N * sum(xn .* exp(-2j*pi*k*n/N));
    a = 1/N * dot(xn,exp(-2j*pi*k*n/N)); % allows any 1-D vector shape
    ak = [ak; a];
end
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

<<<<<<< HEAD
N = 8;
n = 0:N-1;

x = 1 + sin(pi*n/4) + 2*cos(pi*n/2);

ak = f_dfs(x);
rak = real(ak);
iak = imag(ak);

subplot(2,1,1)
stem([n-N,n],[rak;rak]) % show 2 periods
ylabel('real(ak)')

subplot(2,1,2)
stem([n-N,n],[iak;iak]) % show 2 periods
ylabel('imag(ak)')
=======
N = 8;
n = 0:N-1;

x = 1 + sin(pi*n/4) + 2*cos(pi*n/2);

ak = f_dfs(x);
rak = real(ak);
iak = imag(ak);

subplot(2,1,1)
stem([n-N,n],[rak;rak]) % show 2 periods
ylabel('real(ak)')

subplot(2,1,2)
stem([n-N,n],[iak;iak]) % show 2 periods
ylabel('imag(ak)')
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

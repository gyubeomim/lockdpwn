<<<<<<< HEAD
function f_plotdfs(xn)

ak = f_dfs(xn);
n = 0 : length(ak)-1;

subplot(2,2,1)
stem(n,real(ak)); ylabel('real(a_{k})')

subplot(2,2,3)
stem(n,imag(ak)); ylabel('imag(a_{k})')

subplot(2,2,2)
stem(n,abs(ak)); ylabel('|a_{k}|)')

subplot(2,2,4)
stem(n,angle(ak)*180/pi); ylabel('\angle a_{k}')
=======
function f_plotdfs(xn)

ak = f_dfs(xn);
n = 0 : length(ak)-1;

subplot(2,2,1)
stem(n,real(ak)); ylabel('real(a_{k})')

subplot(2,2,3)
stem(n,imag(ak)); ylabel('imag(a_{k})')

subplot(2,2,2)
stem(n,abs(ak)); ylabel('|a_{k}|)')

subplot(2,2,4)
stem(n,angle(ak)*180/pi); ylabel('\angle a_{k}')
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

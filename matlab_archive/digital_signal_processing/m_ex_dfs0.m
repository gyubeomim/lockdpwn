<<<<<<< HEAD

n = 0:6

x = [2 1 -2 3 -1 -1 1]
ak = f_dfs0(x)

close all

% ±ØÁÂÇ¥°è
subplot(2,2,1)
stem(n,abs(ak)); ylabel('|a_{k}|')
title('a_k in polar coordinate')
subplot(2,2,3)
stem(n,angle(ak)*180/pi); ylabel('\angle a_{k} [deg]')
xlabel('k')

% Á÷±³ÁÂÇ¥°è
subplot(2,2,2)
stem(n,real(ak)); ylabel('Re(a_{k})')
title('a_k in rectangular coordinate')
subplot(2,2,4)
stem(n,imag(ak)); ylabel('Im(a_{k})')
xlabel('k')
=======

n = 0:6

x = [2 1 -2 3 -1 -1 1]
ak = f_dfs0(x)

close all

% ±ØÁÂÇ¥°è
subplot(2,2,1)
stem(n,abs(ak)); ylabel('|a_{k}|')
title('a_k in polar coordinate')
subplot(2,2,3)
stem(n,angle(ak)*180/pi); ylabel('\angle a_{k} [deg]')
xlabel('k')

% Á÷±³ÁÂÇ¥°è
subplot(2,2,2)
stem(n,real(ak)); ylabel('Re(a_{k})')
title('a_k in rectangular coordinate')
subplot(2,2,4)
stem(n,imag(ak)); ylabel('Im(a_{k})')
xlabel('k')
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

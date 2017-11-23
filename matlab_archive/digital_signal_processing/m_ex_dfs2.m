<<<<<<< HEAD
N = 64;
n = 0:N-1;

x = sin(2*pi*n/64) + cos(2*pi*n/16) + 0.6*cos(2*pi*n/8) + 0.5*sin(2*pi*n/4);

ak = f_dfs(x);
mak = abs(ak);
aak = angle(ak);

subplot(2,1,1)
stem(n,mak); ylabel('magnitude of ak')

subplot(2,1,2)
stem(n,aak); ylabel('angle of ak')

=======
N = 64;
n = 0:N-1;

x = sin(2*pi*n/64) + cos(2*pi*n/16) + 0.6*cos(2*pi*n/8) + 0.5*sin(2*pi*n/4);

ak = f_dfs(x);
mak = abs(ak);
aak = angle(ak);

subplot(2,1,1)
stem(n,mak); ylabel('magnitude of ak')

subplot(2,1,2)
stem(n,aak); ylabel('angle of ak')

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

<<<<<<< HEAD
% m_ma10.m

n = 0:300;

x = sin(2*pi*n/60)+sin(2*pi*n/10);
x = x .* ( (n >= 60) & (n <= 240) );

h = 0.1*ones(1,10);

y = conv(x,h);

subplot(2,1,1)
stem(n,x,'.')

subplot(2,1,2)
stem(n,y(1:length(n)),'.')

=======
% m_ma10.m

n = 0:300;

x = sin(2*pi*n/60)+sin(2*pi*n/10);
x = x .* ( (n >= 60) & (n <= 240) );

h = 0.1*ones(1,10);

y = conv(x,h);

subplot(2,1,1)
stem(n,x,'.')

subplot(2,1,2)
stem(n,y(1:length(n)),'.')

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

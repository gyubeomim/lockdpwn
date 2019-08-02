<<<<<<< HEAD
% m_dfs_sampledcos.m

M = input('Type number of cycles of cosine in 1 period (ex. 1, 2, 2.5) -->  ');

mcycle = 12; % # of samples to plot per one period of cosine
N = round(mcycle*M); % # of samples per one period
n = 0 : N-1;
nn = [n n+N n+2*N]; % 3 periods 

x1 = cos(2*pi/mcycle*[0:mcycle-1]); % one cycle of sinusoid

xn = repmat(x1,1,ceil(M));
xn = xn(1:N);

ak = f_dfs(xn);
xnn = [xn xn xn];

subplot(3,1,1)
stem(nn,xnn,'r','.'); 
title([num2str(M),' cycles of sinusoid in 1 period of signal'])
hold on
stem(n,xn,'b','.') 
hold off

subplot(3,2,3)
stem(n,abs(ak),'.'); ylabel('magnitude(ak)')

subplot(3,2,5)
stem(n,angle(ak)*180/pi,'.'); ylabel('angle(ak)')

subplot(3,2,4)
stem(n,real(ak),'.'); ylabel('real(ak)')

subplot(3,2,6)
stem(n,imag(ak),'.'); ylabel('imag(ak)')

=======
% m_dfs_sampledcos.m

M = input('Type number of cycles of cosine in 1 period (ex. 1, 2, 2.5) -->  ');

mcycle = 12; % # of samples to plot per one period of cosine
N = round(mcycle*M); % # of samples per one period
n = 0 : N-1;
nn = [n n+N n+2*N]; % 3 periods 

x1 = cos(2*pi/mcycle*[0:mcycle-1]); % one cycle of sinusoid

xn = repmat(x1,1,ceil(M));
xn = xn(1:N);

ak = f_dfs(xn);
xnn = [xn xn xn];

subplot(3,1,1)
stem(nn,xnn,'r','.'); 
title([num2str(M),' cycles of sinusoid in 1 period of signal'])
hold on
stem(n,xn,'b','.') 
hold off

subplot(3,2,3)
stem(n,abs(ak),'.'); ylabel('magnitude(ak)')

subplot(3,2,5)
stem(n,angle(ak)*180/pi,'.'); ylabel('angle(ak)')

subplot(3,2,4)
stem(n,real(ak),'.'); ylabel('real(ak)')

subplot(3,2,6)
stem(n,imag(ak),'.'); ylabel('imag(ak)')

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

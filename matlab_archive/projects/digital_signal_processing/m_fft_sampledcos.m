<<<<<<< HEAD

M = input('Type number of cycles of cosine  -->  ');
mcycle = input('Type # of samples per one period of cosine -->  ');

N = round(mcycle*M); % # of samples per one period
n = 0 : N-1;
nn = [n n+N n+2*N]; % 3 periods 

x1 = cos(2*pi/mcycle*[0:mcycle-1]); % one cycle of sinusoid

xn = repmat(x1,1,ceil(M));
xn = xn(1:N);

close all
f_showfft(xn)

stitle = {[num2str(M),' cycles of cosine in 1 period of signal'] ; ...
          [num2str(mcycle),' samples per one period of cosine'] };
subplot(3,1,1)
title(stitle)



=======

M = input('Type number of cycles of cosine  -->  ');
mcycle = input('Type # of samples per one period of cosine -->  ');

N = round(mcycle*M); % # of samples per one period
n = 0 : N-1;
nn = [n n+N n+2*N]; % 3 periods 

x1 = cos(2*pi/mcycle*[0:mcycle-1]); % one cycle of sinusoid

xn = repmat(x1,1,ceil(M));
xn = xn(1:N);

close all
f_showfft(xn)

stitle = {[num2str(M),' cycles of cosine in 1 period of signal'] ; ...
          [num2str(mcycle),' samples per one period of cosine'] };
subplot(3,1,1)
title(stitle)



>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

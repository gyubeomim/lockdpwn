<<<<<<< HEAD
% this program shows freq components contained in a periodic signal

N = input('Type period N (try not too big number) --> ');

nn = floor(N/2) + 1; % total number of freq components
Omega = 2*pi/N; % 1st harmonic
n = 0 : N-1;


close all
for i = 0 : floor(N/2)
    
    x = cos(i*Omega*n);
       
    subplot(nn,1,i+1)
    stem(n,x,'fill')
    %axis off
    ylabel([int2str(i),'-harmo'])
    
=======
% this program shows freq components contained in a periodic signal

N = input('Type period N (try not too big number) --> ');

nn = floor(N/2) + 1; % total number of freq components
Omega = 2*pi/N; % 1st harmonic
n = 0 : N-1;


close all
for i = 0 : floor(N/2)
    
    x = cos(i*Omega*n);
       
    subplot(nn,1,i+1)
    stem(n,x,'fill')
    %axis off
    ylabel([int2str(i),'-harmo'])
    
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
end
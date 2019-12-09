<<<<<<< HEAD
function f_plotdft(x)

% This function plots DFT of a given sequence x.
% This function calls f_dft to compute DFT.

N = length(x);
if ( N > 100 )
    disp('It may take some time to compute DFT...')
end

kmax = floor(N/2); % if N is an odd number, kmax becomes (N-1)/2
k = 0 : kmax;

X = f_dft(x);
Xk = X(1:kmax+1);

close all

subplot(2,2,1)
stem(k,real(Xk),'fill'), ylabel('real( X(k) )')
xlabel('k')

subplot(2,2,3)
stem(k,imag(Xk),'fill'), ylabel('imag( X(k) )')
xlabel([ 'k  (\Omega_k = 2\pik/N  where  N=' , num2str(N) , ')' ])

subplot(2,2,2)
stem(k,abs(Xk),'fill'), ylabel('| X(k) |')
xlabel('k')

subplot(2,2,4)
stem(k,angle(Xk)*180/pi,'fill'), ylabel('\angle X(k) [deg]')
xlabel([ 'k  (\Omega_k = 2\pik/N  where  N=' , num2str(N) , ')' ])

=======
function f_plotdft(x)

% This function plots DFT of a given sequence x.
% This function calls f_dft to compute DFT.

N = length(x);
if ( N > 100 )
    disp('It may take some time to compute DFT...')
end

kmax = floor(N/2); % if N is an odd number, kmax becomes (N-1)/2
k = 0 : kmax;

X = f_dft(x);
Xk = X(1:kmax+1);

close all

subplot(2,2,1)
stem(k,real(Xk),'fill'), ylabel('real( X(k) )')
xlabel('k')

subplot(2,2,3)
stem(k,imag(Xk),'fill'), ylabel('imag( X(k) )')
xlabel([ 'k  (\Omega_k = 2\pik/N  where  N=' , num2str(N) , ')' ])

subplot(2,2,2)
stem(k,abs(Xk),'fill'), ylabel('| X(k) |')
xlabel('k')

subplot(2,2,4)
stem(k,angle(Xk)*180/pi,'fill'), ylabel('\angle X(k) [deg]')
xlabel([ 'k  (\Omega_k = 2\pik/N  where  N=' , num2str(N) , ')' ])

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

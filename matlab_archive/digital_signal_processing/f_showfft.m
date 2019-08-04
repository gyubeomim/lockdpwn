<<<<<<< HEAD
function f_showfft(x)

N = length(x);

X_original = fft(x);

% find small value and change it to 0 (otherwise you can get wrong angle)
realX = real(X_original);
imagX = imag(X_original);
meanX = (sum(abs(realX)) + sum(abs(imagX)))/2; % sum(realX) and sum(imagX) are zero. Don't drop abs.
small = meanX * 1.e-8;

realX( abs(realX) <= small ) = 0;
imagX( abs(imagX) <= small ) = 0;
X = realX + 1i*imagX;

clf

subplot(3,1,1)
M = 3; % # of cycles to display
n = 0 : N-1;
nn = 0 : M*N-1;
if ( iscolumn(x) ); x = x'; end
plot(nn,repmat(x,1,M),'c.-',n,x,'r.-')
xlabel('n')
ylabel('x[n]')

subplot(3,2,3)
stem(n,abs(X))
xlabel('k'); ylabel('|X(k)|')

subplot(3,2,5)
stem(n,angle(X)*180/pi)
xlabel('k'); ylabel('\angleX(k) [deg]')

subplot(3,2,4)
stem(n,real(X))
xlabel('k'); ylabel('real[X(k)]')

subplot(3,2,6)
stem(n,imag(X))
xlabel('k'); ylabel('imag[X(k)]')
=======
function f_showfft(x)

N = length(x);

X_original = fft(x);

% find small value and change it to 0 (otherwise you can get wrong angle)
realX = real(X_original);
imagX = imag(X_original);
meanX = (sum(abs(realX)) + sum(abs(imagX)))/2; % sum(realX) and sum(imagX) are zero. Don't drop abs.
small = meanX * 1.e-8;

realX( abs(realX) <= small ) = 0;
imagX( abs(imagX) <= small ) = 0;
X = realX + 1i*imagX;

clf

subplot(3,1,1)
M = 3; % # of cycles to display
n = 0 : N-1;
nn = 0 : M*N-1;
if ( iscolumn(x) ); x = x'; end
plot(nn,repmat(x,1,M),'c.-',n,x,'r.-')
xlabel('n')
ylabel('x[n]')

subplot(3,2,3)
stem(n,abs(X))
xlabel('k'); ylabel('|X(k)|')

subplot(3,2,5)
stem(n,angle(X)*180/pi)
xlabel('k'); ylabel('\angleX(k) [deg]')

subplot(3,2,4)
stem(n,real(X))
xlabel('k'); ylabel('real[X(k)]')

subplot(3,2,6)
stem(n,imag(X))
xlabel('k'); ylabel('imag[X(k)]')
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

<<<<<<< HEAD
function X = f_dft(x)

N = length(x);
X = [];
WN = exp(-1j*2*pi/N);

for k = 1:N
    
    Xk = 0;
    for n = 1:N
        pow = (n-1)*(k-1);
        Xk = Xk + x(n)*WN^pow;
    end
    
    X = [X; Xk];
end

% change near-zero values to exactly zero to get correct phase
myzero = 1e-10;
Xr = real(X) .* (abs(real(X)) > myzero);
Xi = imag(X) .* (abs(imag(X)) > myzero);
=======
function X = f_dft(x)

N = length(x);
X = [];
WN = exp(-1j*2*pi/N);

for k = 1:N
    
    Xk = 0;
    for n = 1:N
        pow = (n-1)*(k-1);
        Xk = Xk + x(n)*WN^pow;
    end
    
    X = [X; Xk];
end

% change near-zero values to exactly zero to get correct phase
myzero = 1e-10;
Xr = real(X) .* (abs(real(X)) > myzero);
Xi = imag(X) .* (abs(imag(X)) > myzero);
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
X = Xr + 1i*Xi;
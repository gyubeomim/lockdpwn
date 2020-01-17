<<<<<<< HEAD
N = input('Type N -->  ');
W = zeros(N);
wn = exp(-1j*2*pi/N);

for k = 1:N
    for n = 1:N
        pow = (n-1)*(k-1);
        wkn = wn^pow;
        if ( abs(real(wkn)) < 1e-8 ) wkn = imag(wkn); end
        if ( abs(imag(wkn)) < 1e-8 ) wkn = real(wkn); end
        W(k,n) = wkn;
    end
end

disp(['W_N^kn matrix when N = ',int2str(N)])
disp(W)
=======
N = input('Type N -->  ');
W = zeros(N);
wn = exp(-1j*2*pi/N);

for k = 1:N
    for n = 1:N
        pow = (n-1)*(k-1);
        wkn = wn^pow;
        if ( abs(real(wkn)) < 1e-8 ) wkn = imag(wkn); end
        if ( abs(imag(wkn)) < 1e-8 ) wkn = real(wkn); end
        W(k,n) = wkn;
    end
end

disp(['W_N^kn matrix when N = ',int2str(N)])
disp(W)
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

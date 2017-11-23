<<<<<<< HEAD
% m_pz_chebyshev.m

disp(' ')
disp('This program shows pole/zero of digital chebyshev LPF.')
disp(' ')

n = input('Type n, filter order (ex. 10) -->  ');
Omega1 = input('Type Omega1, cutoff freq (ex. pi/3) -->  ');
delta  = input('Type delta, passband ripple (ex. 0.1) -->  ');

zero = -ones(n,1); % n zeros at z=-1

tan2  = tan(Omega1/2);
m = [0 : 2*n-1]'; % col vector

if ( ceil(n/2) == n/2 ) % when n is even
    phi = (2*m+1) * pi / (2*n); % col vector
else % when n is odd
    phi = m * pi / n; % col vector
end
    
sphi = sin(phi);
cphi = cos(phi);

epsilon = sqrt(1/(1-delta)^2 - 1);
%epsilon = sqrt(1/(1-delta) - 1);
c = epsilon^(-1) + sqrt(1 + + epsilon^(-2));
a = 0.5*(c^(1/n) - c^(-1/n));
b = 0.5*(c^(1/n) + c^(-1/n));

d = (1-a*tan2*cphi).^2 + (b*tan2*sphi).^2;
    
pole = (2*(1-a*tan2*cphi)./d-1)  +  1j*2*b*tan2*sphi;
%pole = pole(abs(pole) <= 1); % only those inside unit circle

zplane(zero,pole)

zero
pole

% disp(' ')
% disp('zeros      poles')
=======
% m_pz_chebyshev.m

disp(' ')
disp('This program shows pole/zero of digital chebyshev LPF.')
disp(' ')

n = input('Type n, filter order (ex. 10) -->  ');
Omega1 = input('Type Omega1, cutoff freq (ex. pi/3) -->  ');
delta  = input('Type delta, passband ripple (ex. 0.1) -->  ');

zero = -ones(n,1); % n zeros at z=-1

tan2  = tan(Omega1/2);
m = [0 : 2*n-1]'; % col vector

if ( ceil(n/2) == n/2 ) % when n is even
    phi = (2*m+1) * pi / (2*n); % col vector
else % when n is odd
    phi = m * pi / n; % col vector
end
    
sphi = sin(phi);
cphi = cos(phi);

epsilon = sqrt(1/(1-delta)^2 - 1);
%epsilon = sqrt(1/(1-delta) - 1);
c = epsilon^(-1) + sqrt(1 + + epsilon^(-2));
a = 0.5*(c^(1/n) - c^(-1/n));
b = 0.5*(c^(1/n) + c^(-1/n));

d = (1-a*tan2*cphi).^2 + (b*tan2*sphi).^2;
    
pole = (2*(1-a*tan2*cphi)./d-1)  +  1j*2*b*tan2*sphi;
%pole = pole(abs(pole) <= 1); % only those inside unit circle

zplane(zero,pole)

zero
pole

% disp(' ')
% disp('zeros      poles')
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
% disp([zero pole])
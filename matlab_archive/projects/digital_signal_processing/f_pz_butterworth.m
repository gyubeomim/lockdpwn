<<<<<<< HEAD
function [zero,pole] = f_pz_butterworth(n,Omega1)
%
% function [zero,pole] = f_pz_butterworth(n,Omega1)
%
% This function gives pole/zero of digital butterworth LPF.
%
% Input
%  n : filter order (ex. 10)
%  Omega1 : cutoff freq (ex. pi/3)

zero = -ones(n,1); % n zeros at z=-1

tansq = (tan(Omega1/2))^2;
tan2  = 2 * tan(Omega1/2);
m = [0 : 2*n-1]'; % col vector

if ( ceil(n/2) == n/2 ) % when n is even
    phi = (2*m+1) * pi / (2*n); % col vector
else % when n is odd
    phi = m * pi / n; % col vector
end
    
sphi = sin(phi);
cphi = cos(phi);
d = 1 - tan2*cphi + tansq;
    
pole = (1-tansq)./d  +  1j*tan2*sphi./d;
pole = pole(abs(pole) <= 1); % only those inside unit circle
=======
function [zero,pole] = f_pz_butterworth(n,Omega1)
%
% function [zero,pole] = f_pz_butterworth(n,Omega1)
%
% This function gives pole/zero of digital butterworth LPF.
%
% Input
%  n : filter order (ex. 10)
%  Omega1 : cutoff freq (ex. pi/3)

zero = -ones(n,1); % n zeros at z=-1

tansq = (tan(Omega1/2))^2;
tan2  = 2 * tan(Omega1/2);
m = [0 : 2*n-1]'; % col vector

if ( ceil(n/2) == n/2 ) % when n is even
    phi = (2*m+1) * pi / (2*n); % col vector
else % when n is odd
    phi = m * pi / n; % col vector
end
    
sphi = sin(phi);
cphi = cos(phi);
d = 1 - tan2*cphi + tansq;
    
pole = (1-tansq)./d  +  1j*tan2*sphi./d;
pole = pole(abs(pole) <= 1); % only those inside unit circle
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

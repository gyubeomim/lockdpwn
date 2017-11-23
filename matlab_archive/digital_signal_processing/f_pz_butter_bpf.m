<<<<<<< HEAD
function [zero,pole,K] = f_pz_butter_bpf(n,Omega2,Omega3)

% function [zero,pole,K] = f_pz_butter_bpf(n,Omega2,Omega3)
%
% This function gives pole/zero of digital butterworth BPF.
% It first finds pole/zero of LPF and then double them by a certain rule.
%
% Input
%  n: filter order (ex. 10). Output BPF is of order 2n.
%  Omega2: lower limit of bandwidth (ex. pi/3)
%  Omega3: upper limit of bandwidth (ex. pi/2)
%
% Output
%  zero: zeros of BPF
%  pole: poles of BPF
%  K: scale factor. Divide by K to make unity magnitude in passband. 

if ( Omega3 <= Omega2 )
    error('Omega3 must be greater than Omega2.')
end

Omega1 = Omega3 - Omega2;

[z,alpha] = f_pz_butterworth(n,Omega1);
K = sum(poly(z)) / sum(real(poly(alpha)));

A = cos((Omega3 + Omega2)/2) / cos((Omega3 - Omega2)/2);

pole1 = 0.5*A*(1+alpha) + sqrt(0.25 * A^2 * (1+alpha).^2 - alpha);
pole2 = 0.5*A*(1+alpha) - sqrt(0.25 * A^2 * (1+alpha).^2 - alpha);
pole = [pole1; pole2];

zero = [-ones(n,1); ones(n,1)]; % n zeros at z=-1 and n zeros at z=1 
=======
function [zero,pole,K] = f_pz_butter_bpf(n,Omega2,Omega3)

% function [zero,pole,K] = f_pz_butter_bpf(n,Omega2,Omega3)
%
% This function gives pole/zero of digital butterworth BPF.
% It first finds pole/zero of LPF and then double them by a certain rule.
%
% Input
%  n: filter order (ex. 10). Output BPF is of order 2n.
%  Omega2: lower limit of bandwidth (ex. pi/3)
%  Omega3: upper limit of bandwidth (ex. pi/2)
%
% Output
%  zero: zeros of BPF
%  pole: poles of BPF
%  K: scale factor. Divide by K to make unity magnitude in passband. 

if ( Omega3 <= Omega2 )
    error('Omega3 must be greater than Omega2.')
end

Omega1 = Omega3 - Omega2;

[z,alpha] = f_pz_butterworth(n,Omega1);
K = sum(poly(z)) / sum(real(poly(alpha)));

A = cos((Omega3 + Omega2)/2) / cos((Omega3 - Omega2)/2);

pole1 = 0.5*A*(1+alpha) + sqrt(0.25 * A^2 * (1+alpha).^2 - alpha);
pole2 = 0.5*A*(1+alpha) - sqrt(0.25 * A^2 * (1+alpha).^2 - alpha);
pole = [pole1; pole2];

zero = [-ones(n,1); ones(n,1)]; % n zeros at z=-1 and n zeros at z=1 
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

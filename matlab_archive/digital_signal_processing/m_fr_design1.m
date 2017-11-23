% m_fr_design1.m
% LPF design starting from ideal LPF.

disp('This program designs LPF using Fourier transform method.')
disp(' ')

M = input('Type M for (2M+1)-term causal low pass filter (ex. 30) -->  ');
Omega1 = input('Type \Omega_1 [rad] (cutoff frequency for LPF) (ex.pi/5)-->  ');

len = 2*M + 1;

close all

% impulse response
subplot(2,1,1)
n0 = -M : M;
h0 = 1 ./ (pi*n0) .* sin(Omega1*n0);
h0(M+1) = Omega1 / pi; % by L'hospital's rule

N = len + 10;
n = 0 : N-1;
h = zeros(1,N);
h(1:len) = h0;
stem(n,h,'.'), title('impulse response')
xlabel('n'), ylabel('h[n]')

% set coeffs of x and y terms
a = zeros(1,len); % coeff of y terms
a(1) = 1;
b = h0; % coeff of x terms

% frequency response
[H,w] = freqz(b,a);

subplot(2,2,3)
plot(w/pi,abs(H)), title('frequency response')
xlabel('\Omega (x \pi)'), ylabel('|H(\Omega)|')
    
subplot(2,2,4)
plot(w/pi,angle(H)*180/pi), title('frequency response')
xlabel('\Omega (x \pi)'), ylabel('\angle H(\Omega) [deg]')
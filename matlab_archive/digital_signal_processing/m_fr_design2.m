% m_fr_design2.m
% BPF (including HPF) design starting from ideal LPF.

disp('This program designs BPF using Fourier transform method.')
disp(' ')

M = input('Type M for (2M+1)-term causal BPF (ex. 30) -->  ');
Omega0 = input('Type \Omega_0 [rad] (center frequency) (ex.pi/3)-->  ');
Omega1 = input('Type \Omega_1 [rad] (half of bandwidth) (ex.pi/10)-->  ');

len = 2*M + 1;

close all

% impulse response
subplot(2,1,1)
n0 = -M : M;
h0 = 1 ./ (pi*n0) .* sin(Omega1*n0);
h0(M+1) = Omega1 / pi; % by L'hospital's rule
h0 = h0 .* cos(Omega0*n0); % shift center freq from 0 to Omega_0

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
% m_ma_design2.m
% MA-based BPF (including HPF) design.

disp('This program designs MA-based BPF (including HPF).')
disp(' ')

M = input('Type M for (2M+1)-term causal MA filter (ex. 10) -->  ');
Omega0 = input('Type \Omega_0 [rad], center freq for BPF (ex. pi/3) -->  ');

len = 2*M + 1;

close all

% impulse response
subplot(2,2,1)
n0 = -M : M;
h0 = 2 / len * cos(Omega0*n0);

N = len*2;
n = 0 : N-1;
h = zeros(1,N);
h(1:len) = h0;
stem(n,h,'.'), title('impulse response')
xlabel('n'), ylabel('h[n]')

% set coeffs of x and y terms
a = zeros(1,len); % coeff of y terms
a(1) = 1;
b = h0; % coeff of x terms

% pole/zero locations
subplot(2,2,3)
zplane(b,a)

% frequency response
[H,w] = freqz(b,a);

subplot(2,2,2)
plot(w/pi,abs(H)), title('frequency response')
xlabel('\Omega (x \pi)'), ylabel('|H(\Omega)|')
    
subplot(2,2,4)
plot(w/pi,angle(H)*180/pi)
xlabel('\Omega (x \pi)'), ylabel('\angle H(\Omega) [deg]')
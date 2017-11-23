<<<<<<< HEAD
% m_ma_design1.m
% MA-based LPF design.

disp('This program designs MA-based LPF.')
disp(' ')

M = input('Type M for (2M+1)-term causal MA filter (ex. 10)  -->  ');

len = 2*M + 1;

a = zeros(1,len); % coeff of y terms
a(1) = 1;
b = 1/len*ones(1,len); % coeff of x terms

close all

% impulse response
subplot(2,2,1)
N = len*3;
[h,x] = dimpulse(b,a,N);
n = 0 : N-1;
stem(n,h,'.'), title('impulse response')
xlabel('n'), ylabel('h[n]')

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
=======
% m_ma_design1.m
% MA-based LPF design.

disp('This program designs MA-based LPF.')
disp(' ')

M = input('Type M for (2M+1)-term causal MA filter (ex. 10)  -->  ');

len = 2*M + 1;

a = zeros(1,len); % coeff of y terms
a(1) = 1;
b = 1/len*ones(1,len); % coeff of x terms

close all

% impulse response
subplot(2,2,1)
N = len*3;
[h,x] = dimpulse(b,a,N);
n = 0 : N-1;
stem(n,h,'.'), title('impulse response')
xlabel('n'), ylabel('h[n]')

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
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
xlabel('\Omega (x \pi)'), ylabel('\angle H(\Omega) [deg]')
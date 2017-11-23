<<<<<<< HEAD
% m_windows_hamming.m

disp('Shows frequency response (magnitude) of Hamming window.')
M = input('Type M for window length (= 2M+1) -->  ');

Omega = 0 : pi/500 : pi; % Omega values for plot

nw = -M : M; % range of n for window
w = 0.54 + 0.46*cos(nw*pi/M); % window values
nwa = -2*M : 2*M; % range of n for plot
wa = [ zeros(1,M) , w , zeros(1,M) ]; 

% Fourier transform
W = zeros(size(Omega));
for n = -M : M
    wn = w(n+M+1); % scalar
    W = W + wn*exp(-1j*Omega*n);
end

close all

subplot(2,1,1)
stem(nwa,wa)
title(['Hamming Window of Length 2M+1 (M = ',int2str(M),')'])
ylabel('w[n]')
xlabel('n') 
axis([-2*M, 2*M, -inf, inf])

subplot(2,1,2)
nf = abs(W(1));
mag = 20*log10( abs(W)/nf );
plot(Omega/pi,mag)
ylabel('|W(\Omega)|_{dB} (normalized for 0dB at \Omega = 0)','interpreter','tex')
xlabel('\Omega (x \pi)','interpreter','tex') 
axis([0 1 -50  inf ])
grid

=======
% m_windows_hamming.m

disp('Shows frequency response (magnitude) of Hamming window.')
M = input('Type M for window length (= 2M+1) -->  ');

Omega = 0 : pi/500 : pi; % Omega values for plot

nw = -M : M; % range of n for window
w = 0.54 + 0.46*cos(nw*pi/M); % window values
nwa = -2*M : 2*M; % range of n for plot
wa = [ zeros(1,M) , w , zeros(1,M) ]; 

% Fourier transform
W = zeros(size(Omega));
for n = -M : M
    wn = w(n+M+1); % scalar
    W = W + wn*exp(-1j*Omega*n);
end

close all

subplot(2,1,1)
stem(nwa,wa)
title(['Hamming Window of Length 2M+1 (M = ',int2str(M),')'])
ylabel('w[n]')
xlabel('n') 
axis([-2*M, 2*M, -inf, inf])

subplot(2,1,2)
nf = abs(W(1));
mag = 20*log10( abs(W)/nf );
plot(Omega/pi,mag)
ylabel('|W(\Omega)|_{dB} (normalized for 0dB at \Omega = 0)','interpreter','tex')
xlabel('\Omega (x \pi)','interpreter','tex') 
axis([0 1 -50  inf ])
grid

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

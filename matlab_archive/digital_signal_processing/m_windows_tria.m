<<<<<<< HEAD
% m_windows_tria.m

disp('Shows frequency response (magnitude) of triangular window.')
M = input('Type M for window length (= 2M+1) -->  ');

Omega = 0 : pi/500 : pi;
n = length(Omega);

W = (M+1)*ones(1,n);
for i = 1 : M
    W = W + 2*(M+1-i)*cos(i*Omega);
end
W = W / (M+1)^2;

close all

subplot(2,1,1)
nw = -M : M;
w = (M+1-abs(nw)) ./ (M+1)^2;
nw = -2*M : 2*M;
w = [ zeros(1,M) , w , zeros(1,M) ];
stem(nw,w)
title(['Triangular Window of Length 2M+1 (M = ',int2str(M),')'])
ylabel('w[n]')
xlabel('n') 
axis([-2*M, 2*M, -inf, inf])

subplot(2,1,2)
mag = 20*log10( abs(W) );
plot(Omega/pi,mag)
ylabel('|W(\Omega)|_{dB} (normalized for 0dB at \Omega = 0)','interpreter','tex')
xlabel('\Omega (x \pi)','interpreter','tex') 
axis([0 1 -50  0 ])
grid

=======
% m_windows_tria.m

disp('Shows frequency response (magnitude) of triangular window.')
M = input('Type M for window length (= 2M+1) -->  ');

Omega = 0 : pi/500 : pi;
n = length(Omega);

W = (M+1)*ones(1,n);
for i = 1 : M
    W = W + 2*(M+1-i)*cos(i*Omega);
end
W = W / (M+1)^2;

close all

subplot(2,1,1)
nw = -M : M;
w = (M+1-abs(nw)) ./ (M+1)^2;
nw = -2*M : 2*M;
w = [ zeros(1,M) , w , zeros(1,M) ];
stem(nw,w)
title(['Triangular Window of Length 2M+1 (M = ',int2str(M),')'])
ylabel('w[n]')
xlabel('n') 
axis([-2*M, 2*M, -inf, inf])

subplot(2,1,2)
mag = 20*log10( abs(W) );
plot(Omega/pi,mag)
ylabel('|W(\Omega)|_{dB} (normalized for 0dB at \Omega = 0)','interpreter','tex')
xlabel('\Omega (x \pi)','interpreter','tex') 
axis([0 1 -50  0 ])
grid

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

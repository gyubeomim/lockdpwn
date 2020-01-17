<<<<<<< HEAD
% m_fr_design21.m
% Designs BPF using Fourier transform method with selection of window.

disp('This program designs BPF using Fourier transform method.')
disp('You can select a window.')
disp(' ')

M = input('Type M for (2M+1)-term causal BPF (ex. 30) -->  ');
Omega0 = input('Type \Omega_0 [rad] (center frequency) (ex.pi/3)-->  ');
Omega1 = input('Type \Omega_1 [rad] (half of bandwidth) (ex.pi/10)-->  ');
iwin = input('Select window (1: rect., 2: tri., 3: hann., 4: hamm.) -->  ');

% error checking
if ( Omega0 < pi )
    if ( Omega0+Omega1 > pi )
        error('(center freq) + (1/2 bandwidth) must be less than pi.')
    end
end

%%%%%  common variables  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

len = 2*M + 1;
n0 = -M : M;

%%%%%  generate window values, w[n]  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

switch iwin
    case 1 % rectangular window
        ww = ones(size(n0));
        sw = 'Rectangular';
    case 2 % triangular window
        ww = (M+1-abs(n0)) ./ (M+1);
        sw = 'Triangular';
    case 3 % hanning window
        ww = 0.5 + 0.5*cos(n0*pi/(M+1));
        sw = 'Hanning';
    case 4 % hamming window
        ww = 0.54 + 0.46*cos(n0*pi/M);
        sw = 'Hamming';
    otherwise
        error('Wrong window selection.')
end

%%%%%  find impulse response, difference eq, and freq response  %%%%%%%%%%%%%%%%

% impulse response
h0 = 1 ./ (pi*n0) .* sin(Omega1*n0);
h0(M+1) = Omega1 / pi; % by L'hospital's rule
h0 = h0 .* cos(Omega0*n0); % shift center freq from 0 to Omega_0
if ( Omega0 < pi )
    h0 = h0 * 2; % scale by 2 (do not scale for HPF)
end
h0 = h0 .* ww; % apply window

% set coeffs of x and y terms
a = zeros(1,len); % coeff of y terms
a(1) = 1;
b = h0; % coeff of x terms

% frequency response
[H,w] = freqz(b,a);

%%%%%  display coefficients of x terms  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp(' ')
disp('Coefficients of x & y terms in difference equation are stored in b & a.')
disp('a(1)*y(n) + a(2)*y(n-1) + ...  = b(1)*x(n) + b(2)*x(n-1) + ...')

%%%%%  plot  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all

% define variables for displaying IR in longer range of n
N = len + 10;
n = 0 : N-1;
h = zeros(1,N);
h(1:len) = h0;

% title
s = ['BPF (HPF) with ',sw,' Window of Length 2M+1 (M = ',int2str(M),')'];

subplot(2,1,1)
stem(n,h,'.')
xlabel('n'), ylabel('h[n]')
axis([0 n(end) -inf inf])
title(s)

subplot(2,2,3)
plot(w/pi,20*log10(abs(H)))
xlabel('\Omega (x \pi)'), ylabel('|H(\Omega)|_{dB}')
if Omega0 < pi
    set(gca,'XTick',[0, (Omega0-Omega1)/pi, (Omega0+Omega1)/pi, 1])
    set(gca,'XTickLabel',{'0';'fb1';'fb2';'1'})
elseif Omega0 == pi
    set(gca,'XTick',[0, (Omega0-Omega1)/pi, 1])
    set(gca,'XTickLabel',{'0';'fc';'1'})
end
set(gca,'XGrid','on')
axis([0 1 -50 inf])

subplot(2,2,4)
plot(w/pi,angle(H)*180/pi)
xlabel('\Omega (x \pi)'), ylabel('\angle H(\Omega) [deg]')
if Omega0 < pi
    set(gca,'XTick',[0, (Omega0-Omega1)/pi, (Omega0+Omega1)/pi, 1])
    set(gca,'XTickLabel',{'0';'fb1';'fb2';'1'})
elseif Omega0 == pi
    set(gca,'XTick',[0, (Omega0-Omega1)/pi, 1])
    set(gca,'XTickLabel',{'0';'fc';'1'})
end
set(gca,'XGrid','on')
=======
% m_fr_design21.m
% Designs BPF using Fourier transform method with selection of window.

disp('This program designs BPF using Fourier transform method.')
disp('You can select a window.')
disp(' ')

M = input('Type M for (2M+1)-term causal BPF (ex. 30) -->  ');
Omega0 = input('Type \Omega_0 [rad] (center frequency) (ex.pi/3)-->  ');
Omega1 = input('Type \Omega_1 [rad] (half of bandwidth) (ex.pi/10)-->  ');
iwin = input('Select window (1: rect., 2: tri., 3: hann., 4: hamm.) -->  ');

% error checking
if ( Omega0 < pi )
    if ( Omega0+Omega1 > pi )
        error('(center freq) + (1/2 bandwidth) must be less than pi.')
    end
end

%%%%%  common variables  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

len = 2*M + 1;
n0 = -M : M;

%%%%%  generate window values, w[n]  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

switch iwin
    case 1 % rectangular window
        ww = ones(size(n0));
        sw = 'Rectangular';
    case 2 % triangular window
        ww = (M+1-abs(n0)) ./ (M+1);
        sw = 'Triangular';
    case 3 % hanning window
        ww = 0.5 + 0.5*cos(n0*pi/(M+1));
        sw = 'Hanning';
    case 4 % hamming window
        ww = 0.54 + 0.46*cos(n0*pi/M);
        sw = 'Hamming';
    otherwise
        error('Wrong window selection.')
end

%%%%%  find impulse response, difference eq, and freq response  %%%%%%%%%%%%%%%%

% impulse response
h0 = 1 ./ (pi*n0) .* sin(Omega1*n0);
h0(M+1) = Omega1 / pi; % by L'hospital's rule
h0 = h0 .* cos(Omega0*n0); % shift center freq from 0 to Omega_0
if ( Omega0 < pi )
    h0 = h0 * 2; % scale by 2 (do not scale for HPF)
end
h0 = h0 .* ww; % apply window

% set coeffs of x and y terms
a = zeros(1,len); % coeff of y terms
a(1) = 1;
b = h0; % coeff of x terms

% frequency response
[H,w] = freqz(b,a);

%%%%%  display coefficients of x terms  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp(' ')
disp('Coefficients of x & y terms in difference equation are stored in b & a.')
disp('a(1)*y(n) + a(2)*y(n-1) + ...  = b(1)*x(n) + b(2)*x(n-1) + ...')

%%%%%  plot  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all

% define variables for displaying IR in longer range of n
N = len + 10;
n = 0 : N-1;
h = zeros(1,N);
h(1:len) = h0;

% title
s = ['BPF (HPF) with ',sw,' Window of Length 2M+1 (M = ',int2str(M),')'];

subplot(2,1,1)
stem(n,h,'.')
xlabel('n'), ylabel('h[n]')
axis([0 n(end) -inf inf])
title(s)

subplot(2,2,3)
plot(w/pi,20*log10(abs(H)))
xlabel('\Omega (x \pi)'), ylabel('|H(\Omega)|_{dB}')
if Omega0 < pi
    set(gca,'XTick',[0, (Omega0-Omega1)/pi, (Omega0+Omega1)/pi, 1])
    set(gca,'XTickLabel',{'0';'fb1';'fb2';'1'})
elseif Omega0 == pi
    set(gca,'XTick',[0, (Omega0-Omega1)/pi, 1])
    set(gca,'XTickLabel',{'0';'fc';'1'})
end
set(gca,'XGrid','on')
axis([0 1 -50 inf])

subplot(2,2,4)
plot(w/pi,angle(H)*180/pi)
xlabel('\Omega (x \pi)'), ylabel('\angle H(\Omega) [deg]')
if Omega0 < pi
    set(gca,'XTick',[0, (Omega0-Omega1)/pi, (Omega0+Omega1)/pi, 1])
    set(gca,'XTickLabel',{'0';'fb1';'fb2';'1'})
elseif Omega0 == pi
    set(gca,'XTick',[0, (Omega0-Omega1)/pi, 1])
    set(gca,'XTickLabel',{'0';'fc';'1'})
end
set(gca,'XGrid','on')
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
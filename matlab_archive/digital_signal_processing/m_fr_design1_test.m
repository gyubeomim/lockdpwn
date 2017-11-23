
% m_fr_design1_test.m

disp('You must run m_fr_design1.m before running this program !!')
disp(' ')

disp('Type two digital frequencies [rad] to make input signal.')
Om1 = input('Frequency of x1 [rad] (ex, 0.1*pi) -->  ');
Om2 = input('Frequency of x2 [rad] (ex, 0.2*pi) -->  ');

N = 200;
n = 0 : N-1;

% generate inputs
x1 = cos(Om1*n);
x2 = cos(Om2*n);
x = x1 + x2;

% compute outputs
y1 = conv(h0,x1);
y2 = conv(h0,x2);
y = conv(h0,x);

close all

% plot inputs
subplot(3,2,1)
plot(n,x1), xlabel('n'), ylabel('x1')
title([num2str(2*M+1),'-term LPF with center freq at ',num2str(Omega1/pi),'\pi [rad]'])

subplot(3,2,3)
plot(n,x2), xlabel('n'), ylabel('x2')

subplot(3,2,5)
plot(n,x), xlabel('n'), ylabel('x (= x1 + x2)')

% plot output2
subplot(3,2,2)
plot(n,y1(1:N)), xlabel('n'), ylabel('y1')
title(['x1: ',num2str(Om1/pi),'\pi [rad]  ,  x2: ',num2str(Om2/pi),'\pi [rad]'])

subplot(3,2,4)
plot(n,y2(1:N)), xlabel('n'), ylabel('y2')

subplot(3,2,6)
plot(n,y(1:N)), xlabel('n'), ylabel('y')

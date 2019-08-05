<<<<<<< HEAD

% m_rectdiff
%
% 21-term causal differentiator using rectangular window

disp('Type M, fa [Hz], f [Hz] in one vector')
disp('    M  = filter length 2M+1') 
disp('    fa = freq [Hz] of analog sinusoid')
disp('    f  = freq [Hz] of sampling')
disp('Try [10 0.1 1], [10 0.1 2], [20 0.1 2], [20 0.1 4]  ... ')
a = input(' --> ');

M = a(1); fa = a(2); f = a(3);

T = 1/f;

% design causal differentiator using rect. window
n = -M : M;
h = [];

for nn = n
    if ( rem(nn,2) ~= 0 )
        h = [h, -1/nn];
    else
        h = [h, 1/nn];
    end
end
h(M+1) = 0;
h = h/T;

% generate input signal and compute output by convolution
tf_long = 1/fa * 20; % start with long signal since convolution is used
t_long = 0 : T : tf_long;

x = sin(2*pi*fa*t_long);
yrect = conv(x,h);

tf = 1/fa * 5; % show 3 period
t = 0 : T : tf;
N = length(t);

% compute output of "rectangular differentiator"
x = x(1:N);
yrect = yrect(1:N);
yreal = 2*pi*fa*cos(2*pi*fa*t);

% find FR of "rectangular differentiator"
b = h*T; % coef of numerator (normalized)
a = 1; % coef of denominator
[H,W]=freqz(b,a);

subplot(3,1,1);
stem(n+M,h)
xlabel('n'); ylabel('h[n]'); title('impulse response of differentiator')

subplot(3,1,3);
plot(t,x,'.-',t,yrect,'.-',t,yreal,'.-')
xlabel('time [sec]');
legend('input','causal','exact')

subplot(3,2,3);
plot(W/pi,W,'g','LineWidth',5)
hold on; plot(W/pi,abs(H)); hold off
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('T \times | H(\Omega) |')

subplot(3,2,4);
plot(W/pi,90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); grid; hold off
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')
=======

% m_rectdiff
%
% 21-term causal differentiator using rectangular window

disp('Type M, fa [Hz], f [Hz] in one vector')
disp('    M  = filter length 2M+1') 
disp('    fa = freq [Hz] of analog sinusoid')
disp('    f  = freq [Hz] of sampling')
disp('Try [10 0.1 1], [10 0.1 2], [20 0.1 2], [20 0.1 4]  ... ')
a = input(' --> ');

M = a(1); fa = a(2); f = a(3);

T = 1/f;

% design causal differentiator using rect. window
n = -M : M;
h = [];

for nn = n
    if ( rem(nn,2) ~= 0 )
        h = [h, -1/nn];
    else
        h = [h, 1/nn];
    end
end
h(M+1) = 0;
h = h/T;

% generate input signal and compute output by convolution
tf_long = 1/fa * 20; % start with long signal since convolution is used
t_long = 0 : T : tf_long;

x = sin(2*pi*fa*t_long);
yrect = conv(x,h);

tf = 1/fa * 5; % show 3 period
t = 0 : T : tf;
N = length(t);

% compute output of "rectangular differentiator"
x = x(1:N);
yrect = yrect(1:N);
yreal = 2*pi*fa*cos(2*pi*fa*t);

% find FR of "rectangular differentiator"
b = h*T; % coef of numerator (normalized)
a = 1; % coef of denominator
[H,W]=freqz(b,a);

subplot(3,1,1);
stem(n+M,h)
xlabel('n'); ylabel('h[n]'); title('impulse response of differentiator')

subplot(3,1,3);
plot(t,x,'.-',t,yrect,'.-',t,yreal,'.-')
xlabel('time [sec]');
legend('input','causal','exact')

subplot(3,2,3);
plot(W/pi,W,'g','LineWidth',5)
hold on; plot(W/pi,abs(H)); hold off
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('T \times | H(\Omega) |')

subplot(3,2,4);
plot(W/pi,90*ones(size(W)),'g','LineWidth',5)
hold on; plot(W/pi,angle(H)*180/pi); grid; hold off
xlabel('\Omega ( \times \pi ) [rad]'); ylabel('\angle H(\Omega) [deg]')
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

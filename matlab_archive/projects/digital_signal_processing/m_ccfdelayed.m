<<<<<<< HEAD
%
% m_ccfdelayed.m
%

N = 1000;
M = 50; % maximum delay for plotting
x = 2*rand(N,1) - 1; % uniform random in [-1, 1]

%--------------------------------------------------------------------
% y[n] = x[n-27] - x[n-43] (delayed)
%--------------------------------------------------------------------

x27 = [zeros(27,1) ; x];
x27 = x27(1:N);
x43 = [zeros(43,1) ; x];
x43 = x43(1:N);
y_d = x27 - x43;

ccf_d = xcorr( x , y_d , M , 'biased' );

%--------------------------------------------------------------------
%y[n] = x[n+27] - x[n+43] (advanced)
%--------------------------------------------------------------------

x27 = [x ; zeros(27,1) ];
x27 = x27(28:end);
x43 = [x ; zeros(43,1) ];
x43 = x43(44:end);
y_a = x27 - x43;

ccf_a = xcorr( x , y_a , M , 'biased' );

%--------------------------------------------------------------------
% plot
%--------------------------------------------------------------------

close all

subplot(3,2,1)
bar(0:N-1,x)
xlabel('n'), ylabel('x[n]'), xlim([0,N])

subplot(3,2,3)
bar(0:N-1,y_d)
xlabel('n'), ylabel('y[n]'), xlim([0,N])
title('y[n] = x[n-27] - x[n-43]')

subplot(3,2,5)
stem(-M:M,ccf_d,'.-')
xlabel('m'), ylabel('\phi_{ xy}[m]'), xlim([-M,M])

subplot(3,2,2)
bar(0:N-1,x)
xlabel('n'), ylabel('x[n]'), xlim([0,N])

subplot(3,2,4)
bar(0:N-1,y_a)
xlabel('n'), ylabel('y[n]'), xlim([0,N])
title('y[n] = x[n+27] - x[n+43]')

subplot(3,2,6)
stem(-M:M,ccf_a,'.-')
xlabel('m'), ylabel('\phi_{ xy}[m]'), xlim([-M,M])
=======
%
% m_ccfdelayed.m
%

N = 1000;
M = 50; % maximum delay for plotting
x = 2*rand(N,1) - 1; % uniform random in [-1, 1]

%--------------------------------------------------------------------
% y[n] = x[n-27] - x[n-43] (delayed)
%--------------------------------------------------------------------

x27 = [zeros(27,1) ; x];
x27 = x27(1:N);
x43 = [zeros(43,1) ; x];
x43 = x43(1:N);
y_d = x27 - x43;

ccf_d = xcorr( x , y_d , M , 'biased' );

%--------------------------------------------------------------------
%y[n] = x[n+27] - x[n+43] (advanced)
%--------------------------------------------------------------------

x27 = [x ; zeros(27,1) ];
x27 = x27(28:end);
x43 = [x ; zeros(43,1) ];
x43 = x43(44:end);
y_a = x27 - x43;

ccf_a = xcorr( x , y_a , M , 'biased' );

%--------------------------------------------------------------------
% plot
%--------------------------------------------------------------------

close all

subplot(3,2,1)
bar(0:N-1,x)
xlabel('n'), ylabel('x[n]'), xlim([0,N])

subplot(3,2,3)
bar(0:N-1,y_d)
xlabel('n'), ylabel('y[n]'), xlim([0,N])
title('y[n] = x[n-27] - x[n-43]')

subplot(3,2,5)
stem(-M:M,ccf_d,'.-')
xlabel('m'), ylabel('\phi_{ xy}[m]'), xlim([-M,M])

subplot(3,2,2)
bar(0:N-1,x)
xlabel('n'), ylabel('x[n]'), xlim([0,N])

subplot(3,2,4)
bar(0:N-1,y_a)
xlabel('n'), ylabel('y[n]'), xlim([0,N])
title('y[n] = x[n+27] - x[n+43]')

subplot(3,2,6)
stem(-M:M,ccf_a,'.-')
xlabel('m'), ylabel('\phi_{ xy}[m]'), xlim([-M,M])
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

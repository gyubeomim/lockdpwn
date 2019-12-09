<<<<<<< HEAD
% m_linearphase.m
%
% Shows effect of linear phase system
% Assumes amplitude ratio is 1.

f1 = input('Type freq [Hz] of sinusoid 1 (3) -->  ');
f2 = input('Type freq [Hz] of sinusoid 2 (5) -->  ');
a  = input('Type a in linear phase delay -a*omega (0.1) -->  ');
C  = input('Type C in constant phase delay (2) -->  ');

f = max([f1 f2])*20; % sampling
tf = 1/min([f1 f2])*3; % final time
t = 0 : 1/f : tf;

x1 = sin(2*pi*f1*t);
x2 = sin(2*pi*f2*t);
x = x1 + x2;

ylin1 = sin(2*pi*f1*(t-a));
ylin2 = sin(2*pi*f2*(t-a));
ylin = ylin1 + ylin2;

ycon1 = sin(2*pi*f1*t-C);
ycon2 = sin(2*pi*f2*t-C);
ycon = ycon1 + ycon2;

subplot(3,2,1); plot(t,x1,t,ylin1);
% legend('in','out')
ylabel('x1')
title('Linear Phase (blue: input, green: output)')

subplot(3,2,3); plot(t,x2,t,ylin2);
% legend('in','out')
ylabel('x2')

subplot(3,2,5); plot(t,x,t,ylin);
% legend('in','out')
ylabel('x1+x2')

subplot(3,2,2); plot(t,x1,t,ycon1);
% legend('in','out')
ylabel('x1')
title('Constant Phase (blue: input, green: output)')

subplot(3,2,4); plot(t,x2,t,ycon2);
% legend('in','out')
ylabel('x2')

subplot(3,2,6); plot(t,x,t,ycon);
% legend('in','out')
ylabel('x1+x2')

% subplot(3,2,1); plot(t,x1); title('sinusoid 1')
% subplot(3,2,3); plot(t,x2); title('sinusoid 2')
% subplot(3,2,5); plot(t,x); title('sinusoid 1+2')
% 
% subplot(3,2,2); plot(t,ylin1,t,ycon1); legend('linear phase','constant phase')
% title('output to sinusoid 1')
% 
% subplot(3,2,4); plot(t,ylin2,t,ycon2); legend('linear phase','constant phase')
% title('output to sinusoid 2')
% 
% subplot(3,2,6); plot(t,x,'.-',t,ylin,t,ycon); legend('input','linear phase','constant phase')
% title('output to sinusoid 1+2')



=======
% m_linearphase.m
%
% Shows effect of linear phase system
% Assumes amplitude ratio is 1.

f1 = input('Type freq [Hz] of sinusoid 1 (3) -->  ');
f2 = input('Type freq [Hz] of sinusoid 2 (5) -->  ');
a  = input('Type a in linear phase delay -a*omega (0.1) -->  ');
C  = input('Type C in constant phase delay (2) -->  ');

f = max([f1 f2])*20; % sampling
tf = 1/min([f1 f2])*3; % final time
t = 0 : 1/f : tf;

x1 = sin(2*pi*f1*t);
x2 = sin(2*pi*f2*t);
x = x1 + x2;

ylin1 = sin(2*pi*f1*(t-a));
ylin2 = sin(2*pi*f2*(t-a));
ylin = ylin1 + ylin2;

ycon1 = sin(2*pi*f1*t-C);
ycon2 = sin(2*pi*f2*t-C);
ycon = ycon1 + ycon2;

subplot(3,2,1); plot(t,x1,t,ylin1);
% legend('in','out')
ylabel('x1')
title('Linear Phase (blue: input, green: output)')

subplot(3,2,3); plot(t,x2,t,ylin2);
% legend('in','out')
ylabel('x2')

subplot(3,2,5); plot(t,x,t,ylin);
% legend('in','out')
ylabel('x1+x2')

subplot(3,2,2); plot(t,x1,t,ycon1);
% legend('in','out')
ylabel('x1')
title('Constant Phase (blue: input, green: output)')

subplot(3,2,4); plot(t,x2,t,ycon2);
% legend('in','out')
ylabel('x2')

subplot(3,2,6); plot(t,x,t,ycon);
% legend('in','out')
ylabel('x1+x2')

% subplot(3,2,1); plot(t,x1); title('sinusoid 1')
% subplot(3,2,3); plot(t,x2); title('sinusoid 2')
% subplot(3,2,5); plot(t,x); title('sinusoid 1+2')
% 
% subplot(3,2,2); plot(t,ylin1,t,ycon1); legend('linear phase','constant phase')
% title('output to sinusoid 1')
% 
% subplot(3,2,4); plot(t,ylin2,t,ycon2); legend('linear phase','constant phase')
% title('output to sinusoid 2')
% 
% subplot(3,2,6); plot(t,x,'.-',t,ylin,t,ycon); legend('input','linear phase','constant phase')
% title('output to sinusoid 1+2')



>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

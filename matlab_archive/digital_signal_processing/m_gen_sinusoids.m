<<<<<<< HEAD


N = 200;    		% Number of samples
fs = 10;    		% Sampling rate
a1 = 1;     		% Amplitude 1
a2 = .25;   		% Amplitude 2
f1 = .05;   		% Frequency 1
f2 = 5;     		% Frequency 2
t = (0:N-1)/fs;	% Time base
x1 = a1*cos(2*pi*f1*t);	% Signal 1
x2 = a2*cos(2*pi*f2*t);	% Signal 2
x = x1 + x2;		% Signal with noise 
close;
plot(t,x)

disp('Following variables are just generated.')
disp('t : time')
disp('x1: sinusoid with 0.05Hz')
disp('x2: sinusoid with 5Hz')
disp('x : x1+x2')
=======


N = 200;    		% Number of samples
fs = 10;    		% Sampling rate
a1 = 1;     		% Amplitude 1
a2 = .25;   		% Amplitude 2
f1 = .05;   		% Frequency 1
f2 = 5;     		% Frequency 2
t = (0:N-1)/fs;	% Time base
x1 = a1*cos(2*pi*f1*t);	% Signal 1
x2 = a2*cos(2*pi*f2*t);	% Signal 2
x = x1 + x2;		% Signal with noise 
close;
plot(t,x)

disp('Following variables are just generated.')
disp('t : time')
disp('x1: sinusoid with 0.05Hz')
disp('x2: sinusoid with 5Hz')
disp('x : x1+x2')
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

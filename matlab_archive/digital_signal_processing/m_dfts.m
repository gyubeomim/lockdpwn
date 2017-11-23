<<<<<<< HEAD
% m_dfts.m
%
% This program compares computation time of different algorithms of DFT.

N = input('Type length of input vector (2000) -->  ');
x = rand(N,1);

t0 = clock;
X1 = f_dft(x);
t1 = etime(clock,t0);

t0 = clock;
X2 = f_dft1(x);
t2 = etime(clock,t0);

t0 = clock;
X3 = fft(x);
t3 = etime(clock,t0);

fprintf('\n computation time (sec) for different algorithms')
fprintf('\n -----------------------------------------------')
fprintf('\n     dft(direct)     dft(modulo )            fft')
fprintf('\n%16.4f%16.4f%16.4f\n',[t1 t2 t3])
%disp([t1 t2 t3])
=======
% m_dfts.m
%
% This program compares computation time of different algorithms of DFT.

N = input('Type length of input vector (2000) -->  ');
x = rand(N,1);

t0 = clock;
X1 = f_dft(x);
t1 = etime(clock,t0);

t0 = clock;
X2 = f_dft1(x);
t2 = etime(clock,t0);

t0 = clock;
X3 = fft(x);
t3 = etime(clock,t0);

fprintf('\n computation time (sec) for different algorithms')
fprintf('\n -----------------------------------------------')
fprintf('\n     dft(direct)     dft(modulo )            fft')
fprintf('\n%16.4f%16.4f%16.4f\n',[t1 t2 t3])
%disp([t1 t2 t3])
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

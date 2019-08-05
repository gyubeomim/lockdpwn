<<<<<<< HEAD
% m_stepresp
%
% This program computes step response of the filter:
% y[n] = 1.5y[n-1] - 0.85y[n-2] + x[n];

nf = input('Type N, the final value of n -->  ');

N = [];
Y = [];

ynm2 = 0;
ynm1 = 0;

for n = 0: nf

    yn = 1.5 * ynm1 - 0.85*ynm2 + f_step(n);
    
    N = [N, n];
    Y = [Y, yn];
    
    ynm2 = ynm1;  % update for the next step
    ynm1 = yn;
        
end

close all
=======
% m_stepresp
%
% This program computes step response of the filter:
% y[n] = 1.5y[n-1] - 0.85y[n-2] + x[n];

nf = input('Type N, the final value of n -->  ');

N = [];
Y = [];

ynm2 = 0;
ynm1 = 0;

for n = 0: nf

    yn = 1.5 * ynm1 - 0.85*ynm2 + f_step(n);
    
    N = [N, n];
    Y = [Y, yn];
    
    ynm2 = ynm1;  % update for the next step
    ynm1 = yn;
        
end

close all
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
stem(N,Y)
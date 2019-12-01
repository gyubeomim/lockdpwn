<<<<<<< HEAD
function y = f_fod(x,T)

%
% This function implements first order difference filter:
%  y[n] = x[n] - x[n-1];
%
% It is assumed that x[-1] = 0

y = diff(x)/T; % built-in function diff generates x[2]-x[1], ... x[n]-x[n-1]

y = [x(1)/T y]; % add (x[0]-x[-1])/T in front

=======
function y = f_fod(x,T)

%
% This function implements first order difference filter:
%  y[n] = x[n] - x[n-1];
%
% It is assumed that x[-1] = 0

y = diff(x)/T; % built-in function diff generates x[2]-x[1], ... x[n]-x[n-1]

y = [x(1)/T y]; % add (x[0]-x[-1])/T in front

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

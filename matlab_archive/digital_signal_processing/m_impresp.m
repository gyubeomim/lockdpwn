<<<<<<< HEAD
% m_impresp
%
% This program computes impulse response of the filter:
% y[n] = 1.5y[n-1] - 0.85y[n-2] + x[n];

disp('stem(n,y) will be displayed.'), disp(' ')
N = input('Type N, the final value of n (50, 100, ...) -->  ');


n = [];
y = [];

yim2 = 0;
yim1 = 0;

for i = 0: N

    yi = 1.5 * yim1 - 0.85*yim2 + f_impulse(i);
    
    n = [n, i];
    y = [y, yi];
    
    yim2 = yim1;  % update for the next step
    yim1 = yi;
        
end

close all
=======
% m_impresp
%
% This program computes impulse response of the filter:
% y[n] = 1.5y[n-1] - 0.85y[n-2] + x[n];

disp('stem(n,y) will be displayed.'), disp(' ')
N = input('Type N, the final value of n (50, 100, ...) -->  ');


n = [];
y = [];

yim2 = 0;
yim1 = 0;

for i = 0: N

    yi = 1.5 * yim1 - 0.85*yim2 + f_impulse(i);
    
    n = [n, i];
    y = [y, yi];
    
    yim2 = yim1;  % update for the next step
    yim1 = yi;
        
end

close all
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
stem(n,y)
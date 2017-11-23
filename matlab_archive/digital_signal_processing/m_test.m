% y[n] = 0.5y[n-1] + x[n];

disp('stem(n,y) will be displayed.'), disp(' ')
N = input('Type N, the final value of n (50, 100, ...) -->  ');

n = [];
y = [];
yim1 = 0;

for i = 0: N

    % yim1 = y[n-1]
    yi = 0.5*yim1 + f_step(i) ;
    
    n = [n, i];
    y = [y, yi];
    
    yim1 = yi;        
end

close all
stem(n,y)
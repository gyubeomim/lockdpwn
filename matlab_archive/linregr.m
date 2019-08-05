function [a,r2] = linregr(x,y)

%{
    input:
        x = independent variable
        y = dependent variable

    output:
        a = vector of slope, a(1), and intercept, a(2)
        r2 = coefficient of determination
%}

n = length(x);
if length(y) ~= n, error('x and y must be smae length'); end
x = x(:); y = y(:); % convert to column vectors

sx = sum(x); sy=sum(y);

sx2 = sum(x.*x); sxy = sum(x.*y); sy2 = sum(y.*y);
a(1) = (n*sxy - sx*sy) / (n*sx2-sx^2);
a(2) = sy/n-a(1)*sx/n;

r2 = ((n*sxy-sx*sy)/sqrt(n*sx2-sx^2)/sqrt(n*sy2-sy^2))^2;
%create plot of data and best fit line
xp = linspace(min(x),max(x),2);
yp = a(1)*xp + a(2);
plot(x,y,'o',xp,yp)
grid on
<<<<<<< HEAD
% m_z_ex1.m

b = conv([1 0 0],[1 -1]); % coef of x (Note: b has 6 terms)
b = conv(b,[1 0 1]);

a = conv([1 0.8],[1 1.38593 0.9604]); % coef of y
a = conv(a,[1 -1.64545 0.9025]);

n  = [];
y  = [];

xrhs = [1 0 0 0 0 0]; % [xn xnm1 xnm2 xnm3 xnm4 xnm5] at n=0
yrhs = [0 0 0 0 0]; % [ynm1 ynm2 ynm3 ynm4 ynm5] at n=0

aa = a;
aa(1)=[]; % remove 1st term
aa = -aa; % since they move to RHS

for nn = 0 : 200 % plot 200 points
    
    yn = aa*yrhs' + b*xrhs';
    
    n = [n nn];
    y = [y yn];
    
    % update for next iteration
    
    xrhs = [0 xrhs]; % shift right by adding x value in front
    xrhs(end) = []; % then remove last term
    
    yrhs = [yn yrhs]; % shift right by adding x value in front
    yrhs(end) = []; % then remove last term
    
end

close all
area(n,y)
=======
% m_z_ex1.m

b = conv([1 0 0],[1 -1]); % coef of x (Note: b has 6 terms)
b = conv(b,[1 0 1]);

a = conv([1 0.8],[1 1.38593 0.9604]); % coef of y
a = conv(a,[1 -1.64545 0.9025]);

n  = [];
y  = [];

xrhs = [1 0 0 0 0 0]; % [xn xnm1 xnm2 xnm3 xnm4 xnm5] at n=0
yrhs = [0 0 0 0 0]; % [ynm1 ynm2 ynm3 ynm4 ynm5] at n=0

aa = a;
aa(1)=[]; % remove 1st term
aa = -aa; % since they move to RHS

for nn = 0 : 200 % plot 200 points
    
    yn = aa*yrhs' + b*xrhs';
    
    n = [n nn];
    y = [y yn];
    
    % update for next iteration
    
    xrhs = [0 xrhs]; % shift right by adding x value in front
    xrhs(end) = []; % then remove last term
    
    yrhs = [yn yrhs]; % shift right by adding x value in front
    yrhs(end) = []; % then remove last term
    
end

close all
area(n,y)
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

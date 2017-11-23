function xb = incsearch(func,xmin,xmax,ns)

%160330_incsearch.m

if nargin < 3, error('at least 3 arguments required'), end
if nargin < 4, ns = 50; end

%incremental search
x = linspace(xmin,xmax,ns);
f = func(x);
nb = 0; xb = []; %xb is null unless sign change detected.
for k = 1:length(x)-1
    if sign(f(k)) ~= sign(f(k+1)) % check for sign change
        nb = nb+1;
        xb(nb,1) = x(k);
        xb(nb,2) = x(k+1);
    end
end

if isempty(xb) %display that no brackets were found
    disp('no brackets found')
    disp('check interval or increase ns')
else
    disp('number of brackets: ') %display number of brackets
    disp(nb)
end

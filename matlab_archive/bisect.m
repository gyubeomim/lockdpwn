function [root,fx,ea,iter] = bisect(func,xl,xu,es,maxit,varargin)

%160330_bisect.m

% varargin은 그냥 추가적인 값으로 보통 NULL로 나타낸다

if nargin<3,error('at least 3 input arguments required'),end
test = func(xl,varargin{:})* func(xu,varargin{:});

if test>0, error('no sign change'),end
if nargin<4 | isempty(es), es = 0.0001; end
if nargin<5 | isempty(maxit), maxit= 50; end

iter = 0; xr = xl; ea = 100;

while(1)
    xrold = xr;
    
    % 이분법 알고리즘
    xr = (xl + xu)/2;
    
    iter = iter + 1;
    if xr ~= 0, ea = abs((xr-xrold)/xr) * 100; end
     
    % 좋은 알고리즘이다.. 굳굳 (160405)
    test  = func(xl,varargin{:}) * func(xr,varargin{:});
    if test < 0
        xu = xr;
    elseif test > 0
        xl = xr;
    else
        ea = 0;
    end
    if ea <= es | iter >= maxit,break,end
end

root = xr; fx = func(xr,varargin{:});

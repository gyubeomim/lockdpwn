function [root,ea,iter]=falsepos(func,xl,xu,es,maxit,varargin)

% 가위치법 M파일
%{
    160405 인터넷에서 다운받은 파일
    
%}

if nargin<3, error('함수에 적어도 3개의 인자가 필요합니다.'),end
test=func(xl,varargin{:})*func(xu,varargin{:});
if test>0,error('구간 값 오류'),end
if nargin<4|isempty(es), es=0.0001; end
if nargin<5|isempty(maxit), maxit=50; end



iter=0; xr=xl;
while(1)
    xrold = xr;
    
    % 가위치법 알고리즘
    xr = xu-(func(xu)*(xl-xu))/(func(xl)-func(xu)); 
    
    iter=iter+1;
    if xr ~=0, ea=abs((xr-xrold)/xr)*100; end
    
    test=func(xl,varargin{:})*func(xr,varargin{:});
    if test<0
        xu=xr;
    elseif test>0
        xl=xr;
    else
        ea=0;
    end
    if ea <= es | iter >= maxit , break, end
end
root=xr;
    
function [root,ea,iter] = newtraph(func,dfunc,xr,es,maxit,varargin)

% 160405

%{
input:
    func = 함수의 이름
    dfunc = 도함수의 이름
    xr = 첫번째로 계산하고 싶은 x의 값
    es = 이상적인 상대오차 값 (기본 = 0.0001%)
    maxit = 최대 반복계산 횟수
    p1,p2... = 함수에서 사용하는 추가적인 변수값들
output:
    root = 실제 근
    ea = 대략적인 상대오차 값 (%)
    iter = 반복횟수
%}

% 만약 인자값이 3개 이하일 경우 프로그램을 종료합니다
if nargin < 3, error('at least 3 input arguments required'),end

% 만약 인자값이 4개 이하일 경우 es(상대오차)값을 0.0001%로 합니다
if nargin<4 | isempty(es),es=0.0001;end

% 만약 인자값이 5개 이하일 경우 maxit(최대반복계산)값을 50번으로 합니다
if nargin<5 | isempty(maxit), maxit=50;end

% iter 값을 0으로 초기화시킨 후
iter = 0;

% iter 값이 maxit 값보다 커질때까지 루프를 돕니다
while(1)
    
    % xrold에 사용자가 선택한 xr 값을 넣고
    xrold = xr;
    
    % Newton-Raphson 법을 이용해 xr 값을 근사시킵니다
    xr = xr - func(xr)/dfunc(xr);
    
    % 반복횟수를 +1 합니다
    iter = iter +1;
    
    % 만약 xr 값이 0이 아니면 ea(상대오차 값)을 구합니다
    if xr ~= 0, ea = abs((xr-xrold)/xr) * 100; end
    
    % 만약 ea(상대오차)값이 es(이상적인 상대오차)값보다 작다면 루프를 탈출합니다.
    if ea <= es | iter >= maxit, break, end
end

% xr(결과값)을 root(실제근)에 대입합니다
root = xr; 

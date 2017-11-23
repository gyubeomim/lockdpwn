function diffex(func,dfunc,x,n)
format long

% x값일 때 함수의 참값을 구합니다
dftrue = dfunc(x);

% 처음 h의 값은 1로 설정하고
h =1 ;                                  

% H의 값에 넣습니다
H(1) = h;                               

% 중심차분의 근사를 구합니다
D(1) = (func(x+h)-func(x-h))/(2*h);     

% 실제값과의 뺄셈으로 오차를 구합니다
E(1) = abs(dftrue - D(1));              

% i를 2부터 n까지 증가시키면서 H,D,E의 값을 구합니다
for i = 2:n
    h = h/10;
    H(i) = h;
    D(i) = (func(x+h)-func(x-h))/(2*h);
    E(i) = abs(dftrue - D(i));
    
end

% H,D,E의 값을 열벡터로 나타냅니다
L=[H' D' E']';

% fprintf 함수를 통해 H,D,E 벡터의 결과값을 출력합니다
fprintf(' step size     finite difference       true error\n');
fprintf('%14.10f    %16.14f     %16.13ff\n',L);
loglog(H,E), xlabel('Step Size'), ylabel('Error')
title('Plot of Error Versus Step Size')
format short
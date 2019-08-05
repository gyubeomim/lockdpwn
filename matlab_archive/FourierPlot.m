%{
    matlab ==> 진동학 p78 예제 1.21, 주기함수 x(t) = A * t/tau 를 Fourier 급수 전개 4번쨰 항까지만 plot하는 코드
%}
%ex1_21.m
%plot the function x(t) = A * t /tau

A = 1;
w = pi;
tau = 2;

for i = 1:101
    t(i) = tau * (i-1)/100;
    x(i) = A * t(i) / tau;
end

subplot(231);
plot(t,x);
grid;
ylabel('x(t)');
xlabel('t');
title('x(t) = A*t/tau' , 'fontsize',20);


for i = 1:101
    x1(i) = A/2;
end

subplot(232);
plot(t,x1);
grid;
xlabel('t');
title('One term', 'fontsize',20);

    
for i = 1:101
    x2(i) = A/2 - A * sin(w*t(i)) / pi;
end

subplot(233);
plot(t,x2);
grid;
xlabel('t');
title('Two term', 'fontsize',20);


for i = 1:101
    x3(i) = A/2 - A * sin(w*t(i)) / pi -A *sin(2*w*t(i)) / (2*pi);
end

subplot(234);
plot(t,x3);
grid;
ylabel('x(t) ');
xlabel('t');
title('Three term', 'fontsize',20);


for i = 1:101
    t(i) = tau * (i-1)/100;
    x4(i) = A/2 - A * sin(w*t(i)) / pi -A *sin(2*w*t(i)) / (2*pi) - A*sin(3*w*t(i)) / (3*pi);
end

subplot(235);
plot(t,x4);
grid;
ylabel('x(t) ');
xlabel('t');
title('Four term', 'fontsize',20);


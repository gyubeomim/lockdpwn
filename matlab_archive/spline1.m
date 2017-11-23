

% x값의 데이터를 입력합니다
x = [1 2 2.5 3 4 5];

% fx값의 데이터를 입력합니다
fx = [1 5 7 8 2 1];

% xx값을 이용해 (0,5) 구간을 100등분합니다
xx = linspace(0,5);

% sp1에 자연끝단조건 3차 스플라인의 값을 입력합니다
sp1 = interp1(x,fx,xx,'spline');

% sp2에 Hermite 3차 스플라인의 값을 입력합니다
sp2 = interp1(x,fx,xx,'pchip');

% sp1은 빨간선, sp2는 녹색점선으로 표시합니다
plot(x,fx,'o',xx,sp1,'r',xx,sp2,'--')
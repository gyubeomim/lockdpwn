<<<<<<< HEAD
% 이 예제에서는 주기 6인 임의의 신호가 4개의 사인파의 합성으로 표현된다는 것을 보여준다.
% 여기서는 x[n]이 우함수가 아니기 때문에 ak가 복소수로 나온다.

n_ori = 0 : 5; % 한 주기
x_ori = ceil(11*rand(1,6))-6; % -5 ~ 5 사이의 랜덤정수 6개
disp('주기 6의 정수 랜덤신호')
disp(x_ori)

ak = f_dfs(x_ori);
akmag = abs(ak);
akpha = angle(ak);

sx = num2str(x_ori);
sakmag = num2str(akmag');
sakpha = num2str(akpha');

a0 = ak(1);

am1 = akmag(2);
am2 = akmag(3);
am3 = akmag(4);

ap1 = akpha(2);
ap2 = akpha(3);
ap3 = akpha(4);

n = 0:11; % 2주기로 확장
nn = 0 : 11/200 : 11; % 점들 사이의 그래프를 부드럽게 만들기 위한 포인트들
x = repmat(x_ori,1,2); % 2주기만큼 확장

x0 = a0*ones(size(n)); % DC
x1 = 2*am1*cos(2*pi*n/6 + ap1);
x2 = 2*am2*cos(4*pi*n/6 + ap2);
x3 = am3*cos(6*pi*n/6 + ap3);

xx0 = a0*ones(size(nn)); % DC
xx1 = 2*am1*cos(2*pi*nn/6 + ap1);
xx2 = 2*am2*cos(4*pi*nn/6 + ap2);
xx3 = am3*cos(6*pi*nn/6 + ap3);
xx = xx0 + xx1 + xx2 + xx3;

xmin = min( [ min(xx) min(xx0), min(xx1), min(xx2), min(xx3) ] );
xmax = max( [ max(xx) max(xx0), max(xx1), max(xx2), max(xx3) ] );

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all
subplot(1,2,1)

plot(n,x,'ok','MarkerFaceColor','k'), hold on
plot(n,x0,'ob',n,x1,'og',n,x2,'or',n,x3,'om')
s  = 'x[n] (N=6)';
s0 = 'a_0 cos(\Omega_{0}n)';
s1 = '2|a_1| cos(\Omega_{1}n + \angle a_1)';
s2 = '2|a_2| cos(\Omega_{2}n + \angle a_2)';
s3 = '|a_3| cos(\Omega_{3}n + \angle a_3)';
legend(s,s0,s1,s2,s3)

stitle{1,1} = ['x = ',sx];
stitle{2,1} = ['|a_k | = ',sakmag];
stitle{3,1} = ['\angle a_k = ',sakpha];
title(stitle)

plot(nn,xx0+xx1+xx2+xx3,'k:')
plot(nn,xx0,'b',nn,xx1,'g',nn,xx2,'r',nn,xx3,'m'); hold off
axis([ min(n)-1 max(n)+1 xmin-1 xmax+1])
grid

% stem(n,x0); hold on
% stem(n,x1)
% stem(n,x2)
% stem(n,x3); hold off
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,2)

stem(n_ori,akmag); ylabel('| a_k |')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,4)

stem(n_ori,akpha*180/pi); ylabel('\angle a_k [deg]')
=======
% 이 예제에서는 주기 6인 임의의 신호가 4개의 사인파의 합성으로 표현된다는 것을 보여준다.
% 여기서는 x[n]이 우함수가 아니기 때문에 ak가 복소수로 나온다.

n_ori = 0 : 5; % 한 주기
x_ori = ceil(11*rand(1,6))-6; % -5 ~ 5 사이의 랜덤정수 6개
disp('주기 6의 정수 랜덤신호')
disp(x_ori)

ak = f_dfs(x_ori);
akmag = abs(ak);
akpha = angle(ak);

sx = num2str(x_ori);
sakmag = num2str(akmag');
sakpha = num2str(akpha');

a0 = ak(1);

am1 = akmag(2);
am2 = akmag(3);
am3 = akmag(4);

ap1 = akpha(2);
ap2 = akpha(3);
ap3 = akpha(4);

n = 0:11; % 2주기로 확장
nn = 0 : 11/200 : 11; % 점들 사이의 그래프를 부드럽게 만들기 위한 포인트들
x = repmat(x_ori,1,2); % 2주기만큼 확장

x0 = a0*ones(size(n)); % DC
x1 = 2*am1*cos(2*pi*n/6 + ap1);
x2 = 2*am2*cos(4*pi*n/6 + ap2);
x3 = am3*cos(6*pi*n/6 + ap3);

xx0 = a0*ones(size(nn)); % DC
xx1 = 2*am1*cos(2*pi*nn/6 + ap1);
xx2 = 2*am2*cos(4*pi*nn/6 + ap2);
xx3 = am3*cos(6*pi*nn/6 + ap3);
xx = xx0 + xx1 + xx2 + xx3;

xmin = min( [ min(xx) min(xx0), min(xx1), min(xx2), min(xx3) ] );
xmax = max( [ max(xx) max(xx0), max(xx1), max(xx2), max(xx3) ] );

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all
subplot(1,2,1)

plot(n,x,'ok','MarkerFaceColor','k'), hold on
plot(n,x0,'ob',n,x1,'og',n,x2,'or',n,x3,'om')
s  = 'x[n] (N=6)';
s0 = 'a_0 cos(\Omega_{0}n)';
s1 = '2|a_1| cos(\Omega_{1}n + \angle a_1)';
s2 = '2|a_2| cos(\Omega_{2}n + \angle a_2)';
s3 = '|a_3| cos(\Omega_{3}n + \angle a_3)';
legend(s,s0,s1,s2,s3)

stitle{1,1} = ['x = ',sx];
stitle{2,1} = ['|a_k | = ',sakmag];
stitle{3,1} = ['\angle a_k = ',sakpha];
title(stitle)

plot(nn,xx0+xx1+xx2+xx3,'k:')
plot(nn,xx0,'b',nn,xx1,'g',nn,xx2,'r',nn,xx3,'m'); hold off
axis([ min(n)-1 max(n)+1 xmin-1 xmax+1])
grid

% stem(n,x0); hold on
% stem(n,x1)
% stem(n,x2)
% stem(n,x3); hold off
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,2)

stem(n_ori,akmag); ylabel('| a_k |')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,4)

stem(n_ori,akpha*180/pi); ylabel('\angle a_k [deg]')
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

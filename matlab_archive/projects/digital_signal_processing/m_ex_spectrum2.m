<<<<<<< HEAD
% 이 예제에서는 주기 9인 신호가 5개의 사인파의 합성으로 표현된다는 것을 보여준다.
%

n_ori = 0 : 8; % 한 주기
x_ori = -2*cos(2*pi*n_ori/9) + 5*cos(4*pi*n_ori/9) + 3*cos(8*pi*n_ori/9);
ak = f_dfs(x_ori);
sx = num2str(x_ori);
sak = num2str(ak');

a0 = ak(1);
a1 = ak(2);
a2 = ak(3);
a3 = ak(4);
a4 = ak(5);

n = 0:17; % 2주기로 확장
nn = 0 : 17/300 : 17; % 점들 사이의 그래프를 부드럽게 만들기 위한 포인트들
x = repmat(x_ori,1,2); % 2주기만큼 확장

x0 = a0 * ones(size(n)); % DC
x1 = 2 * a1 * cos(2*pi*n/9);
x2 = 2 * a2 * cos(4*pi*n/9);
x3 = 2 * a3 * cos(6*pi*n/9);
x4 = 2 * a4 * cos(8*pi*n/9);

xx0 = a0 * ones(size(nn)); % DC
xx1 = 2 * a1 * cos(2*pi*nn/9);
xx2 = 2 * a2 * cos(4*pi*nn/9);
xx3 = 2 * a3 * cos(6*pi*nn/9);
xx4 = 2 * a4 * cos(8*pi*nn/9);
xx = xx0 + xx1 + xx2 + xx3 + xx4;

xmin = min( [ min(xx) min(xx0), min(xx1), min(xx2), min(xx3) min(xx4) ] );
xmax = max( [ max(xx) max(xx0), max(xx1), max(xx2), max(xx3) max(xx4) ] );

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all
subplot(1,2,1)
plot(n,x,'ok','MarkerFaceColor','k'), hold on
plot(n,x0,'ob',n,x1,'og',n,x2,'or',n,x3,'om',n,x4,'oc')
s  = 'x[n] (N=9)';
s0 = 'a_0 cos(\Omega_0 n)';
s1 = '2a_1 cos(\Omega_1 n)';
s2 = '2a_2 cos(\Omega_2 n)';
s3 = '2a_3 cos(\Omega_3 n)';
s4 = '2a_4 cos(\Omega_4 n)';
legend(s,s0,s1,s2,s3,s4)
title(['x = ',sx,' ,   a_k = ',sak])

plot(nn,xx,'k:')
plot(nn,xx0,'b',nn,xx1,'g',nn,xx2,'r',nn,xx3,'m',nn,xx4,'c'); hold off
axis([ min(n)-1 max(n)+1 xmin-1 xmax+1])
grid

% stem(n,x0); hold on
% stem(n,x1)
% stem(n,x2)
% stem(n,x3); hold off

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,2)

stem(n_ori,abs(ak)); ylabel('| a_k |')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,4)

=======
% 이 예제에서는 주기 9인 신호가 5개의 사인파의 합성으로 표현된다는 것을 보여준다.
%

n_ori = 0 : 8; % 한 주기
x_ori = -2*cos(2*pi*n_ori/9) + 5*cos(4*pi*n_ori/9) + 3*cos(8*pi*n_ori/9);
ak = f_dfs(x_ori);
sx = num2str(x_ori);
sak = num2str(ak');

a0 = ak(1);
a1 = ak(2);
a2 = ak(3);
a3 = ak(4);
a4 = ak(5);

n = 0:17; % 2주기로 확장
nn = 0 : 17/300 : 17; % 점들 사이의 그래프를 부드럽게 만들기 위한 포인트들
x = repmat(x_ori,1,2); % 2주기만큼 확장

x0 = a0 * ones(size(n)); % DC
x1 = 2 * a1 * cos(2*pi*n/9);
x2 = 2 * a2 * cos(4*pi*n/9);
x3 = 2 * a3 * cos(6*pi*n/9);
x4 = 2 * a4 * cos(8*pi*n/9);

xx0 = a0 * ones(size(nn)); % DC
xx1 = 2 * a1 * cos(2*pi*nn/9);
xx2 = 2 * a2 * cos(4*pi*nn/9);
xx3 = 2 * a3 * cos(6*pi*nn/9);
xx4 = 2 * a4 * cos(8*pi*nn/9);
xx = xx0 + xx1 + xx2 + xx3 + xx4;

xmin = min( [ min(xx) min(xx0), min(xx1), min(xx2), min(xx3) min(xx4) ] );
xmax = max( [ max(xx) max(xx0), max(xx1), max(xx2), max(xx3) max(xx4) ] );

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all
subplot(1,2,1)
plot(n,x,'ok','MarkerFaceColor','k'), hold on
plot(n,x0,'ob',n,x1,'og',n,x2,'or',n,x3,'om',n,x4,'oc')
s  = 'x[n] (N=9)';
s0 = 'a_0 cos(\Omega_0 n)';
s1 = '2a_1 cos(\Omega_1 n)';
s2 = '2a_2 cos(\Omega_2 n)';
s3 = '2a_3 cos(\Omega_3 n)';
s4 = '2a_4 cos(\Omega_4 n)';
legend(s,s0,s1,s2,s3,s4)
title(['x = ',sx,' ,   a_k = ',sak])

plot(nn,xx,'k:')
plot(nn,xx0,'b',nn,xx1,'g',nn,xx2,'r',nn,xx3,'m',nn,xx4,'c'); hold off
axis([ min(n)-1 max(n)+1 xmin-1 xmax+1])
grid

% stem(n,x0); hold on
% stem(n,x1)
% stem(n,x2)
% stem(n,x3); hold off

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,2)

stem(n_ori,abs(ak)); ylabel('| a_k |')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,4)

>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
stem(n_ori,angle(ak)*180/pi); ylabel('\angle a_k [deg]')
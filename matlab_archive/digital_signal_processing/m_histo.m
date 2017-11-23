<<<<<<< HEAD
% m_histo.m

M = input('Type number of set of uniform random signals to add to form Gaussian -->  ');

%--------------------------------------------------------------------------------------------------
% generate uniformly distributed random and find number of occurrence
%--------------------------------------------------------------------------------------------------
xu = ceil(300*rand(3000,1));
val = [1:300]';
for i = 1:300
   yu(i) = sum( xu == val(i) );
end

%--------------------------------------------------------------------------------------------------
% generate normally distributed random and find number of occurrence
%--------------------------------------------------------------------------------------------------
xn = ceil(300*rand(3000,1));
for i = 1:M-1
    xn = xn + ceil(300*rand(3000,1));
end

% 더했기 때문에 크기의 범위가 1~300 이 아니게 되지. 다시 1~300 사이의 값으로 만들어준다.
% 그냥 M으로 나누면 정수가 아닌 실수도 나올 수 있기 때문에 ceil을 하자
% 4개 더했을 때 10개 더했을 때, 늘려가면 표준편차가 더 좁아질거는거 관찰해봐
xn = ceil(xn/M); 

for i = 1:300
   yn(i) = sum( xn == val(i) );
end

%--------------------------------------------------------------------------------------------------
% plot
%--------------------------------------------------------------------------------------------------
close all

subplot(2,1,1);
bar(val,yu)
title('Histogram of scores for uniformly distributed random signal')

subplot(2,1,2)
bar(val,yn)
title(['Histogram of scores for ',int2str(M),'-addition of uniformly distributed random signal'])
=======
% m_histo.m

M = input('Type number of set of uniform random signals to add to form Gaussian -->  ');

%--------------------------------------------------------------------------------------------------
% generate uniformly distributed random and find number of occurrence
%--------------------------------------------------------------------------------------------------
xu = ceil(300*rand(3000,1));
val = [1:300]';
for i = 1:300
   yu(i) = sum( xu == val(i) );
end

%--------------------------------------------------------------------------------------------------
% generate normally distributed random and find number of occurrence
%--------------------------------------------------------------------------------------------------
xn = ceil(300*rand(3000,1));
for i = 1:M-1
    xn = xn + ceil(300*rand(3000,1));
end

% 더했기 때문에 크기의 범위가 1~300 이 아니게 되지. 다시 1~300 사이의 값으로 만들어준다.
% 그냥 M으로 나누면 정수가 아닌 실수도 나올 수 있기 때문에 ceil을 하자
% 4개 더했을 때 10개 더했을 때, 늘려가면 표준편차가 더 좁아질거는거 관찰해봐
xn = ceil(xn/M); 

for i = 1:300
   yn(i) = sum( xn == val(i) );
end

%--------------------------------------------------------------------------------------------------
% plot
%--------------------------------------------------------------------------------------------------
close all

subplot(2,1,1);
bar(val,yu)
title('Histogram of scores for uniformly distributed random signal')

subplot(2,1,2)
bar(val,yn)
title(['Histogram of scores for ',int2str(M),'-addition of uniformly distributed random signal'])
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

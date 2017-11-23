% matlab ==> 
clear,clc;

% 차량 제원
m = 747;        % 공차중량
ml = 819;       % 적재중량
l = 2.347;     % 휠베이스
lf = 1.103;     % 공차시 전륜 
lr = l - lf;    % 공차시 후륜
lf2 = 1.126;    % 적재시 전륜
lr2 = l - lf2;  % 적재시 후륜
h = 0.54;       % 무게중심 높이
g = 9.81;       % 중력가속도
W = m*g;        % 공차중량 무게
W2 = ml*g;      % 적재중량 무게

a = 0:0.01:1;   % 제동계수
Fbf_W = a.*(lr/l +h/l.*a);     % Fbf/W 공차시
Fbr_W = a.*(lf/l -h/l.*a);     % Fbr/W 공차시
Fbf_W2 = a.*(lr2/l +h/l.*a);     % Fbf/W 적재시  
Fbr_W2 = a.*(lf2/l -h/l.*a);     % Fbr/W 적재시

Fbf = Fbf_W*W;  
Fbr = Fbr_W*W;
Fbf2 = Fbf_W2*W2;  
Fbr2 = Fbr_W2*W2;

mub = 0.4;   % Mu 값 설정

Fbfmax_W = mub*(W*lr/l+h/l*Fbr)/(1-mub*h/l)/W;
Fbrmax_W = mub*(W*lf/l-h/l*Fbf)/(1+mub*h/l)/W;
Fbfmax_W2 = mub*(W2*lr/l+h/l*Fbr2)/(1-mub*h/l)/W2;
Fbrmax_W2 = mub*(W2*lf/l-h/l*Fbf2)/(1+mub*h/l)/W2;

hold on
plot(Fbf_W,Fbr_W,'r','linewidth',1.5)
plot(Fbf_W2,Fbr_W2,'b','linewidth',1.5)
legend('공차중량','적재중량')

for n = -3:6
    eval(['plot(Fbfmax_W+',num2str(n*0.1),',Fbr_W,''--'',''Color'',[0 0 0],''linewidth'',1)'])
end

for n = -3:6
    eval(['plot(Fbf_W,Fbrmax_W+',num2str(n*0.05),',''--'',''Color'',[0 0 0],''linewidth'',1)'])
end

plot(Fbfmax_W2,Fbr_W,'Color',[1 0 0],'linewidth',2)
plot(Fbf_W,Fbrmax_W2,'Color',[0 1 0],'linewidth',2)
axis([0 0.9 0 0.4]), grid



function anim_tracking_SCC_LKS(P,Vx,X,Y,psi,t,scale,steerangle,nframe,imanual)

%Bycicle모델의 X,Y,psi를 불러들여 에니매이션을 보여주는 함수
%
% anim_tracking(X,Y,psi,t,scale,steerangle,nframe,imanual)
%
% Input
%   X: 차량의 CG point의 X좌표 [m].
%   Y: 차량의 CG point의 Y좌표 [m].
%   psi : 차량의 Yaw angle [rad]
%   scale : 차량의 크기 [rad/s].
%   steerangle : 조향각 (전륜의 조향각을 plot하기때문에 추가함) [rad].
%   nframe : frame의 수 (일반적으로 inf)
%   imanual : 자동모드와 수동모드를 결정 (0 : 자동, 1 : 수동)

%초기값 세팅%
xp = 2.5;
xl = 2.2;
y0 = 1;
xftire = 1;

%차량의 Body 좌표값 생성 앞타이어의 좌표를 넣어줌%
bodyx = [xp-0.3, xftire,  -xl, -xl, xftire, xp-0.3,      xp,     xp,  xp-0.3];
bodyy = [    y0,     y0,   y0, -y0,    -y0,    -y0, -y0+0.3, y0-0.3,      y0];
body  = scale * [bodyx; bodyy];

%전륜의 경우 조향각의 영향을 받기때문에 뒷타이어만 고정 plot%
reartirex = [ -1   -2   0    -1   -2];
reartirey = [ y0   y0  nan  -y0  -y0];
reartire  = scale * [reartirex; reartirey];

%원점에서 길이 1인 전륜 타이어 그린다%
fronttirex = [0.5, -0.5];
fronttirey = [  0,    0];
fronttire  = scale * [fronttirex; fronttirey];


N = length(X);
k = 1;
kstride = floor(N/nframe)+1; 
close all
figure;

%x축과 y축 설정 최대값에서 차량의 크기를 고려한 축 설정%
xmax = max(X) + scale*2;
xmin = min(X) - scale*2; 
ymax = max(Y) + scale*2;
ymin = min(Y) - scale*2;

y = polyval(P,X);

%무한루프돌려%
while 1
    s1 = ['X = ',num2str(X(k),'%.2f'),' [m]'];
    s2 = ['Y = ',num2str(Y(k),'%.2f'),' [m]'];
    s3 = ['psi = ',num2str(180/pi*psi(k)), ' [deg]'];
    s4 = ['steerangle = ',num2str(steerangle(k)*17.25*180/pi), ' [deg]'];
    s5 = ['time = ',num2str(t(k),'%.2f'),' [s]'];
    s6 = ' ';
    if imanual == 1
        s6 = 'Manual mode. Type enter to proceed.';
    end
    subplot(2,2,[1,2])
    plot(X,y,'g--','Linewidth',2.5)
    axis equal;
    axis([ xmin , xmax , ymin , ymax ])
    %axis off % 이거 끄면 회색바탕 안끄면 좌표값 보임 %
    title([ {s1} ; {s2} ; {s3} ; {s4} ; {s5} ; {s6} ]) ;
    xlabel('X position [m]') ;
    ylabel('Y position [m]') ;
    hold on;
    plot(X,Y,'r','Linewidth',1);
              
    ROT = [cos(psi(k)) -sin(psi(k));sin(psi(k)) cos(psi(k))];
    ROTtire = [cos(steerangle(k)) -sin(steerangle(k));sin(steerangle(k)) cos(steerangle(k))];
    ROTbody = ROT * body;
    rearROTtire = ROT * reartire;
    frontROTtire = ROTtire * ROT * fronttire;

    plot(X(k),Y(k),'o',X(k),Y(k),'x');
    plot(ROTbody(1,:) + X(k) ,ROTbody(2,:) + Y(k),'b','Linewidth',2);

    plot(rearROTtire(1,:) + X(k) ,rearROTtire(2,:) + Y(k),'b','Linewidth',8);

    plot(frontROTtire(1,:) + X(k) + ROTbody(3), frontROTtire(2,:) + Y(k) + ROTbody(4),'b','Linewidth',8);
    plot(frontROTtire(1,:) + X(k) + ROTbody(9), frontROTtire(2,:) + Y(k) + ROTbody(10),'b','Linewidth',8);
    hold off
      
    if ( imanual == 0 )
        s6 = 'Auto Mode. Please Wait';
        title([ {s1} ; {s2} ; {s3} ; {s4} ; {s5} ; {s6} ]) ;
        pause(0.01);
    else
        pause
    end
   
    subplot(2,2,3,'Linewidth',2)
    plot(t(1:k),Vx(1:k));
    title('Longitudinal Velocity')
    xlabel('time [sec]');ylabel('Vx [km/h]');
    axis([t(1) t(end) min(Vx)*0.9 max(Vx)*1.1])
    
    subplot(2,2,4,'Linewidth',2)
    plot(t(1:k),steerangle(1:k)*17.25*180/pi);
    title('Steering Angle')
    xlabel('time [sec]');ylabel('SWA [deg]');
    axis([t(1) t(end) min(steerangle*17.25*180/pi)*1.1 max(steerangle*17.25*180/pi)*1.1])
    
    
    %루프가 끝나기 위한 조건%
    k = k + kstride;
    
    if ( k > N )
        return
    end
     
end
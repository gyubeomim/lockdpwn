function anim_tracking_ESC(X,Y,psi,t,scale,steerangle,nframe,imanual)
clf

xp = 2.5;
xl = 2.2;
y0 = 1;
xftire = 1;

bodyx = [xp-0.3, xftire,  -xl, -xl, xftire, xp-0.3,      xp,     xp,  xp-0.3];
bodyy = [    y0,     y0,   y0, -y0,    -y0,    -y0, -y0+0.3, y0-0.3,      y0];
body  = scale * [bodyx; bodyy];

reartirex = [ -1   -2   0    -1   -2];
reartirey = [ y0   y0  nan  -y0  -y0];
reartire  = scale * [reartirex; reartirey];

fronttirex = [0.5, -0.5];
fronttirey = [  0,    0];
fronttire  = scale * [fronttirex; fronttirey];


N = length(X);
k = 1;
kstride = floor(N/nframe)+1; 

%x축과 y축 설정 최대값에서 차량의 크기를 고려한 축 설정%
xmax = max(X) + scale*2;
xmin = min(X) - scale*2; 
ymax = max(Y) + scale*2;
ymin = min(Y) - scale*2;

%무한루프돌려%
while 1
    s1 = ['X = ',num2str(X(k),'%.2f'),' [m]'];
    s2 = ['Y = ',num2str(Y(k),'%.2f'),' [m]'];
    s3 = ['psi = ',num2str(180/pi*psi(k)), ' [deg]'];
    s4 = ['steerangle = ',num2str(180/pi*steerangle(k)), ' [deg]'];
    s5 = ['time = ',num2str(t(k),'%.2f'),' [s]'];
    s6 = ' ';
    if imanual == 1
        s6 = 'Manual mode. Type enter to proceed.';
    end
    plot(X,Y,'r','Linewidth',1);
    axis equal;
    axis([ xmin , xmax , ymin , ymax ])
    %axis off % 이거 끄면 회색바탕 안끄면 좌표값 보임 %
    title([ {s1} ; {s2} ; {s3} ; {s4} ; {s5} ; {s6} ]) ;
    xlabel('X position [m]') ;
    ylabel('Y position [m]') ;
    hold on;
      
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
    
    %루프가 끝나기 위한 조건%
    k = k + kstride;
    
    if ( k > N )
        return
    end
     
end
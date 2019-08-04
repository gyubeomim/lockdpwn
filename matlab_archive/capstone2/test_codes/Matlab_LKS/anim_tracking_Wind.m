function anim_tracking_LKS(X,Y,psi,t,scale,steerangle,nframe,imanual)
clf

N = length(X);
k = 1;
kstride = floor(N/nframe)+1; 

xmax = max(X) + scale*2;
xmin = min(X) - scale*2; 
ymax = max(Y) + scale*2;
ymin = min(Y) - scale*2;

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
    axis([ xmin , xmax , ymin , ymax ])
    title([ {s1} ; {s2} ; {s3} ; {s4} ; {s5} ; {s6} ]) ;
    xlabel('X position [m]') ;
    ylabel('Y position [m]') ;
    hold on;
        plot(X(k),Y(k),'o',X(k),Y(k),'x');
    hold off
    
        if ( imanual == 0 )
        s6 = 'Auto Mode. Please Wait';
        title([ {s1} ; {s2} ; {s3} ; {s4} ; {s5} ; {s6} ]) ;
        pause(0.01);
    else
        pause
    end
    
    k = k + kstride;
    
    if ( k > N )
        return
    end
     
end
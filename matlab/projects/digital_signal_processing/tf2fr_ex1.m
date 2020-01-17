<<<<<<< HEAD
% tf2fr_ex1.m

disp('Type any key to proceed')

hold off

a = [1 0.8]; % coeff of y
b = [1 -0.8]; % coeff of x

pole = -0.8 + 0j;
zero = 0.8;

N = 50;
for Omega = 0 : pi/N : pi

    zplane(b,a)
    hold on

    z = exp(1j*Omega);
    plot(real(z),imag(z),'o','MarkerFaceColor','m')
    
    plot([real(zero) real(z)],[imag(zero) imag(z)],'b')
    plot([real(pole) real(z)],[imag(pole) imag(z)],'r')
    
    lengthp = sqrt( (real(pole)-real(z))^2 + (imag(pole)-imag(z))^2 );
    lengthz = sqrt( (real(zero)-real(z))^2 + (imag(zero)-imag(z))^2 );
    
    text(0.8,-0.1,num2str(lengthz),'Color','b')
    text(-0.8,-0.1,num2str(lengthp),'Color','r')
    
    pause
    
    hold off
    
end
=======
% tf2fr_ex1.m

disp('Type any key to proceed')

hold off

a = [1 0.8]; % coeff of y
b = [1 -0.8]; % coeff of x

pole = -0.8 + 0j;
zero = 0.8;

N = 50;
for Omega = 0 : pi/N : pi

    zplane(b,a)
    hold on

    z = exp(1j*Omega);
    plot(real(z),imag(z),'o','MarkerFaceColor','m')
    
    plot([real(zero) real(z)],[imag(zero) imag(z)],'b')
    plot([real(pole) real(z)],[imag(pole) imag(z)],'r')
    
    lengthp = sqrt( (real(pole)-real(z))^2 + (imag(pole)-imag(z))^2 );
    lengthz = sqrt( (real(zero)-real(z))^2 + (imag(zero)-imag(z))^2 );
    
    text(0.8,-0.1,num2str(lengthz),'Color','b')
    text(-0.8,-0.1,num2str(lengthp),'Color','r')
    
    pause
    
    hold off
    
end
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8

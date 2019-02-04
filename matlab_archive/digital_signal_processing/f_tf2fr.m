
function f_tf2fr(poles,zeros)

% function f_tf2fr(poles,zeros)
% 
% Input
%  poles: pole vector (either column vector or empty array)
%  zeros: zero vector (either column vector or empty array)

% check whether poles and zeros are given as column vectors
[mp,np] = size(poles);
if ~isempty(poles) & (np ~= 1)
    error('poles must be a column vector.')
end
[mz,nz] = size(zeros);
if ~isempty(zeros) & (nz ~= 1)
    error('zeros must be a column vector.')
end

disp('Type any key to proceed (ctrl-c to exit)')

theta = 0 : pi/200 : 2*pi;
circlexy = exp(1i*theta); % points around unit circle

close all

pole = -0.8 + 0j;
zero = 0.8;

N = 100;
for Omega = 0 : pi/N : pi

    subplot(1,2,1) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    % plot poles and zeros along with unit circle
    plot(circlexy,':')
    hold on
    plot(real(poles),imag(poles),'rx')
    axis([-1.2 1.2 -1.2 1.2])
    axis equal
    plot(real(zeros),imag(zeros),'bo')
    xlabel('real'), ylabel('imaginary')

    set(gca,'XTick',0)
    set(gca,'YTick',0)
    set(gca,'XGrid','on')
    set(gca,'YGrid','on')
    
    z = exp(1j*Omega);
    plot(real(z),imag(z),'o','MarkerFaceColor','b')
    
    for i = 1:mz
        plot([real(zeros(i)); real(z)],[imag(zeros(i)); imag(z)],'b')
    end
    for i = 1:mp
        plot([real(poles(i)); real(z)],[imag(poles(i)); imag(z)],'r')
    end
    
    lengthzz = 1;
    for i = 1:mz
        lengthz = sqrt( (real(zeros(i))-real(z))^2 + (imag(zeros(i))-imag(z))^2 );
        text(real(zeros(i))-0.05,imag(zeros(i))-0.05,num2str(lengthz),'Color','b')
        lengthzz = lengthzz * lengthz;
    end
    
    lengthpp = 1;
    for i = 1:mp
        lengthp = sqrt( (real(poles(i))-real(z))^2 + (imag(poles(i))-imag(z))^2 );
        text(real(poles(i))-0.05,imag(poles(i))-0.05,num2str(lengthp),'Color','r')
        lengthpp = lengthpp * lengthp;
    end
    
    hold off

    subplot(1,2,2) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    hold on
    
    plot(Omega/pi,lengthzz/lengthpp,'.')
    axis([0 1 0 inf])
    xlabel('\Omega (x \pi)')
    ylabel('|H(\Omega)|')

    pause

end

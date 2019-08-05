<<<<<<< HEAD
% freqresp_2nd.m

while 1
    
    disp('Type ctrl-c to exit')
    r = input('Type r -->  ');
    theta = input('Type theta [deg] -->  ');
    disp(' ')    
    
    a = [1, -2*r*cos(theta*pi/180), r^2]; % coeffs of y
    b = [1 0 0]; % coeffs of x
    
    close all
    
    % find impulse response and plot
    N = 200;
    [h,x] = dimpulse(b,a,N);
    n = 0 : N-1;

    subplot(1,2,1)
    stem(n,h,'.'), title('impulse response')
    xlabel('n'), ylabel('h[n]')
    
    % frequency response
    [H,w] = freqz(b,a);

    subplot(2,2,2)
    plot(w/pi,abs(H)), title('frequency response')
    ylabel('|H(\Omega)|')
    
    subplot(2,2,4)
    plot(w/pi,angle(H)*180/pi)
    xlabel('\Omega (x \pi)'), ylabel('\angle H(\Omega) [deg]')
    
end
=======
% freqresp_2nd.m

while 1
    
    disp('Type ctrl-c to exit')
    r = input('Type r -->  ');
    theta = input('Type theta [deg] -->  ');
    disp(' ')    
    
    a = [1, -2*r*cos(theta*pi/180), r^2]; % coeffs of y
    b = [1 0 0]; % coeffs of x
    
    close all
    
    % find impulse response and plot
    N = 200;
    [h,x] = dimpulse(b,a,N);
    n = 0 : N-1;

    subplot(1,2,1)
    stem(n,h,'.'), title('impulse response')
    xlabel('n'), ylabel('h[n]')
    
    % frequency response
    [H,w] = freqz(b,a);

    subplot(2,2,2)
    plot(w/pi,abs(H)), title('frequency response')
    ylabel('|H(\Omega)|')
    
    subplot(2,2,4)
    plot(w/pi,angle(H)*180/pi)
    xlabel('\Omega (x \pi)'), ylabel('\angle H(\Omega) [deg]')
    
end
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
    
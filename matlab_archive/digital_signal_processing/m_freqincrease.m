<<<<<<< HEAD
% m_freqincrease.m

n = 0:40;
close all

while 1
    
    m = input('Type m (integer) for frequency (= 2*pi*m/8) -->  ');

    omega = 2*pi*m/8;
    x = cos(omega.*n);
    
    stem(n,x)
    
    xlabel('n')
    ylabel('cos(2*pi*m/8*n)')
    axis([ 0 40 -1.5 1.5])
   
    title(['m = ',num2str(m)])
end
=======
% m_freqincrease.m

n = 0:40;
close all

while 1
    
    m = input('Type m (integer) for frequency (= 2*pi*m/8) -->  ');

    omega = 2*pi*m/8;
    x = cos(omega.*n);
    
    stem(n,x)
    
    xlabel('n')
    ylabel('cos(2*pi*m/8*n)')
    axis([ 0 40 -1.5 1.5])
   
    title(['m = ',num2str(m)])
end
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
    
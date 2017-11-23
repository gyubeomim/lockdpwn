clear all ; close all ; clc;


t = 0 : 0.001 : 1;
p = 1;
appr_rect = 1/2;
figure;

for p = 1:1:1000
    appr_rect = appr_rect+ 2*(1./((2*p-1)*pi).*sin(2*pi*(2*p-1)*t));
    plot(t, appr_rect)
    num_of_P = num2str(2*p-1);
    T = strcat('+ 1/', num_of_P, '\pi*sin(', num_of_P,'+\pit)');
    text(0.7, 0.25, T);
    pause(0.1);
end

axis([-0.1 1.1 -0.1 1.1]);
grid on;
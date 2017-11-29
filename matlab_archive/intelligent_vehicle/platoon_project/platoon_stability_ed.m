%{
    matlab ==> 지능형자동차, 군집주행 프로젝트에서 string stability를 검사하는 코드
%}

% set parameters
k1 = 0.0001;
k2 = -1.004;
q = 0.01;
tau = 1.24;

% find out string stability
s = tf('s');
H1 = (-k2 *s + k1) / (q*s^3 + (1+k2*tau)*s^2 - k2*s + k1);
H2 = (tau*q*s^2 + (k2*tau+1)*tau*s) / (q*s^3 + (1+k2*tau)*s^2 - k2*s + k1);

bode(H1); grid  % should be less than 1
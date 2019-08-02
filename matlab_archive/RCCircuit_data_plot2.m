% matlab ==> simulink제어기, RC 회로를 R,C를 바꿔가면서 시뮬레이션 해 본 코드
%                                      sim 명령어를 통해 여러번 돌려볼 수 있다 굳굳
clear, clc

R = 1;
CAP = [1 1/2 1/4];
for k=1:3
    C = CAP(k);
    sim('RCCircuit');
    vc(:,k) = yout(:,2);
end

plot(tout, vc(:,1), tout, vc(:,2), tout, vc(:,3), 'linewidth', 1.5)
xlabel('Time (secs)', 'fontsize', 15); 
ylabel('Amplitude (volts)', 'fontsize', 15);
grid

st1 = 'Capacitor Voltage Plot: R = ';
st2 = num2str(R);
st3 = ' \omega';
st4 = ', C = ' ;
st5 = num2str(CAP(1));
st6 = ' F ';
sl1 = strcat(st1,st2,st3,st4,st5,st6);
st5 = num2str(CAP(2));
sl2 = strcat(st1,st2,st3,st4,st5,st6);
st5 = num2str(CAP(3));
sl3 = strcat(st1,st2,st3,st4,st5,st6);

title(' Capacitor Voltage Plot Using SIM', 'fontsize',16)
legend(sl1, sl2, sl3, 'fontsize',16), axis([0 10 -5 15]);
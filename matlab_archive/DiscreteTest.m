
Ts =0.001;  % Sampling Time : 0.001 
s= tf('s');
z = tf('z',Ts);  

aa = (0.01272*z + 0.01203)/(z^2 - 1.8349*z + 0.8597);
bb = feedback(aa,1);

% bb의l Step응답 테스트
step(bb,0.1)

% bb의 Ramp응답 테스트 
step(bb/(1-z^-1),1/(1-z^-1),0.1);








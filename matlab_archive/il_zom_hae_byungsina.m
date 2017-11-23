% 현석우가 일을 안해서 이름을 이렇게 지었다. 2016_디지털제어 과제
s = tf('s');

J = 52E-7;        % 질량관성모멘트 [ kg * m^2 ]
b = 3.1831E-4;   % 점성마찰계수 [ Nm*s/rad ]  % pdf에 Speed Regulation Constant로 부터 얻는다 % 3.141e-03
K = 0.0245;       % Kt ,토크상수 [ Nm/A ] 
                      % Ke ,역기전력상수 [ V*s/rad ] 둘은 통상 같은 값으로 한다 
R = 1.8;           % 전기자 직렬저항 [ Ohm ]
L = 0.0024;       % 전기자 인덕턴스 [ H ]

% 원래는 분모가 2차방정식이나 
% 각속도(theta') ==> 각도(theta)로 output이 바뀌면서 적분형태로 1/s가 추가되어 3차방정식 형태가 된다.
my_motor = K/(s*((J*s+b)*(L*s+R)+K^2));  
%step(my_motor)


 

[Gm,Pm,Wcg,Wcp] = margin(my_motor) 

Gm =

   38.8458


Pm =

   79.8529


Wcg =

  306.6057


Wcp =

   20.6463

ba=20.6463*2*25

ba =

   1.0323e+03

[Gm,Pm,Wcg,Wcp] = margin(my_motor)

Gm =

   38.8458


Pm =

   79.8529


Wcg =

  306.6057


Wcp =

   20.6463

ba

ba =

   1.0323e+03

bb=ba/2/pi

bb =

  164.2980

fr=1/bb

fr =

    0.0061

dmy= c2d(my_motor,tr,'tustin')
Undefined function or variable 'tr'.
 
dmy= c2d(my_motor,fr,'tustin')

dmy =
 
  0.01275 z^3 + 0.03825 z^2 + 0.03825 z + 0.01275
  -----------------------------------------------
        z^3 - 1.06 z^2 - 0.0782 z + 0.1378
 
Sample time: 0.0060865 seconds
Discrete-time transfer function.

rlocus(dmy)
hold on
zgrid(0.7100,112.5)
zgrid(0.7100,112.5*fr)
a= exp(-sig*fr)

a =

    0.6270

drl=(z-0.402)/(z+0.4);
rlocus(dmy*drl)
drl=14.6*(z-0.402)/(z+0.4);
rlco=drl*dmy

rlco =
 
  0.1862 z^4 + 0.4836 z^3 + 0.334 z^2 - 0.03835 z - 0.07484
  ---------------------------------------------------------
     z^4 - 0.6596 z^3 - 0.5021 z^2 + 0.1065 z + 0.05513
 
Sample time: 0.0060865 seconds
Discrete-time transfer function.

hold off
step(rlco);
hold on
step(clDGs2)
hold off
sys= feedback(rlco,1)

sys =
 
  0.1862 z^4 + 0.4836 z^3 + 0.334 z^2 - 0.03835 z - 0.07484
  ---------------------------------------------------------
   1.186 z^4 - 0.176 z^3 - 0.1681 z^2 + 0.0682 z - 0.01971
 
Sample time: 0.0060865 seconds
Discrete-time transfer function.

step(sys)
step(clDGs2)
hold on
step(sys)

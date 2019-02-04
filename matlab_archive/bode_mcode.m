>> s = tf('s');

J = 52E-7;        % 질량관성모멘트 [ kg * m^2 ]
b = 3.1831E-4;   % 점성마찰계수 [ Nm*s/rad ]  % pdf에 Speed Regulation Constant로 부터 얻는다 % 3.141e-03
K = 0.0245;       % Kt ,토크상수 [ Nm/A ] 
                      % Ke ,역기전력상수 [ V*s/rad ] 둘은 통상 같은 값으로 한다 
R = 1.8;           % 전기자 직렬저항 [ Ohm ]
L = 0.0024;       % 전기자 인덕턴스 [ H ]

% 원래는 분모가 2차방정식이나 
% 각속도(theta') ==> 각도(theta)로 output이 바뀌면서 적분형태로 1/s가 추가되어 3차방정식 형태가 된다.
%Kp = 44.8;
my_motor = K/(s*((J*s+b)*(L*s+R)+K^2));
>> bode(my_motor)
>> help margin
 margin  Gain and phase margins and crossover frequencies.
 
    [Gm,Pm,Wcg,Wcp] = margin(SYS) computes the gain margin Gm, the phase 
    margin Pm, and the associated frequencies Wcg and Wcp, for the SISO 
    open-loop model SYS (continuous or discrete). The gain margin Gm is 
    defined as 1/G where G is the gain at the -180 phase crossing. The 
    phase margin Pm is in degrees. The frequencies Wcg and Wcp are in 
    radians/TimeUnit (relative to the time units specified in SYS.TimeUnit, 
    the default being seconds).
 
    The gain margin in dB is derived by 
       Gm_dB = 20*log10(Gm)
    The loop gain at Wcg can increase or decrease by this many dBs before 
    losing stability, and Gm_dB<0 (Gm<1) means that stability is most 
    sensitive to loop gain reduction.  If there are several crossover 
    points, margin returns the smallest margins (gain margin nearest to 
    0dB and phase margin nearest to 0 degrees).
 
    For a S1-by...-by-Sp array of linear systems, margin returns 
    arrays of size [S1 ... Sp] such that
       [Gm(j1,...,jp),Pm(j1,...,jp)] = margin(SYS(:,:,j1,...,jp)) .  
 
    [Gm,Pm,Wcg,Wcp] = margin(MAG,PHASE,W) derives the gain and phase margins 
    from the Bode magnitude, phase, and frequency vectors MAG, PHASE, and W 
    produced by BODE. margin expects gain values MAG in absolute units and 
    phase values PHASE in degrees. Interpolation is performed between 
    frequency points to approximate the true stability margins.
 
    margin(SYS), by itself, plots the open-loop Bode plot with the gain 
    and phase margins marked with a vertical line. 
 
    See also allmargin, bodeplot, bode, ltiview, DynamicSystem.

    Overloaded methods:
       DynamicSystem/margin

    Reference page in Help browser
       doc margin

>> [Gm,Pm,Wcg,Wcp] = margin(my_motor))
 [Gm,Pm,Wcg,Wcp] = margin(my_motor))
                                   |
Error: Unbalanced or unexpected parenthesis or bracket.
 
>> [Gm,Pm,Wcg,Wcp] = margin(my_motor)

Gm =

   38.8458


Pm =

   79.8529


Wcg =

  306.6057


Wcp =

   20.6463

>> band = bandwidth(my_motor)
Warning: The "bandwidth" command returns NaN for models with infinite DC gain. 
> In warning at 26
  In DynamicSystem.bandwidth at 37 

band =

   NaN

>> my_motor

my_motor =
 
                    0.0245
  ------------------------------------------
  1.248e-08 s^3 + 1.012e-05 s^2 + 0.001173 s
 
Continuous-time transfer function.

>> csys=feedback(my_motor,1)

csys =
 
                        0.0245
  ---------------------------------------------------
  1.248e-08 s^3 + 1.012e-05 s^2 + 0.001173 s + 0.0245
 
Continuous-time transfer function.

>> pole(csys)

ans =

 -676.5522
 -107.7253
  -26.9360

>> h=1-csys

h =
 
      1.248e-08 s^3 + 1.012e-05 s^2 + 0.001173 s
  ---------------------------------------------------
  1.248e-08 s^3 + 1.012e-05 s^2 + 0.001173 s + 0.0245
 
Continuous-time transfer function.

>> H=h/s

H =
 
        1.248e-08 s^3 + 1.012e-05 s^2 + 0.001173 s
  -------------------------------------------------------
  1.248e-08 s^4 + 1.012e-05 s^3 + 0.001173 s^2 + 0.0245 s
 
Continuous-time transfer function.

>> Y=0.0245/0.001173

Y =

   20.8866

>> [Gm,Pm,Wcg,Wcp] = margin(my_motor))
 [Gm,Pm,Wcg,Wcp] = margin(my_motor))
                                   |
Error: Unbalanced or unexpected parenthesis or bracket.
 
>> [Gm,Pm,Wcg,Wcp] = margin(my_motor)

Gm =

   38.8458


Pm =

   79.8529


Wcg =

  306.6057


Wcp =

   20.6463

>> sys=100*my_motor

sys =
 
                     2.45
  ------------------------------------------
  1.248e-08 s^3 + 1.012e-05 s^2 + 0.001173 s
 
Continuous-time transfer function.

>> [Gm,Pm,Wcg,Wcp] = margin(sys)
Warning: The closed-loop system is unstable. 
> In warning at 26
  In DynamicSystem.margin at 63 

Gm =

    0.3885


Pm =

  -19.1397


Wcg =

  306.6057


Wcp =

  478.1455

>> bode(sys)
>> wz=478.1455

wz =

  478.1455

>> ld=100*(1+s/478.14)/(1+s/47814)

ld =
 
  4.781e06 s + 2.286e09
  ---------------------
   478.1 s + 2.286e07
 
Continuous-time transfer function.

>> sys=mymotor*ld
Undefined function or variable 'mymotor'.
 
Did you mean:
>> sys=my_motor*ld

sys =
 
                1.171e05 s + 5.601e07
  -------------------------------------------------
  5.967e-06 s^4 + 0.2902 s^3 + 232 s^2 + 2.682e04 s
 
Continuous-time transfer function.

>> bode(sys)
>> [Gm,Pm,Wcg,Wcp] = margin(sys)

Gm =

   38.8269


Pm =

   22.5056


Wcg =

   3.9709e+03


Wcp =

  581.7212

>> [Gm,Pm,Wcg,Wcp] = margin(sys)

Gm =

   38.8269


Pm =

   22.5056


Wcg =

   3.9709e+03


Wcp =

  581.7212

>> sys2=sys*ld

sys2 =
 
                 5.601e11 s^2 + 5.356e14 s + 1.281e17
  -------------------------------------------------------------------
  0.002853 s^5 + 275.2 s^4 + 6.744e06 s^3 + 5.317e09 s^2 + 6.132e11 s
 
Continuous-time transfer function.

>> [Gm,Pm,Wcg,Wcp] = margin(sys2)

Gm =

    1.1069


Pm =

    2.9695


Wcg =

   4.7669e+04


Wcp =

   4.5252e+04

>> ld2=(1+s/478.14)/(1+s/47814)

ld2 =
 
  47814 s + 2.286e07
  ------------------
  478.1 s + 2.286e07
 
Continuous-time transfer function.

>> sys2=sys*ld2

sys2 =
 
                 5.601e09 s^2 + 5.356e12 s + 1.281e15
  -------------------------------------------------------------------
  0.002853 s^5 + 275.2 s^4 + 6.744e06 s^3 + 5.317e09 s^2 + 6.132e11 s
 
Continuous-time transfer function.

>> [Gm,Pm,Wcg,Wcp] = margin(sys2)

Gm =

  110.6887


Pm =

   77.1621


Wcg =

   4.7669e+04


Wcp =

  873.4940

>> ld3=(1+s/478.14)/(1+s/4781.4)

ld3 =
 
  4781 s + 2.286e06
  ------------------
  478.1 s + 2.286e06
 
Continuous-time transfer function.

>> sys3=my_motor*100*ld3*ld3

sys3 =
 
                 5.601e07 s^2 + 5.356e10 s + 1.281e13
  ------------------------------------------------------------------
  0.002853 s^5 + 29.6 s^4 + 8.763e04 s^3 + 5.548e07 s^2 + 6.132e09 s
 
Continuous-time transfer function.

>> [Gm,Pm,Wcg,Wcp] = margin(sys3)

Gm =

   10.4616


Pm =

   58.7848


Wcg =

   4.6326e+03


Wcp =

  848.8140

>> bode(sys2)
>> lg=(1+s/0.02)/(1+s/0.000894)

lg =
 
  0.000894 s + 1.788e-05
  ----------------------
    0.02 s + 1.788e-05
 
Continuous-time transfer function.

>> sys3=sys2*lg

sys3 =
 
                                                              
            5.007e06 s^3 + 4.789e09 s^2 + 1.145e12 s + 2.29e10
                                                              
  -----------------------------------------------------------------------
                                                                         
  5.706e-05 s^6 + 5.503 s^5 + 1.349e05 s^4 + 1.063e08 s^3 + 1.226e10 s^2 
                                                                         
                                                             + 1.096e07 s
                                                                         
 
Continuous-time transfer function.

>> bode(sys3)
>> [Gm,Pm,Wcg,Wcp] = margin(sys3)

Gm =

   2.4763e+03


Pm =

   71.9050


Wcg =

   4.7669e+04


Wcp =

   82.2312

>> lg2=(1+s/0.02)(1+s/0.011905)
 lg2=(1+s/0.02)(1+s/0.011905)
               |
Error: Unbalanced or unexpected parenthesis or bracket.
 
>> lg2=(1+s/0.02)/(1+s/0.011905)

lg2 =
 
  0.01191 s + 0.0002381
  ---------------------
   0.02 s + 0.0002381
 
Continuous-time transfer function.

>> sys4=sys2*lg2

sys4 =
 
                                                               
            6.668e07 s^3 + 6.377e10 s^2 + 1.525e13 s + 3.049e11
                                                               
  -----------------------------------------------------------------------
                                                                         
  5.706e-05 s^6 + 5.503 s^5 + 1.349e05 s^4 + 1.063e08 s^3 + 1.227e10 s^2 
                                                                         
                                                              + 1.46e08 s
                                                                         
 
Continuous-time transfer function.

>> [Gm,Pm,Wcg,Wcp] = margin(sys4)

Gm =

  185.9532


Pm =

   71.6555


Wcg =

   4.7669e+04


Wcp =

  551.0048

>> lg3=(1+s/0.04)/(1+s/0.023810)

lg3 =
 
  0.02381 s + 0.0009524
  ---------------------
   0.04 s + 0.0009524
 
Continuous-time transfer function.

>> sys5=sys2*lg3

sys5 =
 
                                                              
            1.334e08 s^3 + 1.275e11 s^2 + 3.049e13 s + 1.22e12
                                                              
  -----------------------------------------------------------------------
                                                                         
  0.0001141 s^6 + 11.01 s^5 + 2.698e05 s^4 + 2.127e08 s^3 + 2.453e10 s^2 
                                                                         
                                                              + 5.84e08 s
                                                                         
 
Continuous-time transfer function.

>> [Gm,Pm,Wcg,Wcp] = margin(sys5)

Gm =

  185.9532


Pm =

   71.6547


Wcg =

   4.7669e+04


Wcp =

  551.0048

>> lg3=(1+s/0.4)/(1+s/0.23810)

lg3 =
 
  0.2381 s + 0.09524
  ------------------
   0.4 s + 0.09524
 
Continuous-time transfer function.

>> sys5=sys2*lg3

sys5 =
 
                                                              
            1.334e09 s^3 + 1.276e12 s^2 + 3.054e14 s + 1.22e14
                                                              
  -----------------------------------------------------------------------
                                                                         
  0.001141 s^6 + 110.1 s^5 + 2.698e06 s^4 + 2.127e09 s^3 + 2.458e11 s^2  
                                                                         
                                                              + 5.84e10 s
                                                                         
 
Continuous-time transfer function.

>> [Gm,Pm,Wcg,Wcp] = margin(sys5)

Gm =

  185.9520


Pm =

   71.6396


Wcg =

   4.7669e+04


Wcp =

  551.0049

>> sys5=sys5*lg3

sys5 =
 
                                                                      
    3.175e08 s^4 + 3.039e11 s^3 + 7.284e13 s^2 + 5.812e13 s + 1.162e13
                                                                      
  -----------------------------------------------------------------------
                                                                         
  0.0004565 s^7 + 44.03 s^6 + 1.079e06 s^5 + 8.512e08 s^4 + 9.852e10 s^3 
                                                                         
                                              + 4.677e10 s^2 + 5.562e09 s
                                                                         
 
Continuous-time transfer function.

>> [Gm,Pm,Wcg,Wcp] = margin(sys5)

Gm =

  312.3911


Pm =

   66.3251


Wcg =

   4.7668e+04


Wcp =

  367.6367

>> lg4=(1+s/0.2)/(1+s/0.005953)

lg4 =
 
  0.005953 s + 0.001191
  ---------------------
    0.2 s + 0.001191
 
Continuous-time transfer function.

>> lg4=(1+s/0.04)/(1+s/0.011905)

lg4 =
 
  0.01191 s + 0.0004762
  ---------------------
   0.04 s + 0.0004762
 
Continuous-time transfer function.

>> lg5=(1+s/0.01)/(1+s/0.011905)

lg5 =
 
  0.01191 s + 0.0001191
  ---------------------
   0.01 s + 0.0001191
 
Continuous-time transfer function.

>> sys8=sys2*lg4*lg5

sys8 =
 
                                                                      
    7.938e05 s^4 + 7.592e08 s^3 + 1.815e11 s^2 + 9.075e09 s + 7.259e07
                                                                      
  -----------------------------------------------------------------------
                                                                         
  1.141e-06 s^7 + 0.1101 s^6 + 2698 s^5 + 2.127e06 s^4 + 2.453e08 s^3    
                                                                         
                                               + 5.84e06 s^2 + 3.476e04 s
                                                                         
 
Continuous-time transfer function.

>> [Gm,Pm,Wcg,Wcp] = margin(sys8)

Gm =

  312.3950


Pm =

   66.3714


Wcg =

   4.7669e+04


Wcp =

  367.6365

>> bode(sys8)
>> 

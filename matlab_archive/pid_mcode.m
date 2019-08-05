% matlab ==> 디지털제어 프로젝트 중 PID를 실행한 코드

>> J = 52E-7;
b = 3.141E-3;
K = 0.0245;
R = 1.8;
L = 0.0024;
s = tf('s');
P_motor = K/(s*((J*s+b)*(L*s+R)+K^2));
step(P_motor)
>> rlocus(P_motor)
title('Root Locus - P Control')
sgrid(.5, 0)
sigrid(100)
Undefined function 'sigrid' for input arguments of type 'double'.
 
Did you mean:
>> sgrid(100)
>> rltool(P_motor)
>>  rlocus(P_motor)
title('Root Locus - P Control')
>> P_motor = 44.8*K/(s*((J*s+b)*(L*s+R)+K^2));
step(P_motor)
Error using DynamicSystem/step (line 96)
Plots must be of the same type and size to be superimposed.
 
>> 
>> P_motor = 44.8*K/(s*((J*s+b)*(L*s+R)+K^2));
>> step(P_motor)
Error using DynamicSystem/step (line 96)
Plots must be of the same type and size to be superimposed.
 
>> P_mo
Undefined function or variable 'P_mo'.
 
>> P_motor

P_motor =
 
                    1.098
  -----------------------------------------
  1.248e-08 s^3 + 1.69e-05 s^2 + 0.006254 s
 
Continuous-time transfer function.

>> P_motor

P_motor =
 
                    1.098
  -----------------------------------------
  1.248e-08 s^3 + 1.69e-05 s^2 + 0.006254 s
 
Continuous-time transfer function.

>> step(P_motor)
>> aaa  = feedback(P_motor)
Error using InputOutputModel/feedback (line 47)
Not enough input arguments.
 
>> aaa  = feedback(P_motor,1)

aaa =
 
                        1.098
  -------------------------------------------------
  1.248e-08 s^3 + 1.69e-05 s^2 + 0.006254 s + 1.098
 
Continuous-time transfer function.

>> step(aaa)
>> dist_Cl=feedback(aaa);
Error using InputOutputModel/feedback (line 47)
Not enough input arguments.
 
>> P_motor = P_motor / 44.8

P_motor =
 
                   1.098
  ---------------------------------------
  5.591e-07 s^3 + 0.000757 s^2 + 0.2802 s
 
Continuous-time transfer function.

>> dist_cl=feedback(P_motor,44.8)

dist_cl =
 
                       1.098
  -----------------------------------------------
  5.591e-07 s^3 + 0.000757 s^2 + 0.2802 s + 49.17
 
Continuous-time transfer function.

>> step(dist_cl)
>> lag = (s+0.1)/(s+0.00434)

lag =
 
    s + 0.1
  -----------
  s + 0.00434
 
Continuous-time transfer function.

>> Lag= 44.8*lag

Lag =
 
  44.8 s + 4.48
  -------------
   s + 0.00434
 
Continuous-time transfer function.

>> super= Lag*P_motor;
>> step(super)
>> real=feedback(super,1);
>> step(real)
>> dis_cl=feedback(P_motor,super);
>> step(dis_cl)
>> dis_cl=feedback(P_motor,Lag);
>> step(dis_cl)
>> 
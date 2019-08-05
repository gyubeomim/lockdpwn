% matlab ==> µðÁöÅÐÁ¦¾î ÇÁ·ÎÁ§Æ® Áß Root Locus¸¦ ½ÇÇàÇÑ ÄÚµå
>> s = tf('s');

J = 52E-7;        % ì§ˆëŸ‰ê´?„±ëª¨ë©˜??[ kg * m^2 ]
b = 3.1831E-4;   % ?ì„±ë§ˆì°°ê³„ìˆ˜ [ Nm*s/rad ]  % pdf??Speed Regulation Constantë¡?ë¶?„° ?»ëŠ”??% 3.141e-03
K = 0.0245;       % Kt ,? í¬?ìˆ˜ [ Nm/A ] 
                      % Ke ,??¸°?„ë ¥?ìˆ˜ [ V*s/rad ] ?˜ì? ?µìƒ ê°™ì? ê°’ìœ¼ë¡??œë‹¤ 
R = 1.8;           % ?„ê¸°??ì§ë ¬??•­ [ Ohm ]
L = 0.0024;       % ?„ê¸°???¸ë•?´ìŠ¤ [ H ]
>> 
>> my_motor = K/(s*((J*s+b)*(L*s+R)+K^2));
rlocus(my_motor)
>> motor=2.75*K/(s*((J*s+b)*(L*s+R)+K^2));
>> close = feedback(motor,1)

close =
 
                        0.06738
  ----------------------------------------------------
  1.248e-08 s^3 + 1.012e-05 s^2 + 0.001173 s + 0.06738
 
Continuous-time transfer function.

>> step(close)
>> title('Closed loop step response when K = 2.75 controller','fontsize',20)
>> LC=(s+76)/(s+760);
>> Newsys=motor*LC;
>> rlocus(Newsys)
>> Newsys=my_motor*LC;
>> Newsys

Newsys =
 
                     0.0245 s + 1.862
  -------------------------------------------------------
  1.248e-08 s^4 + 1.961e-05 s^3 + 0.008867 s^2 + 0.8916 s
 
Continuous-time transfer function.

>> rlocus(Newsys)
>> newsys=43.9*Newsys

newsys =
 
                      1.076 s + 81.74
  -------------------------------------------------------
  1.248e-08 s^4 + 1.961e-05 s^3 + 0.008867 s^2 + 0.8916 s
 
Continuous-time transfer function.

>> newclose=feedback(newsys,1)

newclose =
 
                         1.076 s + 81.74
  --------------------------------------------------------------
  1.248e-08 s^4 + 1.961e-05 s^3 + 0.008867 s^2 + 1.967 s + 81.74
 
Continuous-time transfer function.

>> step(newclose)
>> LC=(s+76)/(s+380)

LC =
 
  s + 76
  -------
  s + 380
 
Continuous-time transfer function.

>> newsys=my_motor*LC

newsys =
 
                     0.0245 s + 1.862
  ------------------------------------------------------
  1.248e-08 s^4 + 1.487e-05 s^3 + 0.00502 s^2 + 0.4458 s
 
Continuous-time transfer function.

>> rlocus(newsys)
>> realsys=15.8*newsys;
>> closesys=feedback(realsys,1);
>> step(closesys)
>> LC=(s+80)/(s+800);
>> newsys

newsys =
 
                     0.0245 s + 1.862
  ------------------------------------------------------
  1.248e-08 s^4 + 1.487e-05 s^3 + 0.00502 s^2 + 0.4458 s
 
Continuous-time transfer function.

>> newsys=my_motor*LC

newsys =
 
                      0.0245 s + 1.96
  -------------------------------------------------------
  1.248e-08 s^4 + 2.011e-05 s^3 + 0.009272 s^2 + 0.9386 s
 
Continuous-time transfer function.

>> rlocus(newsys)
>> new=newsys*47.2

new =
 
                      1.156 s + 92.51
  -------------------------------------------------------
  1.248e-08 s^4 + 2.011e-05 s^3 + 0.009272 s^2 + 0.9386 s
 
Continuous-time transfer function.

>> nc=feedback(new,1)

nc =
 
                         1.156 s + 92.51
  --------------------------------------------------------------
  1.248e-08 s^4 + 2.011e-05 s^3 + 0.009272 s^2 + 2.095 s + 92.51
 
Continuous-time transfer function.

>> step(nc)
>> LC=(s+80)/(s+400)

LC =
 
  s + 80
  -------
  s + 400
 
Continuous-time transfer function.

>> new=my_motor*LC

new =
 
                      0.0245 s + 1.96
  -------------------------------------------------------
  1.248e-08 s^4 + 1.512e-05 s^3 + 0.005223 s^2 + 0.4693 s
 
Continuous-time transfer function.

>> rlocus(new)
>> sys=new*17

sys =
 
                     0.4165 s + 33.32
  -------------------------------------------------------
  1.248e-08 s^4 + 1.512e-05 s^3 + 0.005223 s^2 + 0.4693 s
 
Continuous-time transfer function.

>> csys=feedback(sys,1)

csys =
 
                         0.4165 s + 33.32
  ---------------------------------------------------------------
  1.248e-08 s^4 + 1.512e-05 s^3 + 0.005223 s^2 + 0.8858 s + 33.32
 
Continuous-time transfer function.

>> step(csys)
>> rlocus(new)
>> sys=new*47.2

sys =
 
                      1.156 s + 92.51
  -------------------------------------------------------
  1.248e-08 s^4 + 1.512e-05 s^3 + 0.005223 s^2 + 0.4693 s
 
Continuous-time transfer function.

>> sys=new*47.6

sys =
 
                      1.166 s + 93.3
  -------------------------------------------------------
  1.248e-08 s^4 + 1.512e-05 s^3 + 0.005223 s^2 + 0.4693 s
 
Continuous-time transfer function.

>> csys=feedback(sys,1)

csys =
 
                         1.166 s + 93.3
  -------------------------------------------------------------
  1.248e-08 s^4 + 1.512e-05 s^3 + 0.005223 s^2 + 1.635 s + 93.3
 
Continuous-time transfer function.

>> step(sys)
>> step(csys)
>> sys=new*30

sys =
 
                      0.735 s + 58.8
  -------------------------------------------------------
  1.248e-08 s^4 + 1.512e-05 s^3 + 0.005223 s^2 + 0.4693 s
 
Continuous-time transfer function.

>> csys=feedback(sys,1)

csys =
 
                         0.735 s + 58.8
  -------------------------------------------------------------
  1.248e-08 s^4 + 1.512e-05 s^3 + 0.005223 s^2 + 1.204 s + 58.8
 
Continuous-time transfer function.

>> step(csys)
>> rlocus(new)
>> p = pole(my_motor)

p =

         0
 -671.1435
 -140.0700

>> LC=(s+140.0700)/(s+159.1)

LC =
 
  s + 140.1
  ---------
  s + 159.1
 
Continuous-time transfer function.

>> sys=my_motor*LC

sys =
 
                     0.0245 s + 3.432
  -------------------------------------------------------
  1.248e-08 s^4 + 1.211e-05 s^3 + 0.002784 s^2 + 0.1867 s
 
Continuous-time transfer function.

>> rlocus(sys)
>> LC=(s+140.1)/(s+170)

LC =
 
  s + 140.1
  ---------
   s + 170
 
Continuous-time transfer function.

>> sys=my_motor*LC

sys =
 
                     0.0245 s + 3.432
  -------------------------------------------------------
  1.248e-08 s^4 + 1.225e-05 s^3 + 0.002894 s^2 + 0.1994 s
 
Continuous-time transfer function.

>> rlocus(sys)
>> real=3.8*sys

real =
 
                     0.0931 s + 13.04
  -------------------------------------------------------
  1.248e-08 s^4 + 1.225e-05 s^3 + 0.002894 s^2 + 0.1994 s
 
Continuous-time transfer function.

>> creal=feedback(real,1)

creal =
 
                         0.0931 s + 13.04
  ---------------------------------------------------------------
  1.248e-08 s^4 + 1.225e-05 s^3 + 0.002894 s^2 + 0.2925 s + 13.04
 
Continuous-time transfer function.

>> step(creal)
>> z = zero(my_motor)

z =

   Empty matrix: 0-by-1

>> LC=(s+140.1)/(s+200)

LC =
 
  s + 140.1
  ---------
   s + 200
 
Continuous-time transfer function.

>> real=my_motor*LC

real =
 
                     0.0245 s + 3.432
  -------------------------------------------------------
  1.248e-08 s^4 + 1.262e-05 s^3 + 0.003198 s^2 + 0.2346 s
 
Continuous-time transfer function.

>> rlocus(real)
>> LC=(s+140.1)/(s+180)

LC =
 
  s + 140.1
  ---------
   s + 180
 
Continuous-time transfer function.

>> real=my_motor*LC

real =
 
                     0.0245 s + 3.432
  -------------------------------------------------------
  1.248e-08 s^4 + 1.237e-05 s^3 + 0.002996 s^2 + 0.2112 s
 
Continuous-time transfer function.

>> rlocus(real)
>> sys=real*4.33

sys =
 
                     0.1061 s + 14.86
  -------------------------------------------------------
  1.248e-08 s^4 + 1.237e-05 s^3 + 0.002996 s^2 + 0.2112 s
 
Continuous-time transfer function.

>> csys=feedback(sys,1)

csys =
 
                         0.1061 s + 14.86
  ---------------------------------------------------------------
  1.248e-08 s^4 + 1.237e-05 s^3 + 0.002996 s^2 + 0.3173 s + 14.86
 
Continuous-time transfer function.

>> step(csys)
>> LC=(s+140.1)/(s+185)

LC =
 
  s + 140.1
  ---------
   s + 185
 
Continuous-time transfer function.

>> real=my_motor*LC

real =
 
                     0.0245 s + 3.432
  ------------------------------------------------------
  1.248e-08 s^4 + 1.243e-05 s^3 + 0.003046 s^2 + 0.217 s
 
Continuous-time transfer function.

>> rlocus(real)
>> sys=real*4.47

sys =
 
                     0.1095 s + 15.34
  ------------------------------------------------------
  1.248e-08 s^4 + 1.243e-05 s^3 + 0.003046 s^2 + 0.217 s
 
Continuous-time transfer function.

>> csys=feedback(sys,1)

csys =
 
                         0.1095 s + 15.34
  ---------------------------------------------------------------
  1.248e-08 s^4 + 1.243e-05 s^3 + 0.003046 s^2 + 0.3266 s + 15.34
 
Continuous-time transfer function.

>> step(csys)
>> LC=(s+140.1)/(s+190)

LC =
 
  s + 140.1
  ---------
   s + 190
 
Continuous-time transfer function.

>> real=my_motor*LC

real =
 
                     0.0245 s + 3.432
  ------------------------------------------------------
  1.248e-08 s^4 + 1.25e-05 s^3 + 0.003097 s^2 + 0.2229 s
 
Continuous-time transfer function.

>> 
>> rlocus(real)
>> sys=real*4.67

sys =
 
                     0.1144 s + 16.03
  ------------------------------------------------------
  1.248e-08 s^4 + 1.25e-05 s^3 + 0.003097 s^2 + 0.2229 s
 
Continuous-time transfer function.

>> csys=feedback(sys,1)

csys =
 
                         0.1144 s + 16.03
  --------------------------------------------------------------
  1.248e-08 s^4 + 1.25e-05 s^3 + 0.003097 s^2 + 0.3373 s + 16.03
 
Continuous-time transfer function.

>> step(csys)
>> sys=real*5

sys =
 
                     0.1225 s + 17.16
  ------------------------------------------------------
  1.248e-08 s^4 + 1.25e-05 s^3 + 0.003097 s^2 + 0.2229 s
 
Continuous-time transfer function.

>> csys=feedback(sys,1)

csys =
 
                         0.1225 s + 17.16
  --------------------------------------------------------------
  1.248e-08 s^4 + 1.25e-05 s^3 + 0.003097 s^2 + 0.3454 s + 17.16
 
Continuous-time transfer function.

>> step(csys)
>> sys=real*4.67

sys =
 
                     0.1144 s + 16.03
  ------------------------------------------------------
  1.248e-08 s^4 + 1.25e-05 s^3 + 0.003097 s^2 + 0.2229 s
 
Continuous-time transfer function.

>> pole(sys)

ans =

         0
 -671.1435
 -190.0000
 -140.0700

>> LC2=(s+671.1435)/(s+1000)

LC2 =
 
  s + 671.1
  ---------
  s + 1000
 
Continuous-time transfer function.

>> sys2=sys*LC2

sys2 =
 
                  0.1144 s^2 + 92.82 s + 1.076e04
  ----------------------------------------------------------------
  1.248e-08 s^5 + 2.498e-05 s^4 + 0.01559 s^3 + 3.32 s^2 + 222.9 s
 
Continuous-time transfer function.

>> csys2=feedback(sys2,1)

csys2 =
 
                                                     
                      0.1144 s^2 + 92.82 s + 1.076e04
                                                     
  -----------------------------------------------------------------------
                                                                         
  1.248e-08 s^5 + 2.498e-05 s^4 + 0.01559 s^3 + 3.434 s^2 + 315.7 s      
                                                                         
                                                               + 1.076e04
                                                                         
 
Continuous-time transfer function.

>> step(csys2)
>> real=my_motor*LC*LC2

real =
 
                    0.0245 s^2 + 19.88 s + 2304
  ----------------------------------------------------------------
  1.248e-08 s^5 + 2.498e-05 s^4 + 0.01559 s^3 + 3.32 s^2 + 222.9 s
 
Continuous-time transfer function.

>> rlocus(real)
>> sys2=real*7.56

sys2 =
 
                  0.1852 s^2 + 150.3 s + 1.742e04
  ----------------------------------------------------------------
  1.248e-08 s^5 + 2.498e-05 s^4 + 0.01559 s^3 + 3.32 s^2 + 222.9 s
 
Continuous-time transfer function.

>> csys2=feedback(sys2,1)

csys2 =
 
                                                     
                      0.1852 s^2 + 150.3 s + 1.742e04
                                                     
  -----------------------------------------------------------------------
                                                                         
  1.248e-08 s^5 + 2.498e-05 s^4 + 0.01559 s^3 + 3.505 s^2 + 373.2 s      
                                                                         
                                                               + 1.742e04
                                                                         
 
Continuous-time transfer function.

>> step(csys2)
>> LC2=(s+200)/(s+300)

LC2 =
 
  s + 200
  -------
  s + 300
 
Continuous-time transfer function.

>> real=my_motor*LC*LC2

real =
 
                     0.0245 s^2 + 8.332 s + 686.5
  ------------------------------------------------------------------
  1.248e-08 s^5 + 1.624e-05 s^4 + 0.006845 s^3 + 1.152 s^2 + 66.87 s
 
Continuous-time transfer function.

>> rlocus(real)
>> sys2=real*9.56

sys2 =
 
                     0.2342 s^2 + 79.66 s + 6563
  ------------------------------------------------------------------
  1.248e-08 s^5 + 1.624e-05 s^4 + 0.006845 s^3 + 1.152 s^2 + 66.87 s
 
Continuous-time transfer function.

>> csys2=feedback(sys2,1)

csys2 =
 
                                                   
                        0.2342 s^2 + 79.66 s + 6563
                                                   
  -----------------------------------------------------------------------
                                                                         
  1.248e-08 s^5 + 1.624e-05 s^4 + 0.006845 s^3 + 1.386 s^2 + 146.5 s     
                                                                         
                                                                   + 6563
                                                                         
 
Continuous-time transfer function.

>> step(csys2)
>> lag=(s+0.01)/(s+0.002)

lag =
 
  s + 0.01
  ---------
  s + 0.002
 
Continuous-time transfer function.

>> real2=my_motor*LC*LC2*lag

real2 =
 
                                                         
                 0.0245 s^3 + 8.333 s^2 + 686.6 s + 6.865
                                                         
  -----------------------------------------------------------------------
                                                                         
  1.248e-08 s^6 + 1.624e-05 s^5 + 0.006845 s^4 + 1.152 s^3 + 66.88 s^2   
                                                                         
                                                               + 0.1337 s
                                                                         
 
Continuous-time transfer function.

>> rlocus(real2)
>> sys3=real*9.43

sys3 =
 
                      0.231 s^2 + 78.58 s + 6474
  ------------------------------------------------------------------
  1.248e-08 s^5 + 1.624e-05 s^4 + 0.006845 s^3 + 1.152 s^2 + 66.87 s
 
Continuous-time transfer function.

>> csys3=feedback(sys3,1)

csys3 =
 
                                                  
                        0.231 s^2 + 78.58 s + 6474
                                                  
  -----------------------------------------------------------------------
                                                                         
  1.248e-08 s^5 + 1.624e-05 s^4 + 0.006845 s^3 + 1.383 s^2 + 145.4 s     
                                                                         
                                                                   + 6474
                                                                         
 
Continuous-time transfer function.

>> step(sys3)
>> step(csys3)
>> step(csys2)
>> rlocus(real)
>> sys3=real2*9.43

sys3 =
 
                                                        
                  0.231 s^3 + 78.58 s^2 + 6474 s + 64.74
                                                        
  -----------------------------------------------------------------------
                                                                         
  1.248e-08 s^6 + 1.624e-05 s^5 + 0.006845 s^4 + 1.152 s^3 + 66.88 s^2   
                                                                         
                                                               + 0.1337 s
                                                                         
 
Continuous-time transfer function.

>> csys3=feedback(sys3,1)

csys3 =
 
                                                        
                  0.231 s^3 + 78.58 s^2 + 6474 s + 64.74
                                                        
  -----------------------------------------------------------------------
                                                                         
  1.248e-08 s^6 + 1.624e-05 s^5 + 0.006845 s^4 + 1.383 s^3 + 145.5 s^2   
                                                                         
                                                         + 6475 s + 64.74
                                                                         
 
Continuous-time transfer function.

>> step(csys3)
>> real

real =
 
                     0.0245 s^2 + 8.332 s + 686.5
  ------------------------------------------------------------------
  1.248e-08 s^5 + 1.624e-05 s^4 + 0.006845 s^3 + 1.152 s^2 + 66.87 s
 
Continuous-time transfer function.

>> sys2=real*9.41

sys2 =
 
                     0.2305 s^2 + 78.41 s + 6460
  ------------------------------------------------------------------
  1.248e-08 s^5 + 1.624e-05 s^4 + 0.006845 s^3 + 1.152 s^2 + 66.87 s
 
Continuous-time transfer function.

>> csys2=feedback(sys2,1)

csys2 =
 
                                                   
                        0.2305 s^2 + 78.41 s + 6460
                                                   
  -----------------------------------------------------------------------
                                                                         
  1.248e-08 s^5 + 1.624e-05 s^4 + 0.006845 s^3 + 1.382 s^2 + 145.3 s     
                                                                         
                                                                   + 6460
                                                                         
 
Continuous-time transfer function.

>> step(csys2)
>> 

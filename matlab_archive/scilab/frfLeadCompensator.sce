// scilab ==> design lead Compensator in frequency response 
clear,clc

s = poly(0,'s');
gs = 4/(s^3 + 3*s^2 + 2*s);
gs = syslin('c',gs);
kgs = 5*gs;
ds1 = (1 + s/2) / (1 + s/200);
ds2 = (1+s/3) /(1+s/300);
ds3 = (1+s/2) * (1+s/2) / (1+s/20) / (1+s/20);
ds4 = (1+s/2) * (1+s/2) / (1+s/200) / (1+s/200);
ds5 = (1+s/2) * (1+s/2) * (1+s/2) / (1+s/20) / (1+s/20) / (1+s/20);

kdgs1 = kgs * ds1;
kdgs2 = kgs * ds2;
kdgs3 = kgs * ds3;
kdgs4 = kgs * ds4;
kdgs5 = kgs * ds5;

p_margin(kdgs1)
p_margin(kdgs2)
p_margin(kdgs3)
p_margin(kdgs4)
p_margin(kdgs5)



function v = freefall(t,m,cd)
%
g = 9.81;
v= sqrt(g*m/cd)* tanh(sqrt(g*cd/m)*t);
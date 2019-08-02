function v = freefallsubfunc(t ,m ,cd)
v = vel(t,m,cd);
end

function v = vel(t,m,cd)
g = 9.81;
v = sqrt(g*m/cd)*tanh(sqrt(g*cd/m)*t);
end

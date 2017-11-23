clear,clc;
function fout = factor(n)

% factor(n):
% Computes the product of all the integers from 1 to n

x =1;
for i = 1:n
    x = x*i;
end

fout = x;
end

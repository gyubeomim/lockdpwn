function [X] = Triangulation(P1, P2, x1, x2)
    n = size(x1,1);
    X = zeros(n, 3);
    for iIter = 1:n
        u = x1(iIter, :); v = x2(iIter, :);
        skewU = [ 0     -1      u(2);
                  1     0       -u(1);
                  -u(2) u(1)    0];
        skewV = [ 0     -1      v(2);
                  1     0       -v(1);
                  -v(2) v(1)    0];
        
        A = [skewU * P1; skewV * P2];
        [~, ~, V] = svd(A);
        X(iIter, :) = transpose(V(1:3, end)/V(end,end));
    end
end
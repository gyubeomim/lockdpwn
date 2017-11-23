<<<<<<< HEAD
function xs = f_runningsum(x)

% This function implements running sum of input vector x

n = length(x);
xs = zeros(size(x));

for i = 1 : length(x)
    
    xs(i) = sum(x(1:i));
    
=======
function xs = f_runningsum(x)

% This function implements running sum of input vector x

n = length(x);
xs = zeros(size(x));

for i = 1 : length(x)
    
    xs(i) = sum(x(1:i));
    
>>>>>>> 1c09010ef4f575c84c998f27e33251ff22ca30a8
end
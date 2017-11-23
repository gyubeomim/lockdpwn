function fprintfdemo

x = [1:5];
y= [20.4 12.6 17.8 88.7 120.4];
z = [x;y];
fprintf('    x        y\n');
fprintf('%5d %10.3f\n',z);
end

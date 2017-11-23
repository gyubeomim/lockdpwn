figure(1)

plot(x_r, y_r,'r:');
grid on
hold on
plot(x_global, y_global);
xlabel('x[meter]');
ylabel('y[meter]');
legend('reference trajectory', 'vehicle trajectory');
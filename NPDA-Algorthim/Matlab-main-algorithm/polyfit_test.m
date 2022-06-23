function polyfit_test()

x = (0:0.1:10);
y = -5*x.^2+23*x+7;

p = polyfit(x, y, 2);
fprintf('%f\t%f\t%f\n', p(1), p(2), p(3));
end

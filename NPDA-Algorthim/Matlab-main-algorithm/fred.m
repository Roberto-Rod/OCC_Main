function fred()

a = [1 2 3 4 5 6 7];
b = [-4 1 12 29 52 81 116];

q = polyfit(a, b, 2);

fprintf('%f\t%f\n', q(1), q(2), q(3));

end

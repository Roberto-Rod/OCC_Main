function flipper(filename)

data = dlmread(char(filename),',');
pos = data(:, 1);
n = size(data, 2);
fprintf('%i\n', n);
d = data(:, 2:n);
e = flip(d, 1);
f = [pos, e];
outfile = ['fl ', filename];
dlmwrite(outfile, f);

end

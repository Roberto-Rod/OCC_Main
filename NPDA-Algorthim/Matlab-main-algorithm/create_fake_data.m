function create_fake_data(datapath, a, b, width)

gamma = (width / 2);

datasize = 5000;
data = zeros(datasize, 6);

for x = 1:datasize
    data(x, 1) = (x - 1)/1000;
    data(x, 2) = 10000 * gamma^2 * (1 / (gamma^2 + (x - a)^2) + 1 /(gamma^2 + (x - b)^2));
end

data(:,3) = data(:, 2);
data(:,4) = data(:, 2);
data(:,5) = data(:, 2);
data(:,6) = data(:, 2);

fname = strcat(num2str(a/1000, '%1.3f'), 'mm-Raw.csv');
fname(2) = '-';
fake_data_file = strcat(datapath, '\', fname);

dlmwrite(fake_data_file, data);
    
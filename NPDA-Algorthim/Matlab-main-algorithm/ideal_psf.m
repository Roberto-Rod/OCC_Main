function ideal_psf()

filename = 'C:\Users\james\OneDrive\Documents\Occuity\Pachymetry\Idealised signal wrt time.csv';

data = dlmread(filename, ',', 0, 5);
size(data)
xnew = 0:0.1e-6:0.0037655;
xnew = xnew';
size(xnew)
ynew = interp1(data(:, 1), data(:, 2), xnew, 'spline');
dlmwrite('C:\Users\james\OneDrive\Documents\Occuity\Pachymetry\Ideal signal.csv', ynew, ',');
end


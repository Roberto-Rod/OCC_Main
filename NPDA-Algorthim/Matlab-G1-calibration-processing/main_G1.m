
function [ output_args ] = main_G1( data_file, cal_file )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

alpha = 0.0197;     % Difference between ng and np for water at 1310nm

calinfo = dlmread(cal_file);            % Calibration data

conflcidata = dlmread(data_file);
% File containing the data for confocal and LCI meaurements in alternate
% columns. Note that confocal is assumed not to be calibrated: the
% calibration is performed offline. The -scan.csv file should be used here:
% this includes the filtering performed by gConfocal. It is essential that
% the LCI signal is filtered: here it is assumed that a 4x 64 point MA
% filter has been used (earlier found to be optimum). Filtering on the 
% confocal signal is not as critical, but the same filter is applied to 
% both channels so it is assumed that the same 4x 64 point MA filter is
% used here.

conflcidata = calibrate_G1_confocal(conflcidata, calinfo);
% Fit the calibration to the confocal part of the data.

% Load peaks for convolution filtering
% Both confocal and LCI peaks are convolution filtered.
Lorentzians = dlmread('C:\Users\JamesReynolds\Documents\Matlab scripts\G1 scripts\Lorentzians.csv');

% Perform the convolution filter
% NOTE: convolution filters must be applied separately to each row, i.e. no
% averaging, in order to take advantage of the simultaneity of the two
% measurements.
convolved_data = conflcidata;
[convolved_data, peaks] = perform_convolution(conflcidata, Lorentzians);
dlmwrite('C:\Users\JamesReynolds\Documents\Matlab scripts\G1 scripts\Convolved data.csv', convolved_data);
dlmwrite('C:\Users\JamesReynolds\Documents\Matlab scripts\G1 scripts\Peak data.csv', peaks);

for i = 1: floor(length(peaks) / 2)
    spacing_conf(i) = peaks(3, 2*i) - peaks(2, 2*i);
    spacing_lci(i) = peaks(3, 2*i+1) - peaks(2, 2*i+1);
    for j = 1:4
        peakpos_conf(j, i) = peaks(j, 2*i);
        peakpos_lci(j, i) = peaks(j, 2*i+1);
    end
end
conf_mean = mean(peakpos_conf, 2);
lci_mean = mean(peakpos_lci, 2);

fprintf('Confocal peaks\t%f\t%f\t%f\t%f\n', conf_mean(1), conf_mean(2), conf_mean(3), conf_mean(4));
fprintf('LCI peaks\t%f\t%f\t%f\t%f\n', lci_mean(1), lci_mean(2), lci_mean(3), lci_mean(4));

spacing_conf = spacing_conf(2: length(spacing_conf));
spacing_lci = spacing_lci(2: length(spacing_lci));
% Remove the first measurement (which is generally poor)
spacing_conf = hampel_filter(spacing_conf, 2.5);
spacing_lci = hampel_filter(spacing_lci, 2.5);

fprintf('Confocal spacing\t%f\t%f um\n', mean(spacing_conf), std(spacing_conf));
fprintf('LCI spacing\t%f\t%f um\n', mean(spacing_lci), std(spacing_lci));

aa = alpha / 2;
ri = sqrt(aa^2 + spacing_lci ./ spacing_conf) - aa;
% Refractive index
ri = hampel_filter(ri, 2.5);

thickness = sqrt(ri .* spacing_lci .* spacing_conf ./ (ri + alpha));
thickness = hampel_filter(thickness, 2.5);

mean_ri = mean(ri);
sd_ri = std(ri);
mean_thickness = mean(thickness);
sd_thickness = std(thickness);

fprintf('Refractive index\t%f\t%f\n', mean_ri, sd_ri);
fprintf('Thickness\t%f\t%f mm\n', mean_thickness, sd_thickness);
fprintf('%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n', mean(spacing_conf), std(spacing_conf),  mean(spacing_lci), std(spacing_lci), mean_ri, sd_ri, mean_thickness, sd_thickness);

end


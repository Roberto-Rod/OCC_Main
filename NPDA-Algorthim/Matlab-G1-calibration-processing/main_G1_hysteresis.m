function [ output_args ] = main_G1_hysteresis( data_file, cal_file )
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
dlmwrite('C:\Users\JamesReynolds\Documents\Matlab scripts\G1 scripts\Peak data.csv', peaks(:,:,1));
dlmwrite('C:\Users\JamesReynolds\Documents\Matlab scripts\G1 scripts\Peak height data.csv', peaks(:,:,2));

for i = 1: floor(length(peaks) / 2)
    spacing_conf(i) = peaks(3, 2*i, 1) - peaks(2, 2*i, 1);
    spacing_lci(i) = peaks(3, 2*i+1, 1) - peaks(2, 2*i+1, 1);
    for j = 1:4
        peakpos_conf(j, i) = peaks(j, 2*i, 1);
        peakpos_lci(j, i) = peaks(j, 2*i+1, 1);
        peakheight_conf(j, i) = peaks(j, 2*i, 2);
        peakheight_lci(j, i) = peaks(j, 2*i+1, 2);
    end
end
conf_mean = mean(peakpos_conf, 2);
lci_mean = mean(peakpos_lci, 2);
conf_h_mean = mean(peakheight_conf, 2);
lci_h_mean = mean(peakheight_lci, 2);

fprintf('Confocal peaks\t%f\t%f\t%f\t%f\n', conf_mean(1), conf_mean(2), conf_mean(3), conf_mean(4));
fprintf('LCI peaks\t%f\t%f\t%f\t%f\n', lci_mean(1), lci_mean(2), lci_mean(3), lci_mean(4));

%spacing_conf = spacing_conf(2: length(spacing_conf));
%spacing_lci = spacing_lci(2: length(spacing_lci));
% Remove the first measurement (which is generally poor)

% Split into the two directions


fprintf('Confocal spacing\t%f\t%f um\n', mean(spacing_conf), std(spacing_conf));
fprintf('LCI spacing\t%f\t%f um\n', mean(spacing_lci), std(spacing_lci));

% Calculate refractive indices and thicknesses
aa = alpha / 2;
ri = sqrt(aa^2 + spacing_lci ./ spacing_conf) - aa;
thickness = sqrt(ri .* spacing_lci .* spacing_conf ./ (ri + alpha));

% Sort by refractive index 
% (Necessary because of hysteresis and forward/backward scans are not
% neatly arranged)
[s_spacing_conf, ind] = sort(spacing_conf);
s_ri = ri(ind);
s_thickness = thickness(ind);
s_conf = spacing_conf(ind);
s_lci = spacing_lci(ind);

% Find the position of maximum spacing, i.e. split into two groups
diff = 0;
v = length(s_spacing_conf);
max_space = floor(v / 2);  % Default
for i = floor(0.4 * v): ceil(0.6 * v)
    a = s_spacing_conf(i+1) - s_spacing_conf(i);
    if a > diff
        diff = a;
        max_space = i;
    end
end

ri1 = s_ri(1:max_space);
thickness1 = s_thickness(1:max_space);
ri2 = s_ri(max_space+1:length(s_ri));
thickness2 = s_thickness(max_space+1:length(s_ri));
conf1 = s_conf(1:max_space);
lci1 = s_lci(1:max_space);
conf2 = s_conf(max_space+1:length(s_ri));
lci2 = s_lci(max_space+1:length(s_ri));


ri1 = hampel_filter(ri1, 2.5);
ri2 = hampel_filter(ri2, 2.5);
thickness1 = hampel_filter(thickness1, 2.5);
thickness2 = hampel_filter(thickness2, 2.5);
%conf1 = hampel_filter(conf1, 2.5);
%conf2 = hampel_filter(conf2, 2.5);
%lci1 = hampel_filter(lci1, 2.5);
%lci2 = hampel_filter(lci2, 2.5);

mean_ri1 = mean(ri1);
sd_ri1 = std(ri1);
mean_thickness1 = mean(thickness1);
sd_thickness1 = std(thickness1);
mean_ri2 = mean(ri2);
sd_ri2 = std(ri2);
mean_thickness2 = mean(thickness2);
sd_thickness2 = std(thickness2);
mean_conf1 = mean(conf1);
sd_conf1 = std(conf1);
mean_lci1 = mean(lci1);
sd_lci1 = std(lci1);
mean_conf2 = mean(conf2);
sd_conf2 = std(conf2);
mean_lci2 = mean(lci2);
sd_lci2 = std(lci2);

if mean_conf1 > mean_conf2
    mean_ri_high = mean_ri1;
    mean_ri_low = mean_ri2;
    sd_ri_high = sd_ri1;
    sd_ri_low = sd_ri2;
    mean_t_high = mean_thickness1;
    mean_t_low = mean_thickness2;
    sd_t_high = sd_thickness1;
    sd_t_low = sd_thickness2;
    mean_conf_high = mean_conf1;
    mean_conf_low = mean_conf2;
    sd_conf_high = sd_conf1;
    sd_conf_low = sd_conf2;
    mean_lci_high = mean_lci1;
    mean_lci_low = mean_lci2;
    sd_lci_high = sd_lci1;
    sd_lci_low = sd_lci2;
else
    mean_ri_high = mean_ri2;
    mean_ri_low = mean_ri1;
    sd_ri_high = sd_ri2;
    sd_ri_low = sd_ri1;
    mean_t_high = mean_thickness2;
    mean_t_low = mean_thickness1;
    sd_t_high = sd_thickness2;
    sd_t_low = sd_thickness1;
     mean_conf_high = mean_conf2;
    mean_conf_low = mean_conf1;
    sd_conf_high = sd_conf2;
    sd_conf_low = sd_conf1;
    mean_lci_high = mean_lci2;
    mean_lci_low = mean_lci1;
    sd_lci_high = sd_lci2;
    sd_lci_low = sd_lci1;
end

fprintf('Refractive index\t%f\t%f\t%f\t%f\n', mean_ri_high, sd_ri_high, mean_ri_low, sd_ri_low);
fprintf('Thickness\t%f\t%f\t%f\t%f mm\n', mean_t_high, sd_t_high, mean_t_low, sd_t_low);
fprintf('%i\t%i\n', length(ri1), length(ri2));
fprintf('%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n', mean_ri_high, sd_ri_high, mean_ri_low, sd_ri_low, mean_t_high, sd_t_high, mean_t_low, sd_t_low);
fprintf('%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n', mean_conf_high, sd_conf_high, mean_conf_low, sd_conf_low, mean_lci_high, sd_lci_high, mean_lci_low, sd_lci_low);

end


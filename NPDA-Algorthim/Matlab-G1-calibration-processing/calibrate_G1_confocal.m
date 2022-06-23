function conflcidata = calibrate_G1_confocal(conflcidata, calinfo)
% This function perofrms an offline calibration of the confocal arm of the
% G1. File format is assumed to be as per the -raw.csv and -scan.csv files,
% with confocal and LCI data in alternate columns.
%   Detailed explanation goes here

%calinfo = dlmread(cal_file);
%conflcidata = dlmread(data_file);


%xq = calinfo(:, 1);

dsize = size(calinfo, 1);
lsize = size(conflcidata, 1);
csize = size(conflcidata, 2);
confsize = floor((csize - 1) / 2.0);

%fprintf('%i\t%i\n', csize, confsize);

if dsize > lsize
    conflcidata=conflcidata(1:lsize, :);   % Scans matr
    confdata = zeros(lsize, confsize);
    cal=calinfo(1:lsize, 2);                          % Positions array
    xq = calinfo(1:lsize, 1);
else
    conflcidata=conflcidata(1:dsize, :);   % Scans matr
    confdata = zeros(dsize, confsize);
    cal=calinfo(1:dsize, 2);                    % Positions array
    xq = calinfo(1:dsize, 1);
end


for i = 1:confsize
    confdata(:, i) = conflcidata(:, 2 * i);
end  
              
calibrated_data = interp1(cal, confdata, xq);
calibrated_data(isnan(calibrated_data)) = 0;

%size(calibrated_data)
%size(confdata)
%size(conflcidata)

for i = 1:confsize
    conflcidata(:, 2 * i) = calibrated_data(:, i);
end

% Get rid of NaNs

end

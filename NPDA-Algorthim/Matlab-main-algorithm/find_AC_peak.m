function [ q1, q2 ] = find_AC_peak( data )
% This function finds the region of the scan data which covers the FWHM of 
% the AC peak.

%   Input: data: data from a scan
%   Output: AC_peak_data: data within the AC peak FWHM

% Find the AC peak
[max_val, pos_max] = max(data);      % Maximum of the data and its position

% Check that it is the AC peak (useful for verification on silica target)
LH_zone = 100;
if (pos_max > LH_zone)  % If peak at extreme left of scan, assume AC peak
    temp_data = data(1: pos_max - LH_zone);
    [candidate_peak, pos_candidate] = max(temp_data);
    if (2 * candidate_peak > max_val)
        max_val = candidate_peak;
        pos_max = pos_candidate;
    end
end
    
current_dir = pwd;
cd('../Matlab-scan-preprocessing');
med_val = median_uint16_t(data,length(data)); % Median of the data, i.e. zero level
cd(current_dir);

%disp(pos_max);
%disp(max_val - med_val);
toplim = length(data);

half_height = (max_val + med_val) / 2;


i = pos_max;
while((i > 1) && (data(i) > half_height))
  i = i - 1;
end
f1 = pos_max - i;

i = pos_max;
while((i < toplim) && (data(i) > half_height))
  i = i + 1;
end
f2 = i - pos_max;

t_factor = 1;
q1 = ceil(pos_max - t_factor * f1);
q2 = floor(pos_max + t_factor * f2);


end


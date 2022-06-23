function out = find_nth(data, n)
%find_nth.m Finds end of nth pulse
%   This file takes a vector of zeros or ones as an input and returns index 
%   of the nth pulse (pulse means one or more consecutive ones).
% Inputs:
%   data    : a vector, contains zeros or ones
%   n       : a scalar, the number of pulse to look for
% Outputs:
%   out     : a scalar, index of the end of the nth pulse
  idx_offset = 0;
  temp_idx_offset = 0;
  for i=1:n
    idx_offset = idx_offset + temp_idx_offset;
    idx = find(data, 1, 'first');
    if length(idx) ~= 1
      error("No signal start was found.")
    end
    data = data(idx:end);
    temp_idx_offset = idx;
    idx_temp = find(data-1, 1, 'first');
    if length(idx_temp) ~= 1
      error("No signal start was found.")
    end
    data = data(idx_temp:end);
    temp_idx_offset = temp_idx_offset + idx_temp;
  end
  out = idx + idx_offset;
end

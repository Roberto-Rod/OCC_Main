function [scans_out] = normalise_scans(scans_in, digital_gain)
%normalise_scans.m Normalises scan data
%   This file normalises the scan data, collected at at a given gain to
%   the uniform gain. Specifically, the scan information returned by
%   this function corresponds to such signal, as if it was collected with
%   the gain that corresponds to the DPOT (IC4) on the LDA set to 5k. 
% Inputs:
%   scans_in    : a n by 5000 matrix containing n scans. 
% Outputs:
%   scans_out   : a n by 5000 matrix containing n scans.

  scans_out = zeros(size(scans_in));
  
  for i = 1:size(scans_in, 1)
    human_gain = 1 + 10 / (0.1 + 10 * digital_gain(i) / 127);
    DC_offset = median(scans_in(i,:));
    %5k => digital_gain=64 => human_gain=2.96
    scans_out(i,:) = (scans_in(i,:)-DC_offset)./human_gain.*2.96;
  end
end
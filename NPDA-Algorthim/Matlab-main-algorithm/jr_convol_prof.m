function y=jr_convol_prof(data)
% Convolution of the data with a simulated peak profile from Zemax
%
% Author: Raquel Gonzalez
% Last update: 15/09/17
%
% Input: data: Data from one scan (ideally from a mean scan) 
% Output: y: Convoluted scan

filenameAC='iScan AC Peak Profile.csv';
% NOTE: iScan AC Peak Profile.csv contains an averaged peak profile (above FWHM) from
% the centre of a calibration run. As such it gives a realistic ideal peak
% profile comparable to that generated from the AC peak, but unlike the AC
% peak does not vary with range.
ACdata = csvread(filenameAC,1);
temp=ACdata(:,2); %Template

y=conv(data,temp,'same');
end

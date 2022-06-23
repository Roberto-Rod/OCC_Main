function y=convol_prof(data)
% Convolution of the data with a simulated peak profile from Zemax
%
% Author: Raquel Gonzalez
% Last update: 15/09/17
%
% Input: data: Data from one scan (ideally from a mean scan) 
% Output: y: Convoluted scan

filenameAC='iScan AC Peak profile.csv';
ACdata = csvread(filenameAC,1);
temp=ACdata(1:80,2); %Template

y=conv(data,temp,'same');
end

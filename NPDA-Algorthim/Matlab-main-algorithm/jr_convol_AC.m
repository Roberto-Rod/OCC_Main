function y=jr_convol_AC(data)
% Description: Convolution of the data with the AC peak as a template
%
% Author: Raquel Gonzalez
% Last update: 15/09/17
%
% Input: data: Data from one scan (ideally from a mean scan) 
% Output: y: Convoluted scan

[q1, q2] = find_AC_peak(data);
% Find the AC peak
temp = data(q1:q2);
y=conv(data,temp,'same'); % Convolution

end

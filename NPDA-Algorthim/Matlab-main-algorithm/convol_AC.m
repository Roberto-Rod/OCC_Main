function y=convol_AC(data)
% Description: Convolution of the data with the AC peak as a template
%
% Author: Raquel Gonzalez
% Last update: 15/09/17
%
% Input: data: Data from one scan (ideally from a mean scan) 
% Output: y: Convoluted scan


max_val=max(data);      % Maximum of the data
%disp(max_val);

% We find all peaks above half of the maximum value in the signal and save
% the half-height widths. We choose the highest detected peak (sometimes there may be secondary peaks at the tip of the AC)
% [~,idx,w]=findpeaks(data,'MinPeakHeight',max_val/2,'SortStr','descend','Annotate','extents'); % Matlab 2014b
% 
[~,idx,w]=processPeaks(data, (max_val / 2 ), 0 ); % Matlab 2013b

% pks is peak amplitudes
% idx is position index
% w is width

t_factor = 0;
% We select points at both sides of the peak up to 4 times the half-height width.
points=idx(1)-t_factor*floor(w(1)):idx(1) + t_factor*floor(w(1));
fprintf('Points %f/n', points);

temp=data(points);        % Template

y=conv(data,temp,'same'); % Convolution

end

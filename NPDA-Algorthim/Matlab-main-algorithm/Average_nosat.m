function [mean_data, num] = Average_nosat(pos,data0, resolution, align)
% Description: Alignment of the scans wrt the AC peak and pointwise
% average. This increases the S-R.
%
% Author: Raquel Gonzalez
% Last update: 15/09/17
%
% Inputs:
%   pos: Array of positions.
%   data0: Matrix with the scans selected to average
%
% Output:
%   mean_data: The mean of the scans or mean scan
%
%   Example: [mean_data]=Average(pos,data0);
% -------------------------------------------------------------------

% 1. FIND THE AC PEAK POSITION FOR EACH SCAN

% 2. SHIFT ALL THE SCANS SO THE AC PEAK IS LOCATED AT THE MIDDLE OF THE ARRAY
% (pos=2.5, idx=1251)
% Other options is translate them to the position of the AC in the first
% scan, or move them towards the AC peak closer to 0

% -------------------------------------------------------------------


nscans=size(data0,2);      % Number of scans to average

% SAVE SPACE
newdata=0*data0;    % It will contain the shifted data
idx_true=zeros(nscans,1); % It will contain the index value where the AC peak is
i = 0;
sat_limit = 4.501;  % Signal level at which saturation occurs

ref_idx=1251; % Reference index is the middle index of the positions array


for scan=1:nscans 
    data=data0(:,scan);    % Select a single scan
    if (max(data) < sat_limit)
        % Reject single scan if saturates
        i = i + 1;
    
        medData = median(data);
        data = data - medData;  % Subtract off median to give common baseline (nominally zero).
        % This is important as the data is padded with zeros on alignment, and
        % if not on a common baseline peak detection will not work reliably.
        maxData = max(data);
        [q1, q2] = find_AC_peak(data);
        temp_pos = pos(q1:q2);
        temp = data(q1:q2);
        fwhm(scan) = q2 - q1;         % AC peak FWHM
        maxpos = findAC_quad(temp_pos, temp, resolution);
        idx_true(scan) = find(abs(pos - maxpos) < 0.0005); 
        % Index for the maximum within the whole array of positions 
    
        if (align == 0)         % Do not align scans (used for clibration)
            shift = 0;
        else                    % Align scans (used for verification/measurement)
    
            shift=idx_true(scan)-ref_idx;
        end
        %disp(idx_true(scan));
  
        if shift>0               % When the scan is on the right from ref scan
            shiftscan=[data(shift+1:end); zeros(shift,1)];
        else                     % On the left or centered
            shiftscan=[zeros(abs(shift),1); data(1:end+shift)];
        end
    
        % We can insert an if shift>num to discard scans where PC is out of range
    
        newdata(:,i)=shiftscan; % Save the shifted data  
    end 
end


    figure(5);
    plot(newdata);
    title('Shifted Data')

% NORMALISE THE DATA
%normdata=newdata/max(max(newdata));
normdata=newdata(:, 1:i);

% MEAN AND SD
%figure
mean_data=mean(normdata,2); %mean of all columns (basically mean of all the Scans
num = i;
%for i = 1:nscans
%    dev3(:, i) = (normdata(:, i) - mean_data) .^3;
%end

%subplot(1,2,2)
%plot(mean_data);
%title('Aligned and averaged')
%sd_data=std(normdata,0,2);
%skew_data = mean(dev3, 2) ./ (sd_data .^ 3);

% 
% figure
% plot(pos,mean_data, 'r-')

% hold on
% plot(pos,mean_data - sd_data, 'k--')
% plot(pos,mean_data + sd_data, 'k--')
%figure
%plot(pos,sd_data)
end


% Wavelet transform:
%[c,l] = wavedec(dataf,4,'db1');
% [cd1,cd2,cd3,cd4] = detcoef(c,l,[1 2 3 4]);
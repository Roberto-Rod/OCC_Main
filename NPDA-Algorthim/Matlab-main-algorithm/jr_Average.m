function [mean_data]=jr_Average(pos,data0)
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


ref_idx=floor(size(pos, 2) / 2); % Reference index is the middle index of the positions array
disp(ref_idx);

for scan=1:nscans 
    data=data0(:,scan);    % Select a single scan
    points=find(data>=0.5*max(data) & data<=0.8*max(data)); % Choose points with specific amplitude (AC peak)
    rAC=pos(points)';       % Position of the points
    dAC = data(points);
  
    p=polyfit(rAC,dAC,2);  % Fit a quadratic to AC peak
    y = polyval(p,rAC);             % Evaulate the quadratic
                                      % Find the maximum of the parabola
    ACpos=rAC(y==max(y));             % Position of the maximum within the array rAC
    idx_true(scan)=find(pos==ACpos); % Index for the maximum within the whole array of positions  
    
    % 2.
    shift=idx_true(scan)-ref_idx;
    
    pad(1:abs(shift), 1) = median(data);
    
    if shift>0               % When the scan is on the right from ref scan
        shiftscan=[data(shift+1:end); pad];
    else                     % On the left or centered
        shiftscan=[pad; data(1:end+shift)];
    end
    pad = [];                % Deallocate pad array    
    
    % We can insert an if shift>num to discard scans where PC is out of range
    
    newdata(:,scan)=shiftscan; % Save the shifted data     
end

%figure
%subplot(1,2,2)
%plot(newdata)


% NORMALISE THE DATA
%normdata=newdata/max(max(newdata));
normdata=newdata;

% MEAN AND SD
%figure
mean_data=mean(normdata,2);
%sd_data=std(normdata,0,2);
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
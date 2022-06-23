function [PCpos, ref]=findPC_max(ACpos,pos,data,fit)
% Description: Find the PC peak position by looking for the peak with
% greatest prominence wrt the right neigbouring peak, and fitting a
% quadratic curve. Preferably use it after filtering the signal with a matched
% filter so the profiles of the peaks are more well defined and smoother (less number of peaks too).
% The weights determine the quality of the scan being considered and are
% calculated as the difference of the prominence of the PC peak and the
% second highest prominence within peaks to the left of PC.
%
% Author: Raquel Gonzalez
% Last update: 15/09/17
%
% Inputs:
%        ACpos: Position of the AC peak found before using findAC_quad. It
%        is used to find the window where to look for the PC peak
%        pos: Array of positions
%        data: It contains a single scan (ideally, an averaged and matched filtered scan)
%        fit: If fit=1, we fit a quadratic to the PC peak, ow, we pick the
%        height of the detected peak.
% Outputs:
%        PCpos: Position of the PC peak
%        ref: Quality of the scan (Weight)
%

disc=0;  %disc=1 if we want to discard bad scans from the mean thickness calculation
score0=0.5; % Maximum score/weight for secondary peaks, ow we discard them if disc=1

improv=1; % Select all points in the peak

nc = 1.3989;      %Refractive index of cornea
res = 0.001;    % Encoder resolution
mincct = 0.2;   % Minimum central corneal thickness
maxcct = 0.7;   % Maximum central corneal thickness

% DEFINE WINDOW (A human cornea can't be less than 0.4 or greater than 0.7)
% Reduce the range where to look for PCpos based in ACpos
leftbound=floor(ACpos/res)+floor(mincct/(res*nc));
rightbound=floor(ACpos/res)+floor(maxcct/(res*nc));
datapc=data(leftbound:rightbound);
pospc=pos(leftbound:rightbound);

% Find peaks within the window
[pks,idx,wi] = processPeaks(datapc, 0, 0);

	disp(pks);
	disp(idx);
	figure(4)
	hold on
	plot(pospc,datapc);
	plot(pospc(idx),pks,'*k')
	title('PC Peak Maxs')
	hold off

% Find the noise level by calculating the median of the signal
noiselevel=median(data);

    
% New peak detection algorithm:
%     1. If there are more than one peak It will do the ratio between the height of the peak
%         and the height of the peak immediately to the right. The last peak is compared with the noise level
%     2. The maximum of those ratios will correspond to the actual PC peak
%     3. We could fit a quadratic if we want.
%     

 if size(pks,1)>=2
    pks0=[pks(2:end); noiselevel];
    ratio=pks./pks0;        % (1.) Prominence
   
    [PCmx0,PCidx0]=sort(ratio,'descend');  
    PCmx=PCmx0(1);                  % Save intensity of PC peak (maximum)
    PCidx=PCidx0(1);                % Save index of PC peak in the ratio array
    score=ratio./PCmx; %Peak score: Compare the prominences of the peaks with the PC prominence (PC score: 1) (0-1)
 
    disp(score);
    PCidx0=PCidx0(PCidx0<=PCidx);   % We only want to compare PC with peaks on the left hand side
                 
    if size(PCidx0,1)==1   %There are no peaks on the left of PC
        ref0=1;
        ref=ratio(PCidx);
    else
        ref0=1-score(PCidx0(2));            % Another criteria for quality of scans
        ref=ratio(PCidx)-ratio(PCidx0(2));  % Prefered criteria (weight)
    end
    % Quality of measurement (ref): The higher the PC peak is, the better
    % quality. At the same time if secondary peaks have a great height, the
    % weight is reduced.
    
    % ref0
    % ref
    if ref0<score0 && disc==1  % If the second largest peak score is greater than score% of the highest peak, we discard the scan (optional)
        PCpos=0;                                
        disp 'Bad scan. The peaks have similar heights'
        ref0=0;
    else
        idx0=idx(PCidx);
        PCpos=pospc(idx0);
    end
    
 elseif size(pks,1)==1
     PCidx=1;
     idx0=idx;
     ref0=1;       % The score is 1, since it is the only peak found
     ref=pks/noiselevel;
     PCpos=pospc(idx0);
     
 else 
     disp 'No PC peak has been found'
     ref0=0;
     ref=0;
     PCpos=0;
 end


 % QUADRATIC CURVE FITTING 
if PCpos~=0 && fit==1
    
    % To fit the quadratic pol we will choose points along the width of the
    % detected peak
    ridx=idx0+leftbound-1;   % Real index after finding peak in the window
    hw=ceil(wi(PCidx)/2);    % Half width of peak

    %Reduce the data set to the points that are in the peak
    peakidx=ridx-hw:ridx+hw;   %Indices of the peak
    PCdataf=data(peakidx);    %Intensities of the peak

    % Select the points to fit the curve
    if improv==1
        points=peakidx; % For improvement, that is selecting all points in the peak for the PC
    else
        points=peakidx(PCdataf>=0.5*data(ridx) & PCdataf<=0.8*data(ridx)); % Select points within a range of amplitudes
    end

    if isempty(points) || size(points,2)<=2
        %disp 'Not enough points found to fit a quadratic to PC. Try improv=1, a different threshold or a different algorithm.';
        PCpos=0;
        ref0=0;
        ref=0;
    else
        %disp 'Curve fitted successfully.';
        p=polyfit(pos(points),data(points),2);      % Fit the curve

        pos0=pos(points(1)):0.0001:pos(points(end));   
        yPC = polyval(p,pos0);      % Evaluate it with a higher resolution

        PCpos=pos0(yPC==max(yPC)); % Find the maximum of the parabola
    end

  
end    
     
end
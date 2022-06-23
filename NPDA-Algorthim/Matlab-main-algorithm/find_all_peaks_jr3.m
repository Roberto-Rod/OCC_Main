
function [PCpos, PCht, weight]=find_all_peaks_jr3(indAC,pos,data,slopecorr, fit, nc, res, plotFigures)
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

mincct = 0.3;   % Minimum central corneal thickness
maxcct = 0.9;   % Maximum central corneal thickness
%mincct = 0.8;   % Minimum central corneal thickness
%maxcct = 0.65;   % Maximum central corneal thickness
%maxcct = 2.5;    % For verification only

% DEFINE WINDOW (A human cornea can't be less than 0.4 or greater than 0.7)
% Reduce the range where to look for PCpos based in ACpos
% Expressed in array indices
leftbound=floor(indAC)+floor(mincct/(res*nc));
if leftbound > length(data)
    leftbound = length(data);
end
rightbound=floor(indAC)+floor(maxcct/(res*nc));
if rightbound > length(data)
    rightbound = length(data);
end
%fprintf('%i\t%i\n', leftbound, rightbound);

%indexvar = floor(posAC/res);
ACheight = data(indAC);
datapc=data(leftbound:rightbound);
dd_datapc = zeros(length(datapc), 1);
datapc_ma = zeros(length(datapc), 1);
pospc=pos(leftbound:rightbound);    %Position in array indices

% Find the noise level by calculating the median of the signal
current_dir = pwd;
cd('../Matlab-scan-preprocessing');
noiselevel=median_uint16_t(data, length(data));
cd(current_dir);



% Find peaks within the window
[pks,idx,wi, pk_height] = processPeaks_jr2(datapc, 0, 0);

if ~isempty(idx)
    pospeaks = pospc(idx);  % Positions of candidate peaks in mm
end
%ACheight
%pks



if length(pks) > 0
    % Calculate the weighting factor for each peak located
    % Weighting factor is based on empirical limit on the height of ripples as
    % a function of PC position and has a logarithmic amplitude variation.
    % Anything over a threshold height is very likely to be a real PC peak, do
    % not need much change in weighting above threshold. Below threshold peak
    % may still be a real PC peak, so cannot be eliminated completely.
    % t = abs(pospeaks - pos(indAC)) .* nc .* res;    % Estimate of corneal thickness
    t = abs(pospeaks - pos(indAC)) .* nc;
    PCheight = pks ./ ACheight;      % PC peak height normalised to AC peak height
    % Note that this is the ratio of the convolved peaks, so if the AC peak
    % is saturated this will be artificially inflated. 
    % wt = 1 - exp(-2.303 * PCheight ./ (0.035 - 0.04 * t));  % Weighting factor
    %wt = 1 - exp(-2.303 * (PCheight + 0.03) ./ (0.065 - 0.04 * t));  %
    %Alternative weighting factor - use if maxcct > 0.8
    for i = 1:length(pks)
        if t(i) > 1     % Avoids weighting catastrophe for high thickness values
            t(i) = 1;   % Should never be needed with real eyes, but useful for testing
        end
        %z = pospc - pos(indAC);
        %wa = (0.022 - (0.045 .* z) + (0.012 .* z.^2)) * ACheight;
        wt(i) = 1 - exp(-2.303 * PCheight(i) ./ (0.035 - 0.045 .* t(i) + 0.012 .* t(i).^2));
        %fprintf('%f\t%f\t%f\t%f\n', pospeaks(i),pos(indAC), t(i), wt(i));
    end
    % Experimental weighting factor
    
    % Peak with largest weighting factor assumed to be real PC peak
    [weight, ind] = max(wt');            
    PCpos = pospeaks(ind);      % PC peak position in mm
    PCht = PCheight(ind);
    
    
    if slopecorr ~= 0
        halfwidth = 0.1;
        % Find left and right extent of PC peak
        PCleft = PCpos - halfwidth;
        PCright = PCpos + halfwidth;
        %fprintf('%f\t%f\t%f\n', PCpos, PCleft, PCright);
        PCleftindex = find(abs(pospc - PCleft) < res / 2);
        PCrightindex = find(abs(pospc - PCright) < res / 2);
            % Indices of left and right bounds
        PCposindex = find(abs(pospc - PCpos) < res / 2);
        [LHminval, LHminindex] = min(datapc(PCleftindex:PCposindex));
        LHminindex = LHminindex + PCleftindex;
        RHminindex = 2 * PCposindex - LHminindex;
        if RHminindex > rightbound - leftbound
            RHminindex = rightbound - leftbound;
        end
        
        RHminval = datapc(RHminindex);
        LHpos = pospc(LHminindex);
        RHpos = pospc(RHminindex);
        
        
        if slopecorr == 1
            % Linear slope correction
            % Draw stright line between edges of PC peak,
            % i.e. create trace without PC peak
            slope = (RHminval - LHminval) / (RHpos - LHpos);
            data_nopc = datapc;
            for i = LHminindex:RHminindex
                data_nopc(i) = LHminval + slope * (pospc(i) - LHpos);
            end
        
            
        end
        if slopecorr == 2
            % Nonlinear slope correction
            % Intterpolate curve between edges of peak
            % i.e. create best guess AC peak profile without PC peak
            % Select the parts of the curve which do not contain the PC
            % peak and interpolate between them.
            q = length(pospc);
            ACpartpos = [pospc(1:LHminindex); pospc(RHminindex:q)];
            ACpartdata = [datapc(1:LHminindex); datapc(RHminindex:q)];
            data_nopc = interp1(ACpartpos, ACpartdata, pospc, 'spline');
        end
        
        %figure(6)
        %hold on
        %plot(pospc, data_nopc);
        %hold off
        
        % Find the difference
        datadiff = datapc - data_nopc;
        diffmax = max(datadiff);
        maxpos = find(datadiff == diffmax, 1);
        PCp = pospc(maxpos);
        PCh = datapc(maxpos);
    end
    
    %figure(4)
    %hold on
    %plot(pospc,datapc);
    % plot(pospc, data_nopc);
    %plot(PCpos, PCht * ACheight,'*k')
    %title('PC Peak Maxs')
    %hold off
    
    % MA filter of trace
    %dd_top = length(datapc);
    %m = 30;
    %for i = m + 1:dd_top - m - 1
    %    a = i - m;
    %    if a < 1
    %        a = 1;
    %    end
    %    b = i + m;
    %    if b > dd_top
    %        b = dd_top;
    %    end
    %    ma = datapc(a:b);
    %    datapc_ma(i) = mean(ma);
    %end
    
    %for i = m + 2:dd_top - m - 2
    %    dd_datapc(i) = datapc_ma(i+1) - 2 * datapc_ma(i) + datapc_ma(i-1);
        % Double derivative
    %end
   
    
        
    %figure(6)
    %hold on
    %plot(pospc,dd_datapc);
    %title('Double derivative')
    %hold off
    
    % Find minimum of of signal just before PC peak
    PCpos_left = PCpos - 0.1;
    if PCpos_left < pospc(1)
        PCpos_left = pospc(1);
    end
    i = 1;
    % Find left-hand edge
    while pospc(i) < PCpos_left
        i = i + 1;
    end
    
    % Find lowest minimum in range and nearest minimum to PC peak
    min_near = datapc(i);
    min_nearpos = pospc(i);
    min_height = datapc(i);
    min_pos = pospc(i);
    while pospc(i) < PCpos
        i = i + 1;
        if datapc(i) < min_height
            min_height = datapc(i);
            min_pos = pospc(i);
        end
        if (datapc(i) < datapc(i-1)) && (datapc(i) < datapc(i+1))
            min_near = datapc(i);
            min_nearpos = pospc(i);
        end
    end

            
    %idxind = idx(ind);
    
 % QUADRATIC CURVE FITTING 
    if (PCpos ~= 0) && (fit == 1)
    
    % To fit the quadratic pol we will choose points along the width of the
    % detected peak
        hw=ceil(PCwidth/2);    % Half width of peak

    %Reduce the data set to the points that are in the peak
        peakidx=PCpos-hw:ridx+hw;   %Indices of the peak
        PCdataf=data(peakidx);    %Intensities of the peak

    % Select the points to fit the curve
        if improv==1
            points=peakidx; % For improvement, that is selecting all points in the peak for the PC
        else
            points=peakidx(PCdataf>=0.5*(data(ridx) - noiselevel) & PCdataf<=0.8*(data(ridx) - noiselevel)); % Select points within a range of amplitudes
        end

        if isempty(points) || size(points,2)<=2
        %disp 'Not enough points found to fit a quadratic to PC. Try improv=1, a different threshold or a different algorithm.'
            PCpos=0;
            PCheight = 0;
            ref0=0;
            ref=0;
        else
        %disp 'Curve fitted successfully.'
            p=polyfit(pos(points),data(points),2);      % Fit the curve

            pos0=pos(points(1)):0.0001:pos(points(end));   
            yPC = polyval(p,pos0);      % Evaluate it with a higher resolution

            PCpos=pos0(yPC==max(yPC)); % Find the maximum of the parabola
        end

    end
else
    PCpos = 0;
    PCht = 0;
    weight = 0;
end    
 
if (plotFigures == 1)
    figure(4)
    hold on
    dpc = datapc / max(data);
    plot(pospc,dpc);
    ylim([0 0.03]);
    %plot(pospc(idx),pks,'*k')
    title('PC Peak Maxs')
    hold off
end
end
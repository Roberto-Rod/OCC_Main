
function [PCpos, PCht, weight]=find_prominent_peaks_jr(indAC,pos,data, fit, nc, res)
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

mincct = 0.2;   % Minimum central corneal thickness
%maxcct = 0.7;   % Maximum central corneal thickness
%mincct = 0.8;   % Minimum central corneal thickness
maxcct = 0.9;   % Maximum central corneal thickness
%maxcct = 2.5;    % For verification only

% DEFINE WINDOW (A human cornea can't be less than 0.4 or greater than 0.7)
% Reduce the range where to look for PCpos based in ACpos
leftbound=floor(indAC)+floor(mincct/(res*nc));
rightbound=floor(indAC)+floor(maxcct/(res*nc));
%fprintf('%i\t%i\n', leftbound, rightbound);

%indexvar = floor(posAC/res);
ACheight = data(indAC);
datapc=data(leftbound:rightbound);
dd_datapc = zeros(length(datapc), 1);
datapc_ma = zeros(length(datapc), 1);
pospc=pos(leftbound:rightbound);
z = pospc - pos(indAC);         % Create baseline (approx AC peak profile)
%wa = (0.022 - (0.045 .* z) + (0.012 .* z.^2)) .* ACheight;
wa = (0.03 - (0.09 .* z) + (0.072 .* z.^2)) .* ACheight;
datapc = datapc - wa;
% Find the noise level by calculating the median of the signal
noiselevel=median(data);

% Find peaks within the window
[pks,idx,wi, pk_height] = processPeaks_jr(datapc, 0, 0);

if ~isempty(idx)
    pospeaks = pospc(idx);
end


if ~isempty(pks)
    % Calculate the weighting factor for each peak located
    % This weighting factor is based on a modified measure of peak
    % prominence. Prominence is based on the difference between the peak
    % height and the maximum height of a trough within a specified distance
    % of the peak (halfwidth).
    halfwidth = 150;
    
    for i = 1:length(pks)
        LHpk = idx(i) - halfwidth;
        if LHpk < 1
            LHpk = 1;
        end
        RHpk = idx(i) + halfwidth;
        if RHpk > length(datapc)
            RHpk = length(datapc);
        end
        LHprom(i) = pks(i) - min(datapc(LHpk:idx(i)));
        RHprom(i) = pks(i) - min(datapc(idx(i):RHpk));
    end
    
    [PCLH, ind] = max(LHprom');
    PCRH = RHprom(ind);
    PCpos = pospc(idx(ind));
    PCht = pks(ind);
    
    weight = 1 - 2*(PCRH - PCLH) / PCht;
    
    fprintf('%f\t%g\t%g\t%g\t%g\n', PCpos, PCht, PCLH, PCRH, weight);
    
    
%    t = abs(pospeaks - pos(indAC)) .* nc;    % Estimate of corneal thickness
%    PCheight = pks ./ ACheight;      % PC peak height normalised to AC peak height
    
    
    
   
    %Alternative weighting factor - use if maxcct > 0.8
%    for i = 1:length(pks)
%        if t(i) > 1     % Avoids weighting catastrophe for high thickness values
%            t(i) = 1;   % Should never be needed with real eyes, but useful for testing
%        end
        
        % Find the highest peak above baseline
%        wt(i) = PCheight(i);
        %fprintf('%f\t%f\t%f\t%f\n', pospeaks(i),PCheight(i), t(i), wt(i));
%    end
    % Experimental weighting factor
    
    % Peak with largest weighting factor assumed to be real PC peak
%    [weight, ind] = max(wt');            
%    PCpos = pospeaks(ind);
%   PCht = PCheight(ind);
    
    
  
    figure(4)
    hold on
    plot(pospc,(datapc + wa) / ACheight, pospc, wa / ACheight);
    % plot(pospc, data_nopc);
    %plot(PCpos, PCht,'*k')
    title('PC Peak Maxs')
    hold off
    
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
  
%figure(4)
%hold on
%plot(pospc,datapc);
%plot(pospc(idx),pks,'*k')
%title('PC Peak Maxs')
%hold off
end
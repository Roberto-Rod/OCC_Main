function PCpos=findPC_quad(ACpos,pos,dataf,th)
% Description: Find the PC peak position by looking for peaks above a
% threshold and fitting a quadratic curve. 
%
% Author: Raquel Gonzalez
% Last update: 15/09/17
%
% Inputs:
%        ACpos: Position of the AC peak found before using findAC_quad. It
%        is used to find the window where to look for the PC peak
%        pos: Array of positions
%        dataf: It contains a single scan 
%        th: Threshold for the PC peak. Ontly detect peaks above this value
% Outputs:
%        PCpos: Position of the PC peak
%

improv=0;   %If improv=1, we are selecting all points in the PC peak to fit the curve
nc=1.3989;      %Refractive index of cornea
res = 0.001;    % Encoder resolution
mincct = 0.3;   % Minimum central corneal thickness
maxcct = 0.7;   % Maximum central corneal thickness

% DEFINE WINDOW (A human cornea can't be less than 0.4 or greater than 0.7)
% Reduce the range where to look for PCpos based in ACpos
leftbound=floor(ACpos/res)+floor(mincct/(res*nc));
rightbound=floor(ACpos/res)+floor(maxcct/(res*nc));
datapc=data(leftbound:rightbound);
pospc=pos(leftbound:rightbound);
% 
% figure
% plot(pos,dataf)
% hold on
% plot(pospc,datapc)


% [pks,idx,wi]= findpeaks(datapc,'MinPeakHeight',th*10^4,'MinPeakDistance',6,'Annotate','extents');        % Matlab 2014b or later

[pks,idx,wi]= processPeaks(datapc, th*10^4, 6 );        % Matlab 2013b

if isempty(pks)
    fprintf('No PC peaks found between 0.3mm and 0.7mm to the right of AC peak, and above the threshold %2.3f. Try a different threshold or a different algorithm.\n',th)
    PCpos=0;
else
    % To fit the quadratic pol we will choose points along the width of the
    % detected peak, which is taken to be the last one detected by the
    % algorithm.
    ridx=idx(end)+leftbound-1;  %Real index after finding peak in the window
    hw=floor(wi(end)/2); %Half width of peak

    %Reduce the data set to the points that are in the peak
    peakidx=ridx-hw:ridx+hw;   %Indices of the peak
    PCdataf=dataf(peakidx);    %Intensities of the peak

    % Select the points to fit the curve
    if improv==1
        points=peakidx; % For improvement, that is selecting all points in the peak for the PC
    else
        points=peakidx(PCdataf>=0.5*dataf(ridx) & PCdataf<=0.8*dataf(ridx)); % Select points within a range of amplitudes
    end

    if isempty(points) || size(points,2)<=2
        disp 'Not enough points found to fit a quadratic to PC. Try improv=1, a different threshold or a different algorithm.'
        PCpos=0;
    else
        disp 'Curve fitted successfully.'
        p=polyfit(pos(points),dataf(points),2);      % Fit the curve

        pos0=pos(points(1)):0.0001:pos(points(end));   
        yPC = polyval(p,pos0);      % Evaluate it with a higher resolution

        PCpos=pos0(yPC==max(yPC)); % Find the maximum of the parabola
    end  
end

%     figure
%     plot(pos,dataf)  % Plot data
%     hold on
%     plot(pos(points2),dataf(points2),'k*')
%     %plot(r2PC,yPC)   % Plot PC fitted curve
%     hold on
%     %axis([pos(points2(1)-30) pos(points2(end)+30) 0 3*th*10^4])
%     plot(PCpos+0*(0:3*th*10^4),0:3*th*10^4,'k--')  % Plot position of PC
end
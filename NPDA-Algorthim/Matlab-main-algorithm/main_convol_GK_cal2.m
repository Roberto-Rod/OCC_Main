function [AC_PC_thick, mean_med, pp, qq, weightedMean, wmSDE, mean_wt]=main_convol_GK_cal2(filename,sheet,scan0,n,m,p, fit, plotFigures, peakFindType, cal, exp)
% Description: Find the AC and PC peak positions, and the thickness of the
% cornea for each single scan or block of scans(averaged). 
% Each scan or mean scan is filtered with a matched filter that uses the
% AC peak as a template. The peak detection algorithm for the PC peak is
% based on the prominence of the peaks in the filtered signal.
% It calculates the mean, median, weighted mean and weighted median.
%
% Note: It operates by using n blocks of m scans.
%
% Author: Raquel Gonzalez
% Last update: 15/09/17
%
% Inputs:
%       filename: Name of the Excel file
%       sheet: Sheet of the Excel file where the data is
%       (The first column in the Excel sheet should contain the positions) 
%       scan0: Initial scan 
%       n: Number of blocks
%       m: Number of scans in each block
%       (For peak detection in single scans set m=1 and n=number of scans)
%        (If m>1 we are averaging)
%       fit: If fit=1, we fit a quadratic curve to the PC 
%       peakFindType: 0 prominence, 1 amplitude (newer)
%
% Outputs:
%       AC_PC_thick=[ACpos, PCpos, thick]: Position of the AC peak, PC peak
%       and thickness.
%       mean_med=[mean_t,med_t,mean_w1,med_w1]: Mean/median and weighted mean/median of the thickness values.
%       time: Computational time
%       pp: Percentage of accepted scans
%
%
% Examples: 
%           [AC_PC_thick, mean_med]=main_convol('Summary_RGaligned',1,1,3,5,1)
%           [AC_PC_thick, mean_med]=main_convol('Summary_CHaligned',1,1,3,5,1)
%   %90     [AC_PC_thick, mean_med]=main_convol('RGSummaryAllScans',1,1,3,5,1)
%   %60     [AC_PC_thick, mean_med]=main_convol('JRSummaryAllScans',1,1,3,5,1)
close all

numberOfBlocks = n;
blockSize = m;
 fprintf('number Of Blocks: %d, block size: %d\n', numberOfBlocks, blockSize);
convol=1;   % If convol=1, we use the AC peak as a template (prefered), if convol=0 we use the simulated profile (Lorentzian)
slope = 1;
ct=1;       % Number of times to do the convolution (1 is prefered)
hampel = 1; % Flag for Hampel filtering
global lookupname;

if isempty(lookupname)
    lookupname = './Cal lookup.csv';
end

nc=1.3989;                  %Refractive index of cornea
%nc = 1.4468;                % Refractive index of fused silica
%nc = 1.5036;                % Refractive index of BK7
resolution=0.001;

% Select scans to average
totn=m*n;           % Total number of scans
blocks=1:m:totn;    % Indices for the blocks


% Read data
% data0 = xlsread(filename,sheet); 
% pos=data0(:,1);                     % Positions array
% data0=data0(:,scan0+1:scan0+totn);   % Scans matrix

% Read data
if ischar(filename)
    data0 = dlmread(char(filename),',', 1, 0);
else
    data0 = filename;
end
    
if cal == 0
    % Use uncalibrated positions
    pos=data0(:,1) ;                    % Positions array
    data0=data0(:,scan0+1:scan0+totn);   % Scans matr
else
    % Use positions based on calibration data
    lookup0 = dlmread(char(lookupname), ',', 0, 0);

    % Ensure arrays are of the same size
    dsize = size(data0, 1);
    lsize = size(lookup0, 1);
    if dsize > lsize
        data0=data0(1:lsize, scan0+1:scan0+totn);   % Scans matr
        pos=lookup0(:, 2);                          % Positions array
    else
        data0=data0(:, scan0+1:scan0+totn);         % Scans matr
        pos=lookup0(1:dsize, 2);                    % Positions array
    end

end

disp(size(data0));
disp(size(pos));

% Create set of data points at 1um intervals by interpolation

startpos = (ceil(pos(1) * 1000)) / 1000;
endpos = (floor(pos(size(pos, 1)) * 1000)) / 1000;
posq = startpos:resolution:endpos;
posq = posq';
data0;
dataq = interp1(pos, data0, posq);

% Save space
ACpos=zeros(n,1);
PCpos=zeros(n,1);
PCheight=zeros(n,1);
weight=zeros(n,1);
num_sat = zeros(n,1);

cla reset;

if plotFigures == 1
    figure(1);
    plot(posq,dataq);
    title('Raw Input Data')
else
end
%tic;
for i=1:n           % Loop along each block
%    fprintf('%i\n', i);
    data=dataq(:,blocks(i):blocks(i)+p-1);
    if m>=1
       [mean_data, ACp(i), mdn(i), backshift] = Average_AC2(posq,data, resolution, 1);
        % Note: much more reliable PC peak detection if the AC peaks are
        % aligned: this should be done even with single scans
    else       % If we are selecting single scans, do not call Average (we avoid translation of AC peak)
        mean_data=data;
    end

    current_dir = pwd;
    cd('../Matlab-scan-preprocessing');
    ya=mean_data - median_uint16_t(mean_data, length(mean_data));
    cd(current_dir);
    
    max_1 = max(ya(1:1400));
    max_2 = max(ya(1401:3000));
    ACp1(i) = find(max_1 - ya < 0.01, 1);
    ACp2(i) = find(max_2 - ya < 0.01, 1);

    
    figure(3);
    hold on
    plot(ya(1000:1500),'DisplayName',[' Block ' num2str(i)]);
    hold off
    

    if convol==1
        for j=1:ct
            y=jr_convol_AC(ya);   % Convolution with AC as template (favourite)
        end
    elseif convol==0
        for j=1:ct
            y=jr_convol_prof(ya); % Convolution with simulated profile as template
        end
    else
        for j = 1:ct
            y = ya;
        end
    end
    if plotFigures == 1
        figure(2);
        hold on
        plot(y,'DisplayName',[' Block ' num2str(i)]);
        hold off
    end

       max_1 = max(y(1:1400));
    max_2 = max(y(1401:3000));
    ACq1(i) = find(y == max_1, 1);
    ACq2(i) = find(y == max_2, 1);

    [q1, q2] = find_AC_peak(y);
    AC1 = max(y(q1:q2));
    ACind = find(y == AC1, 1);
    ACpos(i) = posq(ACind);
    %ACpos(i)=findAC_quad(posq(q1:q2), y(q1:q2), resolution);           % AC position
    ACheight(i) = max(y(q1:q2));
    ACh(i) = max(ya(q1:q2));
    
     
        %%
        % 
        % # ITEM1
        % # ITEM2
        % 
        if peakFindType == 0
            [PCpos(i), PCheight(i), weight(i)]=findPC_max_jr(ACind,posq,y,fit); %PC pos and quality of scan (weight)
        else
            %PC pos and quality of scan (weight) 
            %& Newer James amplitude style detection
            [PCpos(i), PCheight(i), weight(i)]=find_all_peaks_jr3(ACind, posq, y, slope, 0, nc, resolution, 1);
            %[PCpos(i), PCheight(i), weight(i)] = find_prominent_peaks_jr(ACind, posq, y, 0, nc, resolution);
        end

    %pause
end

%fprintf('%f\t%f\t%f\t', mean(ACpos), mean(PCpos), mean(weight));
if plotFigures == 1
    figure(2);
    %legend('off'); legend('show')
    title('Averaged & Convolved')
else
end


mdn = mdn';
ACheight = ACheight';
ACht = ACh';
ACpt = ACp';
ACpt1 = ACp1';
ACpt2 = ACp2';
ACqt1 = ACq1';
ACqt2 = ACq2';
%time=toc;
%Print out some stuffs
%ACpt
%ACpt1
%ACpt2
%ACqt1
%ACqt2
%ACpos
%ACheight
%ACht
%PCpos
%PCheight
%weight %pc weights
%num_sat

[valid, mean_t, sd_t, median_t, madse_t, mean_w, sd_w, mean_wt, sd_wt] = find_thicknesses(ACheight, ACpos, PCpos, weight, nc, exp, hampel, 1);
fprintf('%f\t%f\t%f\t%f\n', mean(ACheight), mean(ACpos), mean(PCpos), mean(weight));

fprintf( '\n' );
fprintf( 'Number of valid blocks (scans) is %i out of %i\n Total of scans used: %i \n', valid,totn/m,totn);
pp=valid/(totn/m)*100;      % Percentage of valid scans
fprintf('Percentage of valid scans %3.2f %% \n',pp);
fprintf( '\n' );
fprintf('Mean thickness: %3.1f ± %3.1f µm \n',mean_t*1000, sd_t*1000);
fprintf('Median thickness: %3.1f ± %3.1f µm \n',median_t*1000, madse_t*1000);

fprintf('Weighted mean: %3.1f ± %3.1f µm \n', mean_w * 1000, sd_w * 1000);
fprintf('Weight: %1.4f ± %1.4f \n', mean_wt, sd_wt);
weightedMean = mean_w*1000;

if (valid < 8)
    if (valid < 6)
        fprintf('BAD MEASUREMENT: TOO FEW VALID SCANS\n');
    else
        fprintf('Dubious measurement: too few valid scans\n');
    end
end
if (mean_wt < 0.78)
    if (mean_wt < 0.7)
        fprintf('BAD MEASUREMENT: PC PEAKS TOO SMALL\n');
    else
        fprintf('Dubious measurement: PC peaks too small\n');
    end
end

if (sd_w > 0.010)
    if (sd_w > 0.015)
        fprintf('BAD MEASUREMENT: RANDOM DATA');
    else
        fprintf('Dubious measurement: Data spread too great');
    end
end

AC_PC_thick = [ACpt, ACht, ACpos, ACheight, PCpos, PCheight, mdn];

mean_med=0;
pp=0;
qq=0;
wmSDE=sd_w*1000;
mean_wt=0;



end
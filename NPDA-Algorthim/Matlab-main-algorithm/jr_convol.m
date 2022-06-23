function [AC_PC_thick, mean_med, time, pp]=jr_convol(filename,scan0,n,m,fit)
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
%       filename: Name of the csv file
%       (The first column in the file should contain the positions) 
%       scan0: Initial scan 
%       n: Number of blocks
%       m: Number of scans in each block
%       (For peak detection in single scans set m=1 and n=number of scans)
%        (If m>1 we are averaging)
%       fit: If fit=1, we fit a quadratic curve to the PC 
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
%           [AC_PC_thick, mean_med]=main_convol('Summary_RGaligned',1,3,5,1)
%           [AC_PC_thick, mean_med]=main_convol('Summary_CHaligned',1,3,5,1)
%   %90     [AC_PC_thick, mean_med]=main_convol('RGSummaryAllScans',1,3,5,1)
%   %60     [AC_PC_thick, mean_med]=main_convol('JRSummaryAllScans',1,3,5,1)

convol=1;   % If convol=1, we use the AC peak as a template (prefered), if convol=0 we use the Zemax simulated profile
ct=1;       % Number of times to do the convolution (1 is prefered)


nc=1.3989;                  %Refractive index of cornea

% Select scans to average
totn=m*n;           % Total number of scans
blocks=1:m:totn;    % Indices for the blocks


% Read data
data0 = dlmread(filename,",", 1, 0); 
pos=data0(:,1);                     % Positions array
data0=data0(:,scan0+1:scan0+totn);   % Scans matrix

% Create set of data points at 1um intervals by interpolation
startpos = (ceil(pos(1) * 1000)) / 1000;
endpos = (floor(pos(size(pos, 1)) * 1000)) / 1000;
posq = startpos: 0.001: endpos;
dataq = interp1(pos, data0, posq);

% Save space
ACpos=zeros(n,1);
PCpos=zeros(n,1);
weight=zeros(n,1);

cla reset;
hold all
tic
for i=1:n           % Loop along each block
    i
    data=dataq(:,blocks(i):blocks(i)+m-1);
    if m~=1
        mean_data=jr_Average(posq,data);
    else       % If we are selecting single scans, do not call Average (we avoid translation of AC peak)
        mean_data=data;
    end

    y=mean_data;
    if convol==1
        for j=1:ct
            y=jr_convol_AC(y);   % Convolution with AC as template (favourite)
        end
    elseif convol==0
        for j=1:ct
            y=convol_prof(y); % Convolution with simulated profile as template
        end
    end
    
    plot(y,'DisplayName',[' Block ' num2str(i)]);
%   dlmwrite('xmm convolved.csv', y, ',');
    

    % ACpos(i)=jr_findAC_quad(posq,y);           % AC position
    %[PCpos(i),weight(i)]=findPC_max(ACpos,posq,y,fit); %PC pos and quality of scan (weight)
    %pause
end
legend('off'); legend('show')


time=toc

thick=abs(ACpos-PCpos)*nc;   % Thickness 
thick(PCpos==0)=0;
thick1=nonzeros(thick);     % We only choose the values different than zero since they have produced a value for PC

valid=size(thick1,1);       % Number of valid scans
fprintf( '\n Number of valid blocks (scans) is %i out of %i\n Total of scans used: %i \n', valid,totn/m,totn)
pp=valid/(totn/m)*100;      % Percentage of valid scans
fprintf('Percentage of valid scans %3.2f %% \n',pp)

mean_t=mean(thick1);
med_t=median(thick1);

mean_w=(thick'*weight)/sum(weight);   % Weighted mean 
med_w= weightedMedian(thick,weight);  % Weighted median 

mean_med=[mean_t,med_t,mean_w,med_w];

AC_PC_thick=[ACpos, PCpos, thick, weight];

end
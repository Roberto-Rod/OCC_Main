function [AC_PC_thick,mean_med,time,pp]=main(filename,sheet,scan0,n,m,filt,th)
% Description: Find the AC and PC peak positions, and the thickness of the
% cornea for each single scan or block of scan. Calculates mean and median
% of all the thickness values obtained.
% It operates by using n blocks of m scans.
%
% Author: Raquel Gonzalez
% Last update: 15/09/17
%
% Inputs:
%       filename: Name of the Excel file
%       sheet: Sheet of the Excel file where the data is.
%       (The first column in the Excel sheet should contain the positions array)  
%       scan0: Initial scan to consider
%       n: Number of blocks
%       m: Number of scans in each block
%       (For peak detection in single scans set m=1 and n=number of scans)
%        (If m>1 we are averaging blocks)
%       filt: If filt=1, we pass a moving average filter once (prefered)
%                filt=2, we pass it twice
%                else, no filter is applied
%       th: Threshold for the PC peak  (usually 0.02)
%
% Outputs:
%       AC_PC_thick=[ACpos, PCpos, thick]: Position of the AC peak, PC peak
%       and thickness.
%       mean_med=[mean_t,med_t]: Mean and median of the thickness values.
%       time: Computational time
%       pp: Percentage of accepted scans
%
% Examples: 
%           [AC_PC_thick,mean_med]=main('Summary_RGaligned',1,1,10,1,1,0.02)      %60 scans
%           [AC_PC_thick,mean_med]=main('Summary_CHaligned',1,1,10,1,1,0.02)
%           [AC_PC_thick, mean_med]=main('RGSummaryAllScans',1,1,4,5,1,0.02)          
%           [AC_PC_thick, mean_med]=main('JRSummaryAllScans',1,1,5,5,1,0.02) 


% Select scans to average
totn=m*n;            % Total number of scans
blocks=1:m:totn;     % Indices for the blocks

% Read data
data1 = xlsread(filename,sheet); 
pos=data1(:,1);                      % Positions array
data0=data1(:,scan0+1:scan0+totn);   % Scans intensity matrix
        

% Save space
ACpos=zeros(n,1);
PCpos=zeros(n,1);

tic

for i=1:n      % Loop along each block
    %i
    data=data0(:,blocks(i):blocks(i)+m-1);
    if m~=1
        mean_data=Average(pos,data);
    else       % If we are selecting single scans, do not call Average (we avoid translation of AC peak)
        mean_data=data;
    end
% 
%     figure(1)
%     subplot(1,n,i)
%     
    if filt==1 || filt==2           % Filter once
        dataf=movmean(mean_data,8);
        if filt==2                  % Filter twice
            dataf=movmean(dataf,8);
        end
%         plot(pos,mean_data,'-',pos,dataf,'-k')
%         legend('Original Data','Filtered Data')

    else
         dataf=mean_data;       %No filtering
%         plot(pos,dataf,'-')
%         legend('Original Data')
    end
    
   
    ACpos(i)=findAC_quad(pos,dataf);                % AC peak position
    PCpos(i)=findPC_quad(ACpos(i),pos,dataf,th);    % PC peak position

%pause
       
end
time=toc

nc=1.3989;                  %Refractive index of cornea
thick=abs(ACpos-PCpos)*nc;   % Thickness 

thick(PCpos==0)=0;          % In the final mean, include only values where a PC peak has been found
thick1=nonzeros(thick);   % that is, where PCpos is different than zero.

valid=size(thick1,1); % Number of valid scans
fprintf( '\n Number of valid blocks (scans) is %i out of %i\n Total of scans used: %i \n', valid,totn/m,totn)
pp=valid/(totn/m)*100;
fprintf('Percentage of valid scans %3.2f %% \n',pp)

mean_t=mean(thick1);        % Mean
med_t=median(thick1);       % Median

mean_med=[mean_t,med_t];

AC_PC_thick=[ACpos, PCpos, thick];
end
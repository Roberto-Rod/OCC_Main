function [DataSetWeightedMeansAll, DataSetWM]= batch_main_convol()

%User Settings
fileName = 'Output-25-20';
scanDirectory = 'X:\LeinCompanyData\Personal Folders\GKitteridge\Data\data\500s\';
%numberOfBlocksAndBlockSize = [10, 20, 5; 30, 15, 60];
numberOfBlocksAndBlockSize = [25;20];
plotFigures = 1; %Bool value
peakFindType = 1; %newer amplitude based
debug = 0; %set to one if you only want to run through the first set of blocks

%If you turn this on then it will only add valid scans to the final output
%array, you can tweak these values but the formula is:
%valid scan = (pp-qq > validPPQQ) && (wmSDE < validWMSDE) && mean_wt > validMEANT
onlyAddValidScans = 0;
onlyAddNonValidScans = 0;
validPPQQ = 50;
validWMSDE = 20;
validMEANT = 0.85;

%--------------------------%


scans = sprintf('%s*-Scan.csv', scanDirectory);
% Load in any scan files in the below folder
[status, list] = system( ['dir /B /S ',scans] );
result = textscan( list, '%s', 'delimiter', '\n' );
DataFiles = result{1}

[numberOfDataFiles,notUsed] = size(DataFiles);
[notUsed2, blocksCount] = size(numberOfBlocksAndBlockSize);
if debug == 1
 blocksCount =  1; %set for debugging to only run through the scan set once
end
% We want to do a set of processing for each data file, that may be
% changing the block size and processing for each one etc
for count = 1:blocksCount
    % Process for each block size
    
    for innerCount = 1:numberOfDataFiles
        try
            [a,b,pp,qq,weightedMean, wmSDE, mean_wt] = main_convol_GK(DataFiles(innerCount),1,1,numberOfBlocksAndBlockSize(1,count),numberOfBlocksAndBlockSize(2,count),1, plotFigures,peakFindType)
             fprintf('End of DataFile\n\n');
             if onlyAddValidScans == 1
                 if (pp-qq > validPPQQ) && (wmSDE < validWMSDE) && mean_wt > validMEANT
                     OutputData(innerCount,1, count) = weightedMean;
                     OutputData(innerCount,2,count) = wmSDE;
                     OutputData(innerCount,3,count) = mean_wt;
                     OutputData(innerCount,4,count) = pp; % Percentage of valid scans
                     OutputData(innerCount,5,count) = qq; % Percentage of outliers
                     OutputData(innerCount,6,count) = pp-qq; % Percentage of outliers
                 else
                     % Just fill with zeroes
                     OutputData(innerCount,1, count) = 0;
                     OutputData(innerCount,2,count) = 0;
                     OutputData(innerCount,3,count) = 0;
                     OutputData(innerCount,4,count) = 0; 
                     OutputData(innerCount,5,count) = 0; 
                     OutputData(innerCount,6,count) = 0;
                 end
             elseif onlyAddNonValidScans == 1
                 if (pp-qq > validPPQQ) && (wmSDE < validWMSDE) && mean_wt > validMEANT
                     % Just fill with zeroes
                     OutputData(innerCount,1, count) = 0;
                     OutputData(innerCount,2,count) = 0;
                     OutputData(innerCount,3,count) = 0;
                     OutputData(innerCount,4,count) = 0; 
                     OutputData(innerCount,5,count) = 0; 
                     OutputData(innerCount,6,count) = 0;
                 else
                     
                     OutputData(innerCount,1, count) = weightedMean;
                     OutputData(innerCount,2,count) = wmSDE;
                     OutputData(innerCount,3,count) = mean_wt;
                     OutputData(innerCount,4,count) = pp; % Percentage of valid scans
                     OutputData(innerCount,5,count) = qq; % Percentage of outliers
                     OutputData(innerCount,6,count) = pp-qq; % Percentage of outliers
                 end
             else
                 OutputData(innerCount,1, count) = weightedMean;
                 OutputData(innerCount,2,count) = wmSDE;
                 OutputData(innerCount,3,count) = mean_wt;
                 OutputData(innerCount,4,count) = pp; % Percentage of valid scans
                 OutputData(innerCount,5,count) = qq; % Percentage of outliers
                 OutputData(innerCount,6,count) = pp-qq; % Percentage of outliers
             end
        end   
        %close all 
    end
    
end

DataSetWeightedMeansAll = OutputData
%DataSetWM = sum(DataSetWeightedMeansAll,1) ./ sum(DataSetWeightedMeansAll~=0,1)
DataFiles
%Output results to file
Filename = sprintf('%s\\%s_%s%s', scanDirectory, fileName ,datestr(now,'mm-dd-yyyy HH-MM'),'.csv');
csvwrite(Filename,DataSetWeightedMeansAll)

%Play very annoying finishing sound
%load gong
%sound(y,Fs)
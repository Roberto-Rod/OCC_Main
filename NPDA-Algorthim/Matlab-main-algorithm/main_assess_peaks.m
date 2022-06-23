function [ output_args ] = main_assess_peaks( data_folder_path,sheet,scan0,n,m,fit, plotFigures, peakFindType )
%
%   This function assesses the quality of peaks on calibration data.
%   Calibration is normally performed using a mirror, so gives only a
%   single peak, but can be performed using a glass flat, in which case of
%   course only the front ('AC') peak is used for calibration.
%
%   As such it uses the same functions as those used in the analysis of eye
%   data (or indeed simulated eye data or verification data. This ensures
%   consistency of method between calibration, verification and operation.

%   Inputs:
%       data_folder_path: Name of the Excel file
%       sheet: Sheet of the Excel file where the data is
%       (The first column in the Excel sheet should contain the positions) 
%       scan0: Initial scan 
%       n: Number of blocks
%       m: Number of scans in each block
%       (For peak detection in single scans set m=1 and n=number of scans)
%        (If m>1 we are averaging)
%       fit: If fit=1, we fit a quadratic curve to the PC 
%       peakFindType: 0 prominence, 1 amplitude (newer)

%   Outputs:
%       peak quality.csv:A file containing the calibration lookup table:
%           Column 1: Measured position of peak (in encoder space)
%           Column 2: Position of peak in target space calculated from raw
%           data
%           Column 3: Position of peak in target space calculated from
%           smoothed data
%           Column 4: Position of peak in target space calculated by
%           calibration coefficients
%           Column 5: Position of peak in target space: an average of
%           column 2 and column 3.

hold off;
numberOfBlocks = n;
blockSize = m;
fprintf('number Of Blocks: %d, block size: %d\n', numberOfBlocks, blockSize);
convol=1;   % If convol=1, we use the AC peak as a template (prefered), if convol=0 we use the Zemax simulated profile
slope = 1;
ct=1;       % Number of times to do the convolution (1 is prefered)
hampel = 1; % Flag for Hampel filtering
nc=1.0; 
resolution=0.001;
% Select scans to average
totn=m*n;           % Total number of scans
blocks=1:m:totn;    % Indices for the blocks
% Save space


data_filename = dir([data_folder_path,'\*mm.csv']);

% Sort data file names (when they are number based Matlab can confuse the
% order), for numerical file naming
[sorted_data_filename, xpos] = sort_num_based_filename(data_filename,'m');
dist = xpos';
startflag = 0;
caldata = zeros(1, length(dist));

op_filename = [data_folder_path '\Peak characteristics.csv'];
fileID = fopen(op_filename, 'w');
fprintf(fileID, 'File, Mean peak position, SD peak position, Mean height, SD height, Mean FWHM, SD FWHM, Mean SNR, SD SNR, PS displacement, PC height, PS weight\n');

for j = 1 : length(data_filename)
    file_path = [data_folder_path,'\',sorted_data_filename(j).name];
    
    % Read data from calibration file
    %data1 = dlmread(char(file_path),',', scan0, 0); 
    % First two scans are unreliable, do not read
    %dataq = data1';
    
    % Alternative if data in *-raw format
    dataq = dlmread(char(file_path),',', 0, scan0);
    
    %pos=data0(:,1);                    % Positions array in um
    posp = 0:1:4997;                % Use if looking at calibrated data
    pos = posp';
    %dataq=data0(:,scan0+1:scan0+totn);   % Scans matr
    ACpos=zeros(n,1);
    fwhm = zeros(n, 1);
    idx = zeros(n, 1);
    ACht = zeros(n, 1);
    ACheight = zeros(n, 1);
    SNR = zeros(n, 1);
    dataq = dataq';
    % Check that data contains peak
    datamed = median(dataq(:, 3));
    datamax = max(dataq(:, 3)) - datamed;
    dataLH = dataq(4, 3) -  datamed;
    dataRH = dataq(length(dataq) - 3, 3) - datamed;
    
    if (datamax > 10000) && (dataLH < datamax / 2) && (dataRH < datamax / 2)
        %fprintf('%s\t%i\t%i\n', sorted_data_filename(j).name, size(dataq, 1), size(dataq, 2));
        if startflag == 0
            startflag = 1;
            jstart = j;
        end
        data_av = median(dataq, 2);
        med_av = median(data_av);
        data_av = data_av - med_av;
       
        %%
        % 
    
        for i=3:n           % Loop along each block
            %i
        
            data=dataq(:, i);
            data_m = median(data);
            ACht(i) = max(data) - data_m;
            [mean_data, backshift, fwhm(i), idx(i)] = Average_AC_align3(pos, data, resolution, 0);
            % Note: much more reliable PC peak detection if the AC peaks are
            % aligned: this should be done even with single scans

            y=mean_data - median(mean_data);
            if plotFigures == 1
                figure(3);
                hold on
                plot(y,'DisplayName',[' Block ' num2str(i)]);
                hold off
            else
            end
    
            if convol==1
                for k=1:ct
                    y=jr_convol_AC(y);   % Convolution with AC as template (favourite)
                end
            elseif convol==0
                for k=1:ct
                    y=jr_convol_prof(y); % Convolution with simulated profile as template
                end
            end
        
            if backshift ~= 0
                if backshift>0               % When the scan is on the right from ref scan
                    yb = [y(backshift+1:end); zeros(backshift,1)];
                else                     % On the left or centered
                    yb=[zeros(abs(backshift),1); y(1:end+backshift)];
                end
                y = yb;
            end
        
            if plotFigures == 1
                figure(2);
                %hold on
                plot(y,'DisplayName',[' Block ' num2str(i)]);
                %hold off
            else
            end
    
            [q1, q2] = find_AC_peak(y);
            %ACpos(i)=findAC_quad(pos(q1:q2), y(q1:q2), resolution) / resolution;  
            AC1 = max(y(q1:q2));
            ACind = find(y == AC1);
            ACpos(i) = pos(ACind);
            % AC position in encoder counts
            ACheight(i) = max(y(q1:q2));
            %fprintf('%f\t%i\t%i\n', dist(j), ACpos(i), backshift);
            
            a = floor(ACpos(i) - 1 / resolution);   % Find SNR
            b = floor(ACpos(i) + 1 / resolution);
            if a < 1
                noise = data(b:length(pos))';
            elseif b > length(pos)
                noise = data(1:a)';
            else
                noise = [data(1:a)' data(b:length(pos))'];             
            end
            
            SNR(i) = ACht(i) / std(noise);
           
                
            
        end
    
      
        ACmax = max(ACheight);     % Largest AC peak
        ACpos(ACheight < 0.2 * ACmax) = 0; % Reject blocks where the AC peak is suppressed
    
        median_t = floor(median(ACpos));
        median_f = median(fwhm);
        median_i = floor(median(idx));
        median_h = median(ACht);
        madse_t = median(abs(ACpos - median_t)) * 1.4826;
        outliers = 0;
        if (hampel == 1)
            for i = 1: length(ACpos)
                if (abs(ACpos(i) - median_t) > 1.5 * madse_t)
                    ACpos(i) = median_t;
                    fwhm(i) = median_f;
                    idx(i) = median_i;
                    ACht(i) = median_h;
                    outliers = outliers + 1;
                end
            end
        end
        
        figure(7);
        plot(pos, data_av);
        % Find any subsidiary peaks
        [PCpos, PCheight, weight]=find_all_peaks_jr3(median_t, pos, data_av, slope, 0, nc, resolution);
        
        
        qq = outliers / (totn / m) * 100;   % Percentage of outliers    
    
        caldata(j) = mean(ACpos);
        sd_t(j) = std(ACpos);
        m_fwhm = mean(fwhm(3:n));
        sd_fwhm = std(fwhm(3:n));
        m_idx = mean(idx(3:n));
        sd_idx = std(idx(3:n));
        m_ht = mean(ACht(3:n));
        sd_ht = std(ACht(3:n));
        m_snr = mean(SNR);
        sd_snr = std(SNR);
        fprintf(fileID, '%s,%f,%f,%f,%f,%f,%f,', sorted_data_filename(j).name, caldata(j), sd_t(j), m_ht, sd_ht, m_fwhm, sd_fwhm );
        if (PCpos <= 0)
            PCpos = caldata(j);
        end
        fprintf(fileID, '%f,%f,%f,%f,%f\n', m_snr, sd_snr, PCpos - caldata(j), PCheight, weight);

        
     
    else
        fprintf('%s\t%i\t%i\t%i\n', sorted_data_filename(j).name, datamax, dataLH, dataRH);    
        if startflag == 1
            startflag = 0;
            jfinish = j - 1;
        end
    end
end

fclose(fileID);
% Perform light MA filter on data
ma_factor = 5;
jstart = ma_factor + 1;
jend =length(data_filename) - ma_factor;
for j = 1: length(data_filename)
    if (j < jstart) || (j > jend)
        ma_caldata(j) = caldata(j);
    else
        ma_caldata(j) = mean(caldata(j - ma_factor: j + ma_factor));
    end
end

% Reference distances to the start of the scan range
m = (ma_caldata(6) - ma_caldata(2)) / (dist(6) - dist(2));
d0 = dist(6) - ma_caldata(6) / m;
dist = dist - d0;
%fprintf('%i\t%i\n', size(caldata),size(dist));

figure(1);  
plot(caldata, dist);
p2 = polyfit(caldata, dist, 2);
% find best fit quadratic for calibrated data to actual position
% Two-step process performed to minimise rounding errors
%disp(p2);

poly2 = p2(1) * caldata.^2 + p2(2) * caldata + p2(3);
quaderror = dist - poly2;
%figure(4);
%plot(caldata, quaderror);

% fit quartic to fit error
p4 = polyfit(caldata, quaderror, 4);
q4 = polyfit(caldata, dist, 4);

% Add coefficients together to give final polynomial approximation
p4(3) = p4(3) + p2(1);
p4(4) = p4(4) + p2(2);
p4(5) = p4(5) + p2(3);
fprintf('Coefficients are:\n %e\n%e\n%e\n%e\n%e\n', p4(1), p4(2), p4(3), p4(4), p4(5));
fprintf('Coefficients are:\n %e\n%e\n%e\n%e\n%e\n', q4(1), q4(2), q4(3), q4(4), q4(5));

poly4 = p4(1) * caldata.^4 + p4(2) * caldata.^3 + p4(3) * caldata.^2 + p4(4) * caldata + p4(5);
quarterror = dist - poly4;

%figure(6);
%plot(caldata, quarterror);
%dlmwrite('Calibration error.csv', caldata);
%dlmwrite('Calibration error.csv', quarterror, '-append');
hold off;

fprintf('Mean and SD of fit: %f um\t%f\n', mean(quarterror)*1000, std(quarterror)*1000);

ilim = 5000;
cal_lookup = zeros(ilim+1, 5);

% Create lookup table
k = length(caldata);
ma = 35;
j = 2;

for i = 0:ilim
  b = i * resolution;
  q = i + 1;
  if ((b > caldata(j)) && (j < k))
    j = j + 1;
    %fprintf('%f\t%i\t%i\n', dist(j), caldata(j), ma_caldata(j));
  end
  cal_lookup(q, 1) = b;    % Position
  
  % Linear interpolation
  denom = caldata(j) - caldata(j - 1);
  if abs(denom) > 0.0005            % Error trap
      cal_lookup(q, 2) = dist(j) - (dist(j) - dist(j - 1)) * ((caldata(j) - b) / denom);
  else      % If error, extrapolate from existing results
      if (i > 1)
        cal_lookup(q, 2) = 2 * cal_lookup(i, 2) - cal_lookup(i-1, 2);
      end
  end
  
  % Averaged and interpolated
  denom = ma_caldata(j) - ma_caldata(j - 1);
  if abs(denom) > 0.0005            % Error trap
      cal_lookup(q, 3) = dist(j) - (dist(j) - dist(j - 1)) * ((ma_caldata(j) - b) / denom);
  else      % If error, extrapolate from existing results
      if (i > 1)
        cal_lookup(q, 3) = 2 * cal_lookup(i, 3) - cal_lookup(i-1, 3);
      end
  end
  
  % Quartic fit
  cal_lookup(q, 4) = p4(1) * b.^4 + p4(2) * b.^3 + p4(3) * b.^2 + p4(4) * b + p4(5);
end

% Averaged and smoothed
for i = 0:ilim
  imin = i - ma;
    if (imin < 1)
        imin = 1;
    end
  imax = i + ma;
    if (imax > ilim)
        imax = ilim;
    end
  cal_lookup(i+1, 5) = cal_lookup(i+1, 3) - mean(cal_lookup(imin:imax, 3) - cal_lookup(imin:imax, 2));
end
   
dist_file = strcat(data_folder_path, '\Dist.csv');
dlmwrite(dist_file, [xpos caldata']);
lookup_file = strcat(data_folder_path, '\Cal lookup.csv');
dlmwrite(lookup_file, cal_lookup);
    

end


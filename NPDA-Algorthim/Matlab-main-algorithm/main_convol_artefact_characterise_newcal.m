function [ output_args ] = main_convol_artefact_characterise_newcal( data_folder_path, lookup_path)
%
%   This function performs the convolution algotithm on calibration data.
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
%       cal_lookup.csv:A file containing the calibration lookup table:
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

% Set essential parameters for data analysis
sheet = 1;
scan0 = 1;
n = 100;
m = 1;
fit = 1;
plotFigures = 0;
peakFindType = 0;

numberOfBlocks = n;
blockSize = m;
%fprintf('number Of Blocks: %d, block size: %d\n', numberOfBlocks, blockSize);
convol=1;   % If convol=1, we use the AC peak as a template (prefered), if convol=0 we use the Zemax simulated profile
ct=1;       % Number of times to do the convolution (1 is prefered)
hampel = 1; % Flag for Hampel filtering
start = 1;  % Flag for indicating first valid measurement
stop = 0;   % Flag for indicating end of valid measurement region

%nc = 1.3989;   % Cornea
%nc = 1.482;    % Acrylic
nc = 1.4468;    % Fused silica

resolution=0.001;
% Select scans to average
totn=m*n;           % Total number of scans
blocks=1:m:totn;    % Indices for the blocks
% Save space

% Find the lowest level folder name
k = strfind(data_folder_path, '\');
folder_name = data_folder_path(k(length(k)) + 1:length(data_folder_path));

data_filename = dir([data_folder_path,'\*mm.csv']);

% Use positions based on calibration data
lookup0 = dlmread(char(lookup_path), ',', 1, 0);

% Sort data file names (when they are number based Matlab can confuse the
% order), for numerical file naming
[sorted_data_filename, xpos] = sort_num_based_filename(data_filename,'m');
dist = xpos';
startflag = 0;
caldata = zeros(1, length(dist));
z = length(data_filename);
pmax = zeros(z, 1);
pFWHM = zeros(z, 1);
pSNR = zeros(z, 1);
pmaxsd = zeros(z, 1);
pFWHMsd = zeros(z, 1);
pSNRsd = zeros(z, 1);
pPC = zeros(z, 1);
pPCsd = zeros(z, 1);
mean_w = zeros(z, 1);
sd_w = zeros(z, 1);
mean_wt = zeros(z, 1);
sd_wt = zeros(z, 1);
mean_AC = zeros(z, 1);
sd_AC = zeros(z, 1);
fprintf('Running');

for j = 1 : z
    file_path = [data_folder_path,'\',sorted_data_filename(j).name];
    
    % Read data from calibration file
    %data1 = dlmread(char(file_path),',', scan0, 0); 
    % First two scans are unreliable, do not read
    %dataq = data1';
    
    % Alternative if data in *-raw format
    dataq = dlmread(char(file_path),',', 0, scan0);
    
    %pos=data0(:,1);                    % Positions array in um
    posp = 0:1:4999;                % Use if looking at calibrated data
    pos = posp' * resolution;
    
    dsize = size(dataq, 2);
    lsize = size(lookup0, 1);
    if dsize > lsize
        dataq=dataq(scan0:scan0+totn-1, 1:lsize);   % Scans matr
        pos=lookup0(:, 2);                          % Positions array
    else
        dataq=dataq(scan0:scan0+totn-1, :);         % Scans matr
        pos=lookup0(1:dsize, 2);                    % Positions array
    end
        
    %pos = posp';
    %dataq=data0(:,scan0+1:scan0+totn);   % Scans matr
    ACpos=zeros(n,1);
    dataq = dataq';
    % Check that data contains peak
    sample = 5;
    datamed = median(dataq(:, sample));
    [datamax, p_max] = max(dataq(:, sample));
    datamax = datamax - datamed;
    dataLH = dataq(3, sample) -  datamed;
    dataLHgrad = dataq(8, sample) - dataq(3, sample);
    dataRH = dataq(length(dataq) - 3, sample) - datamed;
    dataRHgrad = dataq(length(dataq) - 3, sample) - dataq(length(dataq) - 8, sample);
    peak_replaced = 0;
    % Check that it is the AC peak (useful for verification on silica target and wedge prisms)
    LH_zone = 200;
    if (p_max > LH_zone)  % If peak at extreme left of scan, assume AC peak
        temp_data = dataq(1: p_max - LH_zone, sample) - datamed;
        [candidate_peak, p_cand] = max(temp_data);
        if (8 * candidate_peak > datamax)
            datamax = candidate_peak;
            p_max = p_cand;
            peak_replaced = 1;
        end
    end
    
    if (datamax > 3500)
        % fprintf('%i\t%i\t%i\n', peak_replaced, datamax, p_max);
        if (peak_replaced == 1) || (((dataLH < datamax / 2) || (dataLHgrad < 0)) && ((dataRH < datamax / 2) || (dataRHgrad > 0)))
            % Need to capture cases where the peak is away from the edges
            % Sometimes a second peak will be at the edge, need to ignore
            % this. Cut out by checking the slope: if it has the wrong sign
            % it is definitely a second peak.
            %fprintf('%s\n', sorted_data_filename(j).name);
            fprintf('.');
            if startflag == 0
                startflag = 1;
                jstart = j;
            end
    
            maxy = zeros(n, 1);
            FWHMy = zeros(n, 1);
            SNRy = zeros(n, 1);
            PCpos = zeros(n, 1);
            weight = zeros(n, 1);
            ACp = zeros(n, 1);
            for i=3:n           % Loop along each block
          
        
                %data=dataq(:,blocks(i):blocks(i) + m - 1);
                data = dataq(:, i);
                if (i == 50)
                    pf = 1;
                else
                    pf = 0;
                end
            
                [mean_data, ACp(i), a2, backshift] = Average_AC2(pos, data, resolution, 0);
                %[mean_data, backshift] = Average_AC_align2(pos, data, resolution, 0);
                % Note: much more reliable PC peak detection if the AC peaks are
                % aligned: this should be done even with single scans


                y=mean_data - median(mean_data);
                if plotFigures == 1
                    figure(3);
                    hold on
                    plot(y,'DisplayName',[' Block ' num2str(i)]);
                    hold off
                end
            
                % Find maximum
                if p_max < 100
                    LHS = 1;
                else
                    LHS = p_max - 100;
                end
                if p_max > length(y) - 100
                    RHS = length(y);
                else
                    RHS = p_max + 100;
                end
                maxy(i) = max(y(LHS:RHS));
                % All peaks in roughly the same position, so peak will not
                % move far between scans
                
            
                % Find FWHM
                fy = maxy(i) / 2;
                q = p_max;
                while ((y(q) > fy) && ( q < length(y)))
                    q = q + 1;
                end
                RHy = q;
                q = p_max;
                while ((q > 1) && (y(q) > fy))
                    q = q - 1;
                end
                LHy = q;
                FWHMy(i) = RHy - LHy;
                            
                %LHlimit = p_max - 250;
                %if LHlimit > 1
                %    LHflat = y(1:LHlimit);
                %else
                %    LHflat = [];
                %end
                %RHlimit = p_max + 250;
                %if RHlimit < length(y)
                %    RHflat = y(RHlimit:length(y));
                %else
                %    RHflat = [];
                %end   
                % Find SNR of single scan
                %no_peak_y = [LHflat' RHflat'];
                %no_zeros_y = nonzeros(no_peak_y);
                hampel_y = hampel_filter(y, 3);
                noise = std(hampel_y);
                SNRy(i) = maxy(i) / noise;
            
                %fprintf('%i\t%i\t%f\n', maxy, FWHMy, SNRy);
                     
               
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
                end
    
                [q1, q2] = find_AC_peak2(y);
                %ACpos(i)=findAC_quad(pos(q1:q2), y(q1:q2), resolution) / resolution;  
                AC1 = max(y(q1:q2));
                ACind = find(y == AC1, 1);
                ACpos(i) = pos(ACind);
                % AC position in encoder counts
                ACheight(i) = max(y(q1:q2));
                %fprintf('%f\t%i\t%i\n', dist(j), ACpos(i), backshift);
            
            
                [PCpos(i), PCheight(i), weight(i)]=find_all_peaks_jr3(ACind, pos, y, 0, 0, nc, resolution, pf);
            end

            ACpa = nonzeros(ACp);
            w1 = nonzeros(weight);
            %fprintf('%i\t%f\t%f\t%f\t%f\n', j, mean(w1), std(w1), max(w1), min(w1));
            
            ACpa = hampel_filter(ACpa, 3);
            if start == 1   % Find the scan closest to the front edge
                if mean(ACpa) < 0.12
                    start = 0;
                end
            end
            if stop == 0
                if mean(ACpa) > 4.88
                    stop = 1;
                end
            end
                                       
            %if ((start == 0) && (stop == 0))   % Scan probably in range or all scans taken
                FWHMy = hampel_filter(nonzeros(FWHMy), 3);
                if mean(FWHMy) > 20     % Peak not truncated by edge of scan
                    maxy = hampel_filter(nonzeros(maxy), 3);
                    SNRy = hampel_filter(nonzeros(SNRy), 3);
                    heighty = hampel_filter(PCheight, 3);
                    pmax(j) = round(mean(maxy));
                    pFWHM(j) = mean(FWHMy);
                    pSNR(j) = round(mean(SNRy));
                    pPC(j) = mean(heighty);
                    pmaxsd(j) = round(std(maxy));
                    pFWHMsd(j) = std(FWHMy);
                    pSNRsd(j) = round(std(SNRy));
                    pPCsd(j) = std(heighty);
                    mean_AC(j) = mean(ACpa);
                    sd_AC(j) = std(ACpa);
                    [valid, mean_t, sd_t, median_t, madse_t, mean_w(j), sd_w(j), mean_wt(j), sd_wt(j)] = find_thicknesses(ACheight, ACpos, PCpos, weight, nc, 0, 1, 0);
                    caldata(j) = mean(ACpos);
                end
            %end

      
        
            %ACpos = hampel_filter(ACpos, 3);  
            %PCpos = hampel_filter(PCpos, 3); 

                
            
        end
           
    else
        %fprintf('%s\t%i\t%i\t%i\t%i\n', sorted_data_filename(j).name, datamax, p_max, dataLH, dataRH);    
        if startflag == 1
            startflag = 0;
            jfinish = j - 1;
        end
    end
end

fprintf('\n');
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
if length(ma_caldata) > 5
    cp = 6;
else
    cp = length(ma_caldata);
end
m = (ma_caldata(cp) - ma_caldata(2)) / (dist(cp) - dist(2));
d0 = dist(cp) - ma_caldata(cp) / m;
    
dist = dist - d0;

if plotFigures == 1
    figure(1);  
    plot(caldata, dist);
end
p2 = polyfit(caldata, dist, 2);
% find best fit quadratic for calibrated data to actual position
% Two-step process performed to minimise rounding errors
%disp(p2);

poly2 = p2(1) * caldata.^2 + p2(2) * caldata + p2(3);
quaderror = dist - poly2;
if plotFigures == 1
    figure(4);
    plot(caldata, quaderror);
end

% fit quartic to fit error
p4 = polyfit(caldata, quaderror, 4);
q4 = polyfit(caldata, dist, 4);

% Add coefficients together to give final polynomial approximation
p4(3) = p4(3) + p2(1);
p4(4) = p4(4) + p2(2);
p4(5) = p4(5) + p2(3);
%fprintf('Coefficients are:\n %e\n%e\n%e\n%e\n%e\n', p4(1), p4(2), p4(3), p4(4), p4(5));
%fprintf('Coefficients are:\n %e\n%e\n%e\n%e\n%e\n', q4(1), q4(2), q4(3), q4(4), q4(5));

poly4 = p4(1) * caldata.^4 + p4(2) * caldata.^3 + p4(3) * caldata.^2 + p4(4) * caldata + p4(5);
quarterror = dist - poly4;

if plotFigures == 1
    figure(6);
    plot(caldata, quarterror);
    %dlmwrite('Calibration error.csv', caldata);
    %dlmwrite('Calibration error.csv', quarterror, '-append');
    hold off;
end

%fprintf('Mean and SD of fit: %f um\t%f\n', mean(quarterror)*1000, std(quarterror)*1000);

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

figure(7);

plot(mean_AC, pmax, '*');
title(strcat(folder_name, ' Peak Height'));
maxpmax = max(pmax);
if maxpmax > 50000
    axis([0, 5, 0, inf]);
else
    axis([0, 5, 0, 50000]);
end
fprintf('Maximum peak amplitude:\t%i\n', maxpmax);

pSNRz = nonzeros(pSNR);
minpSNR = min(pSNRz);
fprintf('Minimum SNR (ignore if target not normal):\t%i\t', minpSNR);
if minpSNR < 200
    fprintf('FAIL\n');
else
    fprintf('PASS\n');
end

ax = [0 5];
ay = [55, 55];
figure(8);
plot(mean_AC, pFWHM, '*', ax, ay);
title(strcat(folder_name, ' FWHM'));
if max(pFWHM) > 80
    axis([0, 5, 0, inf]);
else
    axis([0, 5, 0, 80]);
end
maxpFWHM = round(max(pFWHM));
fprintf('Maximum FWHM (ignore if target not normal):\t%i\t', maxpFWHM);
if maxpFWHM > 55
    fprintf('FAIL\n');
else
    fprintf('PASS\n');
end

figure(9);
plot(mean_AC, mean_w, '*');
title(strcat(folder_name, ' Candidate PC Position'));
axis([0, 5, 0, 0.9]);


a = length(xpos);
x1 = zeros(a, 1);
x2 = zeros(a, 1);
y1 = zeros(a, 1);
y2 = zeros(a, 1);
wt_pass = 1;
for i = 1:a
    if ((mean_wt(i) >= 0.7) || ((mean_wt(i) >= 0.6) && (mean_w(i) >= 0.35) && (mean_w(i) <= 0.7)))
        x2(i) = mean_AC(i);
        y2(i) = mean_wt(i);
        wt_pass = 0;
    else
        x1(i) = mean_AC(i);
        y1(i) = mean_wt(i);
    end
end
%x1 = nonzeros(x1);
%x2 = nonzeros(x2);
%y1 = nonzeros(y1);
%y2 = nonzeros(y2);
figure(10);
plot(x1, y1, '*', x2, y2, 'o');
title(strcat(folder_name, ' Candidate PC weight'));
axis([0, 5, 0, 1]);
if wt_pass == 1
    fprintf('Candidate PC peak:\tPASS\n');
else
    fprintf('Candidate PC peak:\tFAIL\n');
end



dist_file = strcat(data_folder_path, '\Peak characterisation.csv');
dlmwrite(dist_file, [xpos mean_AC sd_AC pmax pmaxsd pPC pPCsd pFWHM pFWHMsd pSNR pSNRsd mean_w sd_w mean_wt sd_wt]);
%lookup_file = strcat(data_folder_path, '\Characterised Cal lookup.csv');
%dlmwrite(lookup_file, cal_lookup);
    

end


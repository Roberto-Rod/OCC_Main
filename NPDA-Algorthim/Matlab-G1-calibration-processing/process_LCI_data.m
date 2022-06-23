function process_LCI_data(filepath, filename, min, max, num_scans)

% This function convolves a Lorentzian with the confocal data coming from
% iScan Confocal. The first scan is ignored as it contains incorrect data.
% The ideal confocal peak is Lorentzian, so this should give near-optimal
% filtering. The aim of this is to reduce the magnitude of errors caused by
% asymmetry on the peak due to noise.

% As the interfaces of interest for measurement in vitro are silica/water,
% the amplitude of the peak from these is quite small. Consequently we need
% all the filtering and noise reduction we can get.

s = strcat(filepath, '\', filename);
r = strcat(filepath, '\LCI peak.csv');
%fprintf('%s\n', r);
peak = csvread(r, 1, 0);

thickdata = zeros(max - min + 1, num_scans);

for i = min: max
    p = i - min + 1;
    t = [s ' ' num2str(i) '-Scan.csv'];
    %fprintf('%s\n', t);
    rawdata = csvread(t);
    x = rawdata(:, 1);
    a = size(rawdata, 1);
    convdata = zeros(a, num_scans);
    convdata(:, 1)= x;
    peakdata = zeros(4, num_scans);
    thickdata(p, 1) = i;
    
    for j = 3:num_scans+1
        % Set data spacing to 1um
        k = j - 1;
        
        m = median(rawdata(:, k));
        rawdata(:, k) = rawdata(:, k) - m;
        
        % Perform convolution
        convdata(:, k) = conv(rawdata(:, k), peak(:, 2), 'same');
        plot(convdata(:, 1), convdata(:, 2));
        % Find the peak positions
        b = 1;
        for n = 2:(size(convdata, 1) - 1)
            if convdata(n, k) > 10
                %fprintf('%i', n);
                if (convdata(n-1, k) <= convdata(n, k)) && (convdata(n+1, k) < convdata(n, k))
                    peakdata(b, k) = convdata(n, 1);
                    b = b + 1;
                end
            end
        end 
        
        thickdata(p, k) = peakdata(2, k) - peakdata(1, k);  
        p3data(p, k) = peakdata(2, k);
        p2data(p, k) = peakdata(1, k);
          
    end
end


% Hampel filter
t_data = thickdata;
t_data(:, 1) = [];
t_med = median(t_data, 2);
t_medarray = repmat(t_med, 1, size(t_data, 2));
t_ad = abs(t_data - t_medarray);
t_madse = 1.4826 * median(t_ad, 2);
for i = 1: max - min + 1
    for j = 1: size(t_data, 2)
        if abs(t_data(i, j) - t_medarray(i, j)) > 3 * t_madse(i)
            t_data(i, j) = t_medarray(i, j);
        end
    end
end

f_mean = mean(t_data, 2);
m_mean = mean(f_mean);
m_sd = std(f_mean, 1);
fprintf('%f\n', f_mean);
fprintf('%f\t%f\n', m_mean, m_sd);

outfile = [s ' ' num2str(min) ' ' num2str(max) '-Thick.csv'];
csvwrite(outfile, thickdata);
outfile = [s ' ' num2str(min) ' ' num2str(max) '-P2.csv'];
csvwrite(outfile, p2data);
outfile = [s ' ' num2str(min) ' ' num2str(max) '-P3.csv'];
csvwrite(outfile, p3data);
end

        
        

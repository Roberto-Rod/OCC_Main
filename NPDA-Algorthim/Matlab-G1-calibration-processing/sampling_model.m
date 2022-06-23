function sampling_model(sample_length)

% This function models the effect of varying the sampling interval and the
% filter width on simulated LCI data. Parameters of the simulated data have
% been set to approximate to the data seen in the real LCI system.

% Sample_length is assumed to be in um, MA_length is a number. It is
% assumed that four passes are made on the filter.

% Data examined is assumed to extend over 200um (long enough to avoid
% edge effects).

% All constants and calculations in um.

lambda = 1.32;
HWHM = 15;
n_ma = 4;
filter_length = 25.6;
data_length = 200;

scans = 30;


maxpos = zeros(1, scans);
maxht = zeros(1, scans);
rng;


for k = 0.001:0.001:0.8
    sample_length = k;
    no_samples = floor(data_length / sample_length);
    no_filter = floor(filter_length / sample_length);
    raw_data = zeros(1, no_samples);
    pos = zeros(1, no_samples);
    ma_data = zeros(scans, no_samples);
    phi = rand(1, scans) * 2 * pi;
    
    for j = 1:scans
        % Create raw data
        for i = 1:no_samples
            pos(i) = -data_length / 2 + i * sample_length;
            raw_data(i) = cos(4 * pi * pos(i) / lambda + phi(j)) * exp(-0.5 * (pos(i) / HWHM)^2);
        end

        rect_data = abs(raw_data);

        for i = 1:n_ma
            t_data = movmean(rect_data, no_filter);
            rect_data = t_data;
        end

        ma_data(j, :) = rect_data;
        [maxht(1, j), p] = max(rect_data);
        maxpos(1, j) = pos(p);
    end

    meanht = mean(maxht);
    stdht = std(maxht);
    meanpos = mean(maxpos);
    stdpos = std(maxpos);

    fprintf('%f\t%f\t%f\t%f\t%f\n', sample_length, meanht, stdht, meanpos, stdpos);
end
%plot(pos, ma_data);
end
    


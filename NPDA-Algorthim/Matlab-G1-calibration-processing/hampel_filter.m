function [filt, outliers] = hampel_filter(t, num)

% Performs a Hampel filter of degree num on data in t

median_t = median(t);
madse_t = median(abs(t - median_t)) * 1.4826;
outliers = 0;
for i = 1: length(t)
    if (abs(t(i) - median_t) > num * madse_t)
        t(i) = median_t;
        outliers = outliers + 1;
    end
end
filt = t;
end
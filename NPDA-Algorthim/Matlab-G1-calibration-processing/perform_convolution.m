function [convolved_data, peak_data] = perform_convolution( conflcidata, Lorentzian )
%This function convolves the confocal and LCI scans with ideal Lorentzian
%peaks (different peaks for each). As such it forms a convolution filter.

min_diff_confocal = 2;
min_diff_LCI = 0.5;
convolved_data(:, 1) = conflcidata(:, 1);

for j = 2: 2:size(conflcidata, 2) - 1
    k = j + 1;
    % Confocal
    med = median(conflcidata(:, j));
    convolved_data(:, j) = conv(conflcidata(:, j) - med, Lorentzian(:, 2), 'same');
    
    % LCI
    med = median(conflcidata(:, k));
    convolved_data(:, k) = conv(conflcidata(:, k) - med, Lorentzian(:, 3), 'same');
    
    % Find the peak positions
    b = 1;
    for n = 1000:(size(conflcidata, 1) - 1000)
        if ((convolved_data(n, j) - convolved_data(n-500, j) > min_diff_confocal) && (b < 5))
            if (convolved_data(n-1, j) <= convolved_data(n, j)) && (convolved_data(n+1, j) < convolved_data(n, j))
                peak_data(b, j, 1) = convolved_data(n, 1);  % Peak position
                peak_data(b, j, 2) = convolved_data(n, j);  % Peak height
                b = b + 1;
            end
        end
    end 
    if b < 5
        for c = b:4
            peak_data(c, j, 1) = 0;
            peak_data(c, j, 2) = 0;
        end
    end
    b = 1;
    for n = 1000:(size(conflcidata, 1) - 1000)
        if ((convolved_data(n, k) - convolved_data(n-500, k) > min_diff_LCI) && (b < 5))
            if (convolved_data(n-1, k) <= convolved_data(n, k)) && (convolved_data(n+1, k) < convolved_data(n, k))
                peak_data(b, k, 1) = convolved_data(n, 1); % Peak position
                peak_data(b, k, 2) = convolved_data(n, k);  % Peak height
                b = b + 1;
            end
        end
    end 
    if b < 5
        for c = b:4
            peak_data(c, k, 1) = 0;
            peak_data(c, k, 2) = 0;
        end
    end
end

end


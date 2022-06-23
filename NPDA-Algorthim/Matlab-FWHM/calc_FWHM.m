function [fwhm, left_idx, right_idx] = calc_FWHM(scan, max_idx, half_max)

    % Check if scan saturates
    max_val = scan(max_idx);
    
    if max_idx-1 > 0
        if scan(max_idx-1) == max_val
            fwhm = 0;
            left_idx = 0;
            right_idx = 0;
            return;
        end
    end

    if max_idx+1 <= length(scan)
        if scan(max_idx+1) == max_val
            fwhm = 0;
            left_idx = 0;
            right_idx = 0;
            return;
        end
    end

    finished = false;
    idx = max_idx-1;
    while ~finished
        if idx < 1
            fwhm = 0;
            left_idx = 0;
            right_idx = 0;
            return;
        elseif scan(idx) < half_max
            finished = true;
            left_idx = idx;
        end
        idx = idx - 1;
    end
            
    finished = false;
    idx = max_idx+1;
    while ~finished
        if idx > length(scan)
            fwhm = 0;
            return;
        elseif scan(idx) < half_max
            finished = true;
            right_idx = idx;
        end
        idx = idx + 1;
    end
    fwhm = right_idx - left_idx;

end
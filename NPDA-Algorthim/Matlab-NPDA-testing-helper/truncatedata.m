function [valid_data, truncated_data, offsets, medians] = truncatedata(data, interrupt_lvl)

    SCAN_PF_WINDOW_MIN = 200;
    SCAN_FILTER_WINDOW = 1000;
    SCAN_LENGTH = 5000;
    SCAN_PF_WINDOW_MAX = SCAN_LENGTH - SCAN_FILTER_WINDOW + SCAN_PF_WINDOW_MIN;
    
    scan_length = size(data,1);
    
    valid_data = [];
    truncated_data = [];
    offsets = [];
    medians = [];
    
    valid_scan_counter = 1;

    for i = 1:size(data,2)
        
        scan_data = data(:,i);
        
        cmp_peak_positions_0 = 1;
        while( scan_data(cmp_peak_positions_0) < interrupt_lvl && cmp_peak_positions_0 < scan_length )
            cmp_peak_positions_0 = cmp_peak_positions_0 + 1;
        end
        
        if cmp_peak_positions_0 > 15 && cmp_peak_positions_0 <= 4985 %Ensure a noise spike at beginning/end of the scan was not detected
            if cmp_peak_positions_0 <  SCAN_PF_WINDOW_MIN + 1
                peak_finding_window_0 = 1;
                peak_finding_window_1 = SCAN_FILTER_WINDOW;
            elseif cmp_peak_positions_0 > SCAN_PF_WINDOW_MAX
                peak_finding_window_0 = SCAN_LENGTH - SCAN_FILTER_WINDOW + 1;
                peak_finding_window_1 = SCAN_LENGTH;
            else
                peak_finding_window_0 = cmp_peak_positions_0 - SCAN_PF_WINDOW_MIN + 1;
                peak_finding_window_1 = cmp_peak_positions_0 - SCAN_PF_WINDOW_MIN + SCAN_FILTER_WINDOW;
            end
            
            valid_data(:, valid_scan_counter) = data(:,i);
            truncated_data(:, valid_scan_counter) = data(peak_finding_window_0:peak_finding_window_1, i);
            offsets(valid_scan_counter) = peak_finding_window_0 - 1; %-1 corrects for C indexing
            %medians(valid_scan_counter) = median(data(peak_finding_window_0:peak_finding_window_1, i)); % Uncomment this line if using medians of restricted window scans
            %medians(valid_scan_counter) = median(data(:, i));
            sdata = sort(data(:, i));
            medians(valid_scan_counter) = sdata(2500);

            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            %SCAN_DC_AVERAGE = 64;
            %noise_threshold = 0;
            %noise_min = 65535;
            %noise_max = 0;

            %for i=peak_finding_window_0:(peak_finding_window_0+SCAN_DC_AVERAGE)
            %   if data(i) < noise_min 
            %       noise_min = data(i);
            %   end

            %   if data(i) > noise_max
            %       noise_max = data(i); 
            %   end
            %
            %   noise_threshold = noise_threshold + data(i);
            %end
            %    
            %noise_threshold = ( noise_threshold / SCAN_DC_AVERAGE );
            %medians(valid_scan_counter) = noise_threshold - ( (noise_max - noise_min) / 2 );
            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
            
            
            valid_scan_counter = valid_scan_counter + 1;
        end
    end
end
[file, path] = uigetfile('*.csv');
if file == 0
    fprintf('No file selected\n')
    return
end
fprintf('File opened: %s\n', file);

fpath = strcat(path, file);

data = dlmread(fpath);

[scan, ~, ~, ~] = validate_data(data);

%Count number of scans
scans_no = size(scan, 1);
scan_lth = size(scan, 2);

%Establish comarator settings
comparator_threshold_SFR = 13;
comparator_threshold = ((2^4)-comparator_threshold_SFR)/(2^4)*2^16;

%Allocate memory to variables
peak1_region = zeros(scans_no,scan_lth);

%Identify first peak region
for i=1:scans_no
    %Identify first peak region
    region_counter = 0;
    peak1_region_found = false;
    for j=1:scan_lth
        if peak1_region_found == true
            peak1_region(i,j) = 0;
        else
            if region_counter < 10
                peak1_region(i,j) = 0;
                if scan(i,j) > comparator_threshold
                    region_counter = region_counter + 1;
                else
                    region_counter = 0;
                end
            elseif region_counter == 10
                peak1_region(i,max(1,j-9):j) = ones(1,length(max(1,j-9):j));
                region_counter = region_counter + 1;
            else
                if scan(i,j) > comparator_threshold
                    peak1_region(i,j) = 1;
                else
                    peak1_region_found = true;
                end
            end
        end
    end

end

%Allocate memory to variables
max_val = zeros(scans_no,1);
max_idx = zeros(scans_no,1);
dc_offset = zeros(scans_no,1);
half_max = zeros(scans_no,1);
fwhm = zeros(scans_no,1);
left_idx = zeros(scans_no,1);
right_idx = zeros(scans_no,1);

for i=1:scans_no
    [max_val(i), max_idx(i)] = max(scan(i,:).*peak1_region(i,:));
    dc_offset(i) = median(scan(i,:));
    half_max(i) = dc_offset(i) + 0.5*(max_val(i) - dc_offset(i));
    if dc_offset(i) < 10 || dc_offset(i) > 6500
        fwhm(i) = 0;
        left_idx(i) = 0;
        right_idx(i) = 0;
    else
        [fwhm(i), left_idx(i), right_idx(i)] = calc_FWHM(scan(i,:), max_idx(i), half_max(i));
    end
end

mean_fwhm = mean(nonzeros(fwhm));
sd_fwhm = std(nonzeros(fwhm));
fprintf('+------------------------------------------------+\n');
fprintf('| Results                                        |\n');
fprintf('+------------------------------------------------+\n');
fprintf('| Total scans collected: %6d                  |\n', scans_no);
fprintf('| Good scans:            %6d                  |\n', length(nonzeros(fwhm)));
fprintf('| Mean FWHM:             %6.2f                  |\n', mean_fwhm);
fprintf('| SD FWHM:               %6.2f                  |\n', sd_fwhm);
fprintf('+------------------------------------------------+\n');

disp_idx = 0;
figure_handle = figure();
while 1
    if disp_idx == 0
        figure(figure_handle);
        clf;
        hold on;
        for i=1:scans_no
            plot(scan(i,:),'b-');
        end
        
        if length(nonzeros(fwhm)) == 0
            title(sprintf('No good scans.\n<- arrow to increment, -> arrow to decrement, space to finish.'))
        else
            plot([mean(max_idx(fwhm~=0)), mean(max_idx(fwhm~=0))], [0, 65536], 'k--');
            plot([mean(max_idx(fwhm~=0))-0.5*mean_fwhm, mean(max_idx(fwhm~=0))-0.5*mean_fwhm], [0, 65536], 'r--');
            plot([mean(max_idx(fwhm~=0))+0.5*mean_fwhm, mean(max_idx(fwhm~=0))+0.5*mean_fwhm], [0, 65536], 'r--');
            xlim([mean(max_idx(fwhm~=0))-5*mean_fwhm, mean(max_idx(fwhm~=0))+10*mean_fwhm])
            title(sprintf('All scans. Mean FWHM: %6.2f.\n<- arrow to increment, -> arrow to decrement, space to finish.', mean_fwhm))
        end
    else
        figure(figure_handle);
        clf;
        hold on;
        plot(scan(disp_idx,:),'b-');
        ylim([0, 65536]);
        
        if fwhm(disp_idx) == 0
            title(sprintf('Scan no.: %d. Bad scan.\n<- arrow to increment, -> arrow to decrement, space to finish.', disp_idx))
        else
            plot([max_idx(disp_idx), max_idx(disp_idx)], [0, 65536], 'k--');
            plot([left_idx(disp_idx), left_idx(disp_idx)], [0, 65536], 'r--');
            plot([right_idx(disp_idx), right_idx(disp_idx)], [0, 65536], 'r--');
            plot([0, 5000], [dc_offset(disp_idx), dc_offset(disp_idx)], 'r--');
            plot([left_idx(disp_idx), right_idx(disp_idx)], [half_max(disp_idx), half_max(disp_idx)], 'r--');
            plot(max_idx(disp_idx), max_val(disp_idx), 'rx');
            xlim([left_idx(disp_idx) - (max_idx(disp_idx)-left_idx(disp_idx))*10, right_idx(disp_idx) + (right_idx(disp_idx)-max_idx(disp_idx))*20]);
            title(sprintf('Scan no.: %d. FWHM: %6.2f.\n<- arrow to increment, -> arrow to decrement, space to finish.', disp_idx, fwhm(disp_idx)))
        end
    end

    [~, ~, button] = ginput(1);
    if button == 28 % <- arrow
        disp_idx = disp_idx - 1;
        if disp_idx < 0
            disp_idx = scans_no;
        end
    elseif button == 29 % -> arrow
        disp_idx = disp_idx + 1;
        if disp_idx > scans_no
            disp_idx = 0;
        end
    elseif button == 32 % spacebar
        return;
    end
end

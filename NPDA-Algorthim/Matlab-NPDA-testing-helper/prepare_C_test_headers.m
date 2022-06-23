function [error, retval] = prepare_C_test_headers( scan_path_in, scan_file_in, cal_path_in, cal_file_in, NPDA_alg_folder, ceedling_test_folder, block_cnt, scan_cnt )

    format long

    interrupt_threshold = 30000;

    %% Set up basics
    cal_file_path = strcat(cal_path_in, cal_file_in);
    scan_file_path = strcat(scan_path_in, scan_file_in);
    total_scan_count = block_cnt * scan_cnt;

    %% Read scan data
    scan_data  = csvread(scan_file_path);
    scan_pos = scan_data(:,1); %Position data
    scan_data = scan_data(:,2:end); %Scan data (get rid of the first column)
    scan_size = length(scan_pos);

    %% Truncate the data
    [valid_data, truncated_data, offsets, medians] = truncatedata(scan_data, interrupt_threshold);

    %% Save valid_data (untruncated) to file, which will then be processed by the NPDA algorithm
    if size(valid_data, 2) < total_scan_count
        disp('Insufficient valid data to run NPDA algorithm with given block_cnt and scan_cnt');
        error = 1;
        retval = {'', ''};
        return
    end
    data_to_save = zeros(size(valid_data,1), size(valid_data,2)+1);
    data_to_save(:,1) = scan_pos;
    data_to_save(:,2:(total_scan_count+1)) = valid_data(:,1:total_scan_count);
    current_folder = pwd;
    temp_data_csv_file = strcat(current_folder, '\temp_data.csv');
    csvwrite(temp_data_csv_file, data_to_save);

    %% Run NPDA algorithm on the cal and scan data
    current_folder = pwd;
    cd(NPDA_alg_folder)
    [~, ~, ~, ~, weightedMean, wmSDE, mean_wt, valid, ~] = main_convol_GK_cal_as_param2(temp_data_csv_file, cal_file_path, 0, 1, block_cnt, scan_cnt, scan_cnt, 0, 0, 1, 1, 1);
    cd(current_folder)
    corneal_thickness = weightedMean;
    corneal_thickness_accuracy = wmSDE;
    mean_weight = mean_wt;
    valid_blocks = valid;
    clear weightedMean wmSDE mean_wt valid

    %% Read cal data
    cal_data  = csvread(cal_file_path);
    cal_data = cal_data(:,2);

    %% Parse cal & data into a header file
    [~, scan_data_file_in_wo_extension, ~] = fileparts(scan_file_in);
    [~, cal_file_in_wo_extension, ~] = fileparts(cal_file_in);
    
    var_name = sprintf('%s_%s', scan_data_file_in_wo_extension, cal_file_in_wo_extension);
    var_name = regexprep(var_name, '-', '_');
    var_name = regexprep(var_name, '[^A-Za-z0-9_]', '');

    data_file_out = sprintf('test_m_npda_%s_%s.h', scan_data_file_in_wo_extension, cal_file_in_wo_extension);
    data_file_out_path = sprintf('%s\\%s', ceedling_test_folder, data_file_out);

    datatoheaderwmedian(truncated_data, offsets, medians, corneal_thickness, corneal_thickness_accuracy, mean_weight, valid_blocks, cal_data, var_name, data_file_out, data_file_out_path, scan_file_in, scan_size, total_scan_count, interrupt_threshold )

    %% Create test file
    %test_file_name = sprintf('test_m_npda_scan_data_%s_cal_%s.c', scan_data_file_in_wo_extension, cal_file_in_wo_extension);
    %test_file_name_path = sprintf('%s\\%s', ceedling_test_folder, test_file_name);

    %createtestfile( test_file_name, test_file_name_path, cal_file_out, data_file_out )

    %% Finish the function
    error = 0;
    retval = {data_file_out, var_name};
end
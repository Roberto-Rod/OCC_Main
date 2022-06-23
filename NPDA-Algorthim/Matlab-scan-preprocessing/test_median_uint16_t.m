clear all;
global S;

% %% The first test is to verify if the median_uint16_t implementation is returning desired values.
% success = 0;
% failure = 0;
% tic
% for i=1:10000
%     r = rand(5000,1);
%     r_sorted = sort(r);
%     med1_ll = r_sorted(2500);
%     med1_ul = r_sorted(2500);
%     S=1;
%     med2 = median_uint16_t(r,length(r));
%     if med2 <= med1_ul && med2 >= med1_ll
%         success = success + 1;
%     else
%         failure = failure + 1;
%     end
% end
% toc
% fprintf('Succeeded: %d, Failed: %d\n', success, failure);
% %% The second test is to evaluate performance of the function if we assume
% % step = 2
% success = 0;
% failure = 0;
% tic
% for i=1:10000
%     r = rand(5000,1);
%     r_sorted = sort(r);
%     med1_ll = r_sorted(2350);
%     med1_ul = r_sorted(2650);
%     S=2;
%     med2 = median_uint16_t(r,length(r));
%     if med2 <= med1_ul && med2 >= med1_ll
%         success = success + 1;
%     else
%         failure = failure + 1;
%     end
% end
% toc
% fprintf('Succeeded: %d, Failed: %d\n', success, failure);

%% The third test is to evaluate the effect of the new median calculation (i.e.
% with step = 2 on npda algorithm).
success = 0;
failure = 0;

fprintf('Note that sample scan data used for software testing is located here:\n')
fprintf('Occuity - Documents\\Projects\\P1 Pachymeter\\Software documentation\\Software Verification\\Sample test data\\P1 Handheld #001\n')

scan_files_path = uigetdir('./', 'Select location of scan data');
if scan_files_path == 0
    return
end

NPDA_alg_folder = uigetdir('./', 'Select location of the NPDA algorithm folder');
if NPDA_alg_folder == 0
    return
end

list_of_csv_files = dirrec(scan_files_path, '.csv');
list_of_scan_data_files =  list_of_csv_files(cellfun(@numel, regexp(list_of_csv_files, '[A-Z][A-Z]-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-Raw\.csv$'))==1);

scan_files_processed = 0;
for i = 1:length(list_of_scan_data_files)
    clear valid_data
    %% Prepare file name strings
    scan_data_file_with_path = char(list_of_scan_data_files(i));
    [scan_data_file_path, scan_data_file_wo_extension, scan_data_file_extension] = fileparts(scan_data_file_with_path);
    
    %% Read scan data
    block_cnt = 10;
    scan_cnt = 10;
    total_scan_count = block_cnt * scan_cnt;

    scan_data  = csvread(scan_data_file_with_path);
    scan_pos = scan_data(:,1); %Position data
    scan_data = scan_data(:,2:end); %Scan data (get rid of the first column)
    scan_size = length(scan_pos);

    %% Select only such data that has a peak
    idx = 1;
    for j=1:size(scan_data,2)
        [m,loc] = max(scan_data(:,j));
        if m > 30000 && loc > 15 && loc < 4000
            valid_data(:,idx) = scan_data(:,j);
            idx = idx + 1;
        end
    end
    
    %% Check if the file has got the right amount of data
    if size(valid_data, 2) < total_scan_count
        disp('Insufficient valid data to with given block_cnt and scan_cnt.')
        continue;
    end
    
    if scan_size ~= 5000
        disp('Scan data has wrong length.')
        continue;
    end

    %% Run npda on the data
    data_to_run_npda = zeros(5000, idx);
    data_to_run_npda(:,1) = scan_pos;
    data_to_run_npda(:,2:end) = valid_data;
    
    current_folder = pwd;
    cd(NPDA_alg_folder)
    S=1;
    [~, ~, ~, ~, weightedMean1, wmSDE1, ~] = main_convol_GK_cal2(data_to_run_npda, 0, 1, block_cnt, scan_cnt, scan_cnt, 0, 0, 1, 1, 0);
    S=2;
    [~, ~, ~, ~, weightedMean2, wmSDE2, ~] = main_convol_GK_cal2(data_to_run_npda, 0, 1, block_cnt, scan_cnt, scan_cnt, 0, 0, 1, 1, 0);
    cd(current_folder)

    fprintf('\nDifference: %f(mean)/%f(SD)\n', abs(weightedMean1-weightedMean2), abs(wmSDE1-wmSDE2));
    if abs(weightedMean1-weightedMean2) < 0.5 && abs(wmSDE1-wmSDE2) < 0.5
        success = success + 1;
    else
        failure = failure + 1;
    end
end
fprintf('Succeeded: %d, Failed: %d\n', success, failure);


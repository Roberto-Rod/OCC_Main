fprintf('Note that sample scan data used for software testing is located here:\n')
fprintf('Occuity - Documents\\Projects\\P1 Pachymeter\\Software documentation\\Software Verification\\Sample test data\\P1 Handheld #001\n')


scan_files_path = uigetdir('./', 'Select location of scan data');
if scan_files_path == 0
    return
end

list_of_csv_files = dirrec(scan_files_path, '.csv');
list_of_scan_data_files =  list_of_csv_files(cellfun(@numel, regexp(list_of_csv_files, '[A-Z][A-Z]-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-Raw\.csv$'))==1);

function_name = 'median_uint16_t';
function_file = 'npda_tools.c';

scan_files_processed = 0;
for i = 1:length(list_of_scan_data_files)
    %% Prepare file name strings
    scan_data_file_with_path = char(list_of_scan_data_files(i));
    [scan_data_file_path, scan_data_file_wo_extension, scan_data_file_extension] = fileparts(scan_data_file_with_path);
    
    output_file = sprintf('test_u_%s_%03d.c', function_name, scan_files_processed+1);
    output_file_loc = strcat('./', output_file);

    %% Read scan data
    
    block_cnt = 10;
    scan_cnt = 10;
    total_scan_count = block_cnt * scan_cnt;

    scan_data  = csvread(scan_data_file_with_path);
    scan_pos = scan_data(:,1); %Position data
    scan_data = scan_data(:,2:end); %Scan data (get rid of the first column)
    scan_size = length(scan_pos);

    %% Check if the file has got the right amount of data
    if size(scan_data, 2) < total_scan_count
        error('Insufficient valid data to with given block_cnt and scan_cnt.')
    end
    
    if scan_size ~= 5000
        error('Scan data has wrong length.')
    end

    %% Select from the file 5 sample scans (10th, 30th, 50th, 70th and 90th)
    sample_data(1,:) = scan_data(:, 10)';
    sample_data(2,:) = scan_data(:, 30)';
    sample_data(3,:) = scan_data(:, 50)';
    sample_data(4,:) = scan_data(:, 70)';
    sample_data(5,:) = scan_data(:, 90)';
    
    %% Run median_uint16_t on that data 
    global S;
    S = 2;
    result(1) = median_uint16_t(sample_data(1,:), length(sample_data(1,:)));
    result(2) = median_uint16_t(sample_data(2,:), length(sample_data(2,:)));
    result(3) = median_uint16_t(sample_data(3,:), length(sample_data(3,:)));
    result(4) = median_uint16_t(sample_data(4,:), length(sample_data(4,:)));
    result(5) = median_uint16_t(sample_data(5,:), length(sample_data(5,:)));
    
    %% Create a test file
    fileID = fopen(output_file_loc,'w');
    create_test_file_header(fileID, output_file, ...
        sprintf('Unit tests of %s in %s. Data from %s.', function_name, function_file, scan_data_file_wo_extension), ...
        {'npda.h', 'npda_tools.h'});
    create_test_file_setup(fileID);
    create_test_file_teardown(fileID);

    for j=1:length(result)
        fprintf(fileID,'/* ************************************************************************** */\n');
        fprintf(fileID,'/** \n');
        fprintf(fileID,' * @brief            Function tested: %s()\n', function_name);
        fprintf(fileID,' *\n');
        fprintf(fileID,' * @test             Runs %s fuction and measures execution time, max\n', function_name);
        fprintf(fileID,' *                   stack usage and returned value.\n');
        fprintf(fileID,' *\n');
        fprintf(fileID,' * @note             None\n');
        fprintf(fileID,' */\n');
        fprintf(fileID,'/* ************************************************************************** */\n');
        fprintf(fileID,'void test_%s_%03d_%03d(void)\n', function_name, scan_files_processed+1, j);
        fprintf(fileID,'{\n');
        fprintf(fileID,'    uint16_t iret;\n');
        fprintf(fileID,'    uint16_t data_in[] = {');
        for k=1:size(sample_data, 2)
            fprintf(fileID,'%d,', sample_data(j,k));
            if mod(k, 50) == 0
                fprintf(fileID,'\n');
                fprintf(fileID,'    ');
            end
        end
        fprintf(fileID,'    };\n');
        fprintf(fileID,'    unsigned int time;\n');
        fprintf(fileID,'    unsigned int stack_usage;\n');
        fprintf(fileID,'    \n');
        fprintf(fileID,'    unity_helper_tic();\n');
        fprintf(fileID,'    iret = %s(data_in, 5000);\n', function_name);
        fprintf(fileID,'    time = unity_helper_toc();\n');
        fprintf(fileID,'    stack_usage = unused_stack - stack_monitoring_measure_unused_stack();\n');
        fprintf(fileID,'    \n');
        fprintf(fileID,'    UnityPrint("TEST: test_%s_%03d_%03d(void): ");\n', function_name, scan_files_processed+1, j);
        fprintf(fileID,'    UnityPrint("Execution time: ");\n');
        fprintf(fileID,'    UnityPrintNumberUnsigned(time);\n');
        fprintf(fileID,'    UnityPrint("us. ");\n');
        fprintf(fileID,'    UnityPrint("Max stack usage: ");\n');
        fprintf(fileID,'    UnityPrintNumberUnsigned(stack_usage);\n');
        fprintf(fileID,'    UnityPrint("bytes.");\n');
        fprintf(fileID,'\n');
        fprintf(fileID,'    TEST_ASSERT_EQUAL_INT(%d, iret);\n', result(j));
        fprintf(fileID,'}\n');
        fprintf(fileID,'\n');
    end
    
    create_test_file_footer(fileID);
    fclose(fileID);
    
    scan_files_processed = scan_files_processed + 1;
    if scan_files_processed >= 5 %Finish script execution if 5 files are successfully processed
        return 
    end

end
fprintf('Test files prepared.\n')

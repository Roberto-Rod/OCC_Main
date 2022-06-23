%[cal_file, cal_file_path] = uigetfile('*.csv', 'Select cal data');
%if cal_file == 0
%    return
%end

%scan_files_path = uigetdir('./', 'Select location of scan data');
%if scan_files_path == 0
%    return
%end

%NPDA_path = uigetdir('./', 'Select location of the NPDA algorithm');
%if NPDA_path == 0
%    return
%end

%ceedling_test_path = uigetdir('./', 'Select location of the ceedling tests');
%if ceedling_test_path == 0
%    return
%end

cal_file = 'cal_01.csv';
cal_file_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\NPDA-Algorthim\Matlab-NPDA-testing-helper\data\';
scan_files_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\scan-data\P1 Handheld #001';
%scan_files_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\scan-data\P1 Data';
NPDA_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\NPDA-Algorthim\Matlab-main-algorithm';
ceedling_test_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\PDA-Module-dev\PDA-Module\firmware\test';

list_of_scan_data_files = dirrec(scan_files_path, '.csv');

list_of_filtered_scan_data_files =  list_of_scan_data_files(cellfun(@numel, regexp(list_of_scan_data_files, '[A-Z][A-Z]-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-[0-9]+-Raw\.csv$'))==1);

headers = {};

for i = 1:length(list_of_filtered_scan_data_files)
    scan_data_file_with_path = char(list_of_filtered_scan_data_files(i));
    [scan_data_file_path, scan_data_file_wo_extension, scan_data_file_extension] = fileparts(scan_data_file_with_path);
    scan_data_file_path = strcat(scan_data_file_path, '\');
    scan_data_file = strcat(scan_data_file_wo_extension, scan_data_file_extension);

    fprintf('%d/%d Preparing test file for %s\n', i, length(list_of_filtered_scan_data_files), scan_data_file); 
    [error, retval] = prepare_C_test_headers(scan_data_file_path, scan_data_file, cal_file_path, cal_file, NPDA_path, ceedling_test_path, 10, 10);
    fprintf('\n'); 
    if error == 0
        headers{end+1} = retval;
    end
end
prepare_C_test_files(headers, ceedling_test_path, 2);

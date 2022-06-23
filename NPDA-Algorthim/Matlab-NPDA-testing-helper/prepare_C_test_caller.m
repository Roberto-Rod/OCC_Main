%[cal_file, cal_file_path] = uigetfile('*.csv', 'Select cal data');
%if cal_file == 0
%    return
%end

%[scan_data_file, scan_data_file_path] = uigetfile('*.csv', 'Select scan data');
%if scan_data_file_path == 0
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
%scan_data_file = 'RT-2020-07-27-01-51-04-10-100-Raw.csv';
%scan_data_file_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\scan-data\P1 Data\';
%scan_data_file = 'DB-2020-09-09-03-40-14-15-300-Raw.csv';
%scan_data_file_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\scan-data\P1 Handheld #001\Eye Tests 090920\';
scan_data_file = 'LPJ-2020-11-04-06-09-05-10-100-Raw.csv';
scan_data_file_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\scan-data\P1 Handheld #001\Eye tests 041120\';

NPDA_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\NPDA-Algorthim\Matlab-main-algorithm';
ceedling_test_path = 'C:\Users\PiotrLaszczak\MPLABXProjects\PDA-Module-dev\PDA-Module\firmware\test';



[error, retval] = prepare_C_test_headers(scan_data_file_path, scan_data_file, cal_file_path, cal_file, NPDA_path, ceedling_test_path, 10, 10);
if error == 0
    header_name{1} = retval;
    prepare_C_test_files(header_name, ceedling_test_path, 5);
end
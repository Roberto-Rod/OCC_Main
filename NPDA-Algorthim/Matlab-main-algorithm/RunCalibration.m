clear all;close all; 

global reg_col_names;
global reg_col_Types ;
global reg_col_format;
global reg_file_path; 
global version;

reg_col_names = {'CalibrationID',    'DateCreated',  'Operator', 'DeviceID',     'DeviceName',   'DataLocation',    'Version'};
reg_col_Types = ['uint32',           'string',       'string',   'uint32',       'string',       'string',          'string'];
reg_col_format = '%u32%s%s%u32%s%s%s';
version = '1.02';
fprintf('Create Calibration lookup v%s\r\n', version);

h_fig = figure('Name','Calibration register info', 'Position', [400 400 300 300]);
set(h_fig,'KeyPressFcn',@create_reg_table);
uicontrol(h_fig,'Style','text',  'Position', [10 275, 280 15], 'String', 'Hit r to adjust calibration register location.')
uicontrol(h_fig,'Style','text',  'Position', [10 255, 280 15], 'String', 'Hit c to create a new calibration register.')

userProfile = getenv('USERPROFILE'); 
cal_conf_loc = [userProfile,'\','cal_conf.mat'];
fprintf('Config file loc: %s\r\n',cal_conf_loc); 

if(exist(cal_conf_loc, 'file'))
    
    load(cal_conf_loc, 'reg_file_path');
    info_str = ['Loaded Calibration register location: ',reg_file_path];
    
    uicontrol(h_fig,'Style','text',  'Position', [10 160, 280 80], 'String',  info_str);
    
    fprintf('%s \r\n',info_str ); 
else 
    fprintf('cal_conf.mat file not found\r\n');

    [fname, path] = uigetfile('*.csv','Select location of Calibration Register', 'calibration_register.csv');
    
    if isequal(fname,0) && isequal(path,0)
        fprintf('No file selected. Finishing now.\r\n');
        return;
    end
    
    reg_file_path = strcat(path, fname);

end 
pause(2); 

try
    [loadednames, cal_data] = read_cal_reg(reg_file_path, reg_col_format); 
    
    info_str = ['Checked at Calibration register location:',reg_file_path];
    uicontrol(h_fig,'Style','text',  'Position', [10 20, 280 80], 'String',  info_str); 
    fprintf('%s \r\n',info_str ); 
    same = 1; 
    for i = 1: min([length(loadednames), length(reg_col_names)])
        if(strcmp(loadednames{i}{1},reg_col_names{i})==0)
            same = 0; 
            break; 
        end 
    end 
    
    if(same ==0)
        fprintf('Error opening Calibration Register\r\n');
        return;
    end 
    save(cal_conf_loc, 'reg_file_path');
    
catch ME
    fprintf('Error opening Calibration Register %s\r\n', ME.message);
    return; 
end

pause(1);
close(h_fig); 

cal_path = uigetdir('title','Select location of Calibration Directory');

if isequal(cal_path ,0)
    fprintf('No dir selected. Finishing now.\r\n');
    return;
end

fprintf('Create Calibration lookup v%s\r\n', version);

h_pfig = figure('Name','Calibration process');
set(h_pfig,'KeyPressFcn',@create_reg_table);

figure_size = get(h_pfig, 'Position'); 
info_text_y_pos = figure_size(4) - 40; 
info_text_width = figure_size(3) - 20; 
uicontrol(h_pfig,'Style','text',  'Position', [10 info_text_y_pos, info_text_width 40], 'String', ['Processing: ',cal_path])

pause(0.5);
cal_LUT = (main_convol_calibrate3(cal_path, 1, 1, 100, 1, 1, 0, 0)); 

cal_warn = ' ';
cal_mean = mean(mean(cal_LUT)); 
if(cal_mean <2.45)||(cal_mean > 2.55) || (max(max(cal_LUT)) <5)
    cal_warn = 'Warning: Cal check failed: check calibration graphs'; 
    fprintf('%s\r\n', cal_warn);
end

global head_name;
global head_op_name;

head_cal_id = uint32(0); 
head_dev_id = uint32(0); 
head_name = 'Test2';
head_op_name = 'unknown';
head_DT = char(datestr(now, 'dd/MM/yyyy HH:mm:ss'));

global tbx_dev_name; 
global tbx_op_name;
global txt_valid; 
global inputs_valid ; 

global txt_op_name; 
global txt_dev_name; 

global save_file;

save_file =0; 

inputs_valid = 0; 

try 
    
    in_fig= figure('Name','Calibration info', 'Position', [400 400 300 300]); 
    
    row = 300; 
    row_h = 25;
    
    row = row - row_h; 
    status = sprintf('Calibration Look up created size %d by %d', size(cal_LUT,1), size(cal_LUT,2)); 
    uicontrol(in_fig,'Style','text',  'Position', [10 row, 290 20], 'String', status ); 
    
    row = row - row_h; 
    uicontrol(in_fig,'Style','text',  'Position', [10 row, 290 20], 'String', cal_warn); 
    
    row = row - row_h; 
    uicontrol(in_fig,'Style','text',  'Position', [10 row, 90 20], 'String', 'OCC-P1-GA-')
    
    tbx_dev_name = uicontrol(in_fig, 'Style','edit','Position', [100 row, 90 20]);
    txt_dev_name = uicontrol(in_fig,'Style','text',  'Position', [200 row, 90 20], 'String', '_'); 
    
    row = row - row_h; 
    uicontrol(in_fig,'Style','text',  'Position', [10 row, 90 20], 'String', 'Operator Name')
    tbx_op_name = uicontrol(in_fig, 'Style','edit','Position', [100 row, 70 20]);
    txt_op_name = uicontrol(in_fig,'Style','text',  'Position', [200 row, 90 20], 'String', '_'); 
    
    
    row = row - row_h; 
    txt_cal_id = uicontrol(in_fig,'Style','text',  'Position', [10 row, 290 20], 'String', 'Calibration ID:');
    
    row = row - (row_h*2); 
    
    uicontrol(in_fig,'Style','text',  'Position', [10 row, 290 50], 'String', ['Data Path: ',cal_path])

    row = row - row_h; 
    txt_valid = uicontrol(in_fig,'Style','text',  'Position', [10 row, 290 20], 'String', '_'); 
    
    row = row - row_h; 
    but_check = uicontrol(in_fig,'Style','pushbutton',  'Position', [10 row, 80 20], 'String', 'Check', 'Callback', @push_btn_check);
    
    but_save = uicontrol(in_fig,'Style','pushbutton',  'Position', [100 row, 80 20], 'String', 'Save', 'Callback', @push_btn_save);
   
    while (1)
        
        if ~ishandle(in_fig)
            break; 
        end
        
        if save_file ==1 
            
            [loadednames, cal_data] = read_cal_reg(reg_file_path, reg_col_format); 

            max_current_id = max(cell2mat(cal_data(:,1)));
            
            head_cal_id  = 0; 
            if(max_current_id < uint32(hex2dec('FFFFFFFF')))
               head_cal_id = max_current_id + 1; 
            end
            
            cal_header{1} = sprintf('Calibration ID: %u', head_cal_id);
            set(txt_cal_id, 'String', cal_header{1});
            cal_header{2} = sprintf('Device ID: %u', head_dev_id);
            cal_header{3} = sprintf('Name: %s', head_name);
            cal_header{4} = sprintf('Created: %s', head_DT);
            
            lookup_file = strcat(cal_path, '\Cal lookup.csv');
            
            fileID = fopen(lookup_file, 'w');
            
            for i=1:length(cal_header)
                fprintf(fileID, '%s', cal_header{i});
                if i ~= length(cal_header)
                    fprintf(fileID, ', ');
                else
                    fprintf(fileID, '\r\n');
                end
            end
            
            fclose(fileID);
            
            dlmwrite(lookup_file, cal_LUT, '-append');
            
            set(txt_valid, 'String', 'Cal lookup file saved.');
            
            new_entry(1,:)= {head_cal_id, head_DT, head_op_name, head_dev_id, head_name, cal_path, version};

            write_cal_reg(reg_file_path, reg_col_format, reg_col_names, new_entry, 'Append')  

            fprintf('Calibration file created and calibration register updated\r\n'); 
            
            set(txt_valid, 'String', 'Cal lookup file saved. Finished!');

            disp(new_entry);

            pause(5);
            
            close(in_fig); 
            
           break;  
        end
        
        pause(1);
        
    end 
    
catch ME
    
    fprintf('Calibration post processing exception: %s\r\n', ME.message);
    return; 
    
end

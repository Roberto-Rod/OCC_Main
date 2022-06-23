function create_reg_table(src, event)

    global reg_col_names;
    global reg_col_format;
    global version;
    global reg_file_path;
    if (event.Key == 'c')
        
        [fname, path] = uiputfile('*.csv','Select location of Calibration Register to Create', 'calibration_register.csv');
        if isequal(fname,0) && isequal(path,0)
            fprintf('No file selected. Finishing now.\n');
            return;
        end 
        reg_file_path = strcat(path, fname);
        d =char(datestr(now, 'dd/MM/yyyy HH:mm:ss')); 
        new_table(1,:)= {0,d,'Me',0,'Invalid for test', ':test dir\/,',version};

        try
           write_cal_reg(reg_file_path, reg_col_format, reg_col_names, new_table, 'Overwrite')  
           userProfile = getenv('USERPROFILE'); 
           cal_conf_loc = [userProfile,'\','cal_conf.mat'];
           save(cal_conf_loc, 'reg_file_path');
        catch ME
            fprintf('Failed to create a new Calibration Register.\n');
        end
        
    elseif (event.Key == 'r')
        [fname, path] = uigetfile('*.csv', 'Select location of Calibration Register', 'calibration_register.csv');
    
        if isequal(fname,0) && isequal(path,0)
            fprintf('No file selected. Finishing now.\r\n');
            return;
        end
        reg_file_path = strcat(path, fname);
    end 

end 
function push_btn_check(src, event)

    global tbx_dev_name;
    global tbx_op_name;
    global txt_valid; 
    
    global head_name;
    global head_op_name;
    
    global inputs_valid; 
    global txt_op_name; 
    global txt_dev_name;
    
    reg_exp_accepted = '\s?([A-Za-z0-9-]+)\s?'; 
    
    strs_input_name = get(tbx_dev_name,'String');
    strs_input_op = get(tbx_op_name,'String');
    
    strs_input_name(ismember(strs_input_name, ',|')) = '_';
    strs_input_op(ismember(strs_input_op, ',|')) = '_';
    
    str_name_valid = '';
    str_op_valid = ''; 
    
    [~, t] = regexp(strs_input_name,reg_exp_accepted, 'match', 'tokens' );
    if(length(t) > 0)
        str_name_valid = t{1}{1}; 
        if length(str_name_valid) > 16
            str_name_valid = str_name_valid(1:16);
        end
    end
    
    [~, t] = regexp(strs_input_op ,reg_exp_accepted,  'match', 'tokens' );
    if(length(t) > 0)
        str_op_valid  = t{1}{1};
        if length(str_op_valid) > 16
            str_op_valid = str_op_valid(1:16);
        end
    end 
    
    set(txt_op_name, 'String', str_op_valid);
    set(txt_dev_name, 'String', str_name_valid);
    
    if (strcmp(str_op_valid, '')) || (strcmp(str_name_valid, '')) 
        set(txt_valid, 'String', 'Some inputs are invalid');
        inputs_valid = 0; 
    else 
        
        set(txt_valid, 'String', 'Inputs checked as shown');
        inputs_valid = 1; 
        
        head_name = str_name_valid; 
        head_op_name = str_op_valid;
        
    end 

end
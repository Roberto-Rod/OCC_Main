function [] = prepare_C_test_files( list_of_headers, ceedling_test_folder, tests_per_file )

    format long

    i = 1;
    file_count = 1;
    
    
    header_file_names = {};
    var_names = {};
    
    while i <= length(list_of_headers)
        header_file_name = list_of_headers{i}{1};
        var_name = list_of_headers{i}{2};
        if any(strcmp(var_name, var_names)) || any(strcmp(header_file_name, header_file_names))
            printf('WARNING: Header %s already exists! Skipping this test...\n', header_file_name);
        else
            var_names{end+1} = var_name;
            header_file_names{end+1} = header_file_name;
        end
        if ~isempty(var_names)
            if (mod(i, tests_per_file) == 0 && i ~= 1) || i == length(list_of_headers)
                test_file_name = sprintf('test_m_npda_%03d.c', file_count);
                test_file_name_path = sprintf('%s\\%s', ceedling_test_folder, test_file_name);
                createtestfile( test_file_name, test_file_name_path, header_file_names, var_names );
                header_file_names = {};
                var_names = {};
                file_count = file_count + 1;
            end
        end
        i = i + 1;
    end
end
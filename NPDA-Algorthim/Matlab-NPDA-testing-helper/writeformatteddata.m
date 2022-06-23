function [] = writeformatteddata(file, data, data_len, data_in_one_row, float_or_int)

    end_of_loop = min([size(data,1), data_len]);

    i = 1;
    entry_i_val = i;
    while i <= end_of_loop
        no_comma = 1;
        if i ~= entry_i_val
            fprintf(file, ',\n                                ');
        end
        for j = 1:1:min([data_in_one_row, end_of_loop-i+1])
            if no_comma ~= 1
                fprintf(file, ', ');
            else
                no_comma = 0;
            end
            if strcmp(float_or_int, 'float')
                fprintf(file, '%.5f', data(i,1));
            elseif strcmp(float_or_int, 'int')
                fprintf(file, '%d', data(i,1));
            end
            i = i + 1;
        end
    end

    entry_i_val = i;
    if end_of_loop < data_len
        while i <= data_len
            if i ~= entry_i_val
                fprintf(file, ',\n                                ');
                no_comma = 1;
            else
                no_comma = 0;
            end
            for j = 1:1:min([data_in_one_row, data_len-i+1])
                if no_comma ~= 1
                    fprintf(file, ', ');
                else
                    no_comma = 0;
                end
                if strcmp(float_or_int, 'float')
                    fprintf(file, '0.00000');
                elseif strcmp(float_or_int, 'int')
                    fprintf(file, '0');
                end
                i = i + 1;
            end
        end
    end
end
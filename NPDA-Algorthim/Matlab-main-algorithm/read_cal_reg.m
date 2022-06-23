function [names, data] = read_cal_reg(filename, formatSpec)
%READ_CAL_REG This function attempts to access the calibration
%register and reads its first row (strings) as well as data formatted as
%per formatSpec
%   First parameter is the file name
%   Second parameter is the format of the file to read
   
   fileID = fopen(filename, 'r');
   if fileID == -1
      error('Unable to open the file.'); 
   end
      
   titleFormatSpec = '';
   for i=1:length(strfind(formatSpec,'%'))
       titleFormatSpec = sprintf('%s%%s',titleFormatSpec);
   end
    
   tline = fgetl(fileID);
   first_line = true;
   row_index = 1;
   while ischar(tline)
      if first_line
         first_line = false;
         names = textscan(tline,titleFormatSpec,'Delimiter','|');
         for i=1:length(names)
             if iscell(names{i})
                 if ischar(names{i}{1})
                    names{i}{1} = strtrim(names{i}{1});
                 end
             end
         end
         tline = fgetl(fileID);
         continue
      end
       
      data(row_index,:) = textscan(tline,formatSpec,'Delimiter','|');
      for i=1:length(data(row_index,:))
         if iscell(data{row_index, i})
            if ischar(data{row_index, i}{1})
               data{row_index, i}{1} = strtrim(data{row_index, i}{1});
            end
         end
      end
      row_index = row_index + 1;
      tline = fgetl(fileID);
   end
   fclose(fileID);
end


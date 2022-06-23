function [] = write_cal_reg(filename, formatSpec, names, data, mode)
%WRITW_CAL_REG This function attempts to access the calibration
%register and saves to it. If mode = 'Overwrite' is set, then a brand new
%file is created with names column and data. If mode = 'Append' then only
%data is appended at the end of the file.
%   First parameter is the file name
%   Second parameter is the format of the file to write
%   Third parameter is column titles
%   Fourth parameter is data to write
%   Fifth parameter is mode
   if ~strcmp(mode, 'Overwrite') && ~strcmp(mode, 'Append')
      error('Unknown mode selected.'); 
   end
       
   if strcmp(mode,'Overwrite')
       fileID = fopen(filename, 'w');
   else
       fileID = fopen(filename, 'a');
   end
   
   if fileID == -1
      error('Unable to open the file.'); 
   end
      
   titleFormatSpec = '';
   for i=1:length(strfind(formatSpec,'%'))
       titleFormatSpec = sprintf('%s%%s',titleFormatSpec);
   end
   
   if strcmp(mode,'Overwrite')
       for i=1:length(names)
           fprintf(fileID, '%s', names{i});
           if i ~= length(names)
               fprintf(fileID, ' | ');
           end
       end
       fprintf(fileID, '\r\n');
   end
   
   formatSpec = regexprep(formatSpec, '(.)%', '$1|%');
   formatSpec = regexprep(formatSpec, 'u32', 'u');
   
   for i=1:size(data,1)
      fprintf(fileID, formatSpec, data{i,:});
      fprintf(fileID, '\r\n');
   end
   
   fclose(fileID);
end


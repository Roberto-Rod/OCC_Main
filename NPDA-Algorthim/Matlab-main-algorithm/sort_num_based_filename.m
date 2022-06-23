function [sorted_data_filename varargout]  = sort_num_based_filename(data_filename, separating_char)

indicator_num = zeros(size(data_filename));
for i = 1 : length(data_filename)
    scp = find(data_filename(i).name == separating_char); % separating character position
    if ~isempty(find(data_filename(i).name=='-'))
        dum = find(data_filename(i).name=='-');
        data_filename(i).name(dum)='.';
        indicator_num(i) = str2double(data_filename(i).name(1:scp-1));
        data_filename(i).name(dum)='-';
    else
        indicator_num(i) = str2double(data_filename(i).name(1:scp-1));
    end
end

[sorted_indicator_num, ind] = sort(indicator_num);

for i = 1 : length(data_filename)
    sorted_data_filename(i,1) = data_filename(ind(i));
end

if nargout == 2
    varargout{1}= sorted_indicator_num;
end
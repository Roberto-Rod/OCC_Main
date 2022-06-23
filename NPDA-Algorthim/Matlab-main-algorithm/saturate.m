function [data, used] = saturate( data, s_level )
% Puts an arbitrary saturation level on the input data.

% Used to est whether saturation has an effect on the determined AC
% position

used = 0;
for i = 1:size(data, 1)
    for j = 1:size(data, 2)
        if data(i, j) > s_level
            data(i, j) = s_level;
            used = 1;
        end
    end
end

end


function [pks,locs,w] = processPeaks( data, mph, mpd )

if( mph == 0 )
    [pks,locs]=findpeaks(data); % Matlab 2013b
elseif( mpd == 0 )
    [pks,locs]=findpeaks(data,'MinPeakHeight',mph,'SortStr','descend'); % Matlab 2013b
else
    [pks,locs]=findpeaks(data,'MinPeakHeight',mph,'MinPeakDistance',mpd,'SortStr','descend'); % Matlab 2013b
end

[pks,locs,w] = findPeakFWHM(data, pks,locs);
,
%--------------------------------------------------------------------------
function [pks,locs,w] = findPeakFWHM(X,pks,locs)

w = zeros(length(pks));

if( ( isempty(locs) == 0 ) && ( locs(1) > 0 ) )
    
    med_val = median(X); % Median of the data, i.e. zero level
    
    for j = 1:length(pks)

        max_val = pks(j);      % Maximum of the data    
        half_height = (max_val + med_val) / 2;
        disp(max_val);
        disp(med_val);
        disp(half_height);
        disp(X(locs(j)));
        
        if( locs(j) > 0 )
            
            i = locs(j);
            while( ( i > 0 ) && ( X(i) > half_height ) )
              i = i - 1;
            end

            f1 = locs(j) - i;

            i = locs(j);
            while( ( i < length(X) ) && ( X(i) > half_height ) )
              i = i + 1;
            end

            f2 = i - locs(j);

            w(j) = f2 + f1;
        else
            w(j) = 0;
        end
        disp(w(j));

        
    end
    
end
% [EOF]

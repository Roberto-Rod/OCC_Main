function [pks,locs,w,pk_height] = processPeaks( data, mph, mpd )

%if( mph == 0 )
%    [pks,locs]=findpeaks(data); % Matlab 2013b
%elseif( mpd == 0 )
%    [pks,locs]=findpeaks(data,'MinPeakHeight',mph,'SortStr','descend'); % Matlab 2013b
%%else
%    [pks,locs]=findpeaks(data,'MinPeakHeight',mph,'MinPeakDistance',mpd,'SortStr','descend'); % Matlab 2013b
%end

[pks, locs] = peakfinder(data, mph);
[pks,locs,w, pk_height] = findPeakFWHM(data, pks,locs);



%--------------------------------------------------------------------------
function [pks,locs,w, pk_height] = findPeakFWHM(X,pks,locs)

w = zeros(length(pks));
pk_height = w;

if( ( isempty(locs) == 0 ) && ( locs(1) > 0 ) )
    
    
    for j = 1:length(pks)

        max_val = pks(j);      % Maximum of the data    

        if( locs(j) > 0 )
            
            % Find half height of peak
            top = locs(j);
            i = 1;
            while ((top - i > 1) && (X(top - i) < X (top - i + 1)) && (top + i < length(X) - 1) && (X(top + i) < X(top + i - 1)))
                i = i + 1;
            end
         
            if (X(top - i) < X(top + i))
                min_height = X(top + i);
            else
                min_height = X(top - i);
            end
            
            half_height = (max_val + min_height) / 2;
            pk_height(j) = max_val - min_height;
            
            % Find FWHM of peak    
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
     

        
    end
    
end

%--------------------------------------------------------------------------

function [pks, locs] = peakfinder(data, mph)
% Function for finding all the peaks in a set of data above a minimum peak
% height.

j = 1;
for i = 2:length(data) - 1
    if (data(i) > data(i - 1)) && (data(i) > data(i + 1)) && (data(i) > mph)
        pks(j) = data(i);
        locs(j) = i;
        j = j + 1;
    end
end
if j == 1
    pks = [];
    locs = [];
end



% [EOF]

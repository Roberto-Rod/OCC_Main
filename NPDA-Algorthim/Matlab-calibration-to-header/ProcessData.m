function [peaks_out, data_out] = ProcessData( pos, data_in, pthresh, hthresh )
%
%
%
%
%

%hold off;
figure(1)

data = MAF( data_in, 16 );
data = MAF( data, 16 );
data = data * (3.3/65535);

data_out = [];
peaks_out = [];
scan = zeros( 1, 1000 );
pindex = 0;

Peaks = zeros( size(data,2), 12 );

for( j = 1:size(data,2) )
    
    a = peakfinding( data(:,j), 2, pthresh, hthresh );
    Peaks( j,1:6 ) = a(1,:);
    Peaks( j,7:12 ) = a(2,:);
    plot( pos, data( :,j ) );
    hold on;
    
    if( a(1,1) > 4000 )  
        scan = data_in( 4001:5000,j);  
        pindex = 4000;
    elseif( a(1,1) > 200 )  
        scan = data_in( a(1,1)-199:a(1,1)+800,j);
        pindex = a(1,1)-200;
    else
        scan = data_in( 1:1000,j);  
        pindex = 0;
    end
    
    data_out = [ data_out, scan ];
    peaks_out = [ peaks_out, pindex ];
    
    if( Peaks(j,1) > 0 )
        plot( pos(Peaks(j,1)),data(Peaks(j,1),j),'Marker','x','MarkerEdgeColor','r' )
        plot( pos(Peaks(j,2)),data(Peaks(j,2),j),'Marker','x','MarkerEdgeColor','g' )
        plot( pos(Peaks(j,3)),data(Peaks(j,3),j),'Marker','x','MarkerEdgeColor','g' )        
    end
    
    if( Peaks(j,7) > 0 )    
        plot( pos(Peaks(j,7)),data(Peaks(j,7),j),'Marker','x','MarkerEdgeColor','r' )
        
        if( Peaks(j,8) > 0 )
            plot( pos(Peaks(j,8)),data(Peaks(j,8),j),'Marker','x','MarkerEdgeColor','g' )
        end
        
        if( Peaks(j,9) > 0 )
            plot( pos(Peaks(j,9)),data(Peaks(j,9),j),'Marker','x','MarkerEdgeColor','g' )            
        end
    end
    
%    hold off;    
%    input('Press any key.');
end

hold off;  
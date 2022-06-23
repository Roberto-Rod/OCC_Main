function maxpos=findAC_quad(pos, dataf, resolution)
% Description: Find the position of the AC peak and fit a curve
%
% Author: Raquel Gonzalez
% Last update: 15/09/17
%
% Inputs:
%           pos: Array of positions
%           dataf: Data corresponding to a single scan
% Output: 
%           ACpos: Position for the AC peak


% AC PEAK QUADRATIC FITTING
% Choose points between 50% and 80% of the amplitude of the AC peak
maxval = max(dataf);
%mina = 0.5*max(dataf);
%maxa = 0.8*max(dataf);
mina = 0.5*max(dataf);
maxa = 0.95*max(dataf);
points=find(dataf>=mina & dataf<=maxa); 
r1AC=pos(points);
testvar = dataf(points);
if (length(r1AC) > 2)
    p = polyfit(r1AC,dataf(points),2);      % Get coefficients
    %fprintf('p = %f\t%f\t%f\n', p(1),p(2), p(3));
    % We evaluate the polynomial with greater resolution to have a better
    % fitting. However, notice that the respective amplitudes would change.
    r2AC=pos(points(1)):resolution:pos(points(end));   
    yAC = polyval(p,r2AC);   

    ACpos=r2AC(yAC==max(yAC)); % Find the maximum of the parabola
    maxpos = ACpos(1);          % Truncate in case two points equal height
    %fprintf('%f\t%f\t%f\n', maxpos,r1AC(1), r1AC(end));
else
    maxpos = 1;
end
% figure
% plot(pos,dataf)      % Plot the data
% hold on
% plot(r2AC,yAC)       % Plot fitted curve for AC
% plot(ACpos+0*(0:yAC(idxAC)),0:yAC(idxAC),'k--')   % Plot position of AC
end
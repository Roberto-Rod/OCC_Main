function ACpos=jr_findAC_quad(pos,dataf)
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
points=find(dataf>=0.5*max(dataf) & dataf<=0.8*max(dataf)); 
r1AC=pos(points)';
disp(size(r1AC));
disp(size(dataf));
p=polyfit(r1AC,dataf(points),2);      % Get coefficients

% We evaluate the polynomial with greater resolution to have a better
% fitting. However, notice that the respective amplitudes would change.
r2AC=pos(points(1)):0.001:pos(points(end));   
yAC = polyval(p,r2AC);   

ACpos=r2AC(yAC==max(yAC)); % Find the maximum of the parabola


% figure
% plot(pos,dataf)      % Plot the data
% hold on
% plot(r2AC,yAC)       % Plot fitted curve for AC
% plot(ACpos+0*(0:yAC(idxAC)),0:yAC(idxAC),'k--')   % Plot position of AC
end
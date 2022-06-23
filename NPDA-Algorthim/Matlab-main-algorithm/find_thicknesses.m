function [valid, mean_t, sd_t, median_t, madse_t, mean_w, sd_w, mean_wt, sd_wt] = find_thicknesses(ACheight, ACpos, PCpos, weight, nc, exp, hampel, plotFigures)

ACmax = max(ACheight);     % Largest AC peak
thick=abs(ACpos-PCpos)*nc;   % Thickness
thick(PCpos==0)=0;
thick(ACheight < 0.2 * ACmax) = 0; % Reject blocks where the AC peak is suppressed
if exp == 1
    thick(ACht < 16000) = 0;            % Experimental AC height criterion
end

weight(thick == 0) = 0;
thick(weight == 0) = 0;
thick1=nonzeros(thick);     % We only choose the values different than zero since they have produced a value for PC
weight1 = nonzeros(weight);

%disp(ACheight);

valid=size(thick1,1);       % Number of valid scans

median_t = median(thick1);
madse_t = median(abs(thick1 - median_t)) * 1.4826;

outliers = 0;
if (hampel == 1)
    for i = 1: length(thick1)
        if (abs(thick1(i) - median_t) > 1.5 * madse_t)
            if plotFigures == 1
                fprintf('Filtered data: %.4f\n', thick1(i));
            end
            thick1(i) = median_t;
            weight1(i) = 0;
            outliers = outliers + 1;
        end
    end
end


mean_t=mean(thick1);
sd_t = std(thick1);

thick_w = thick1.* weight1;
mean_w=sum(thick_w) / sum(weight1);   % Weighted mean 

sd_w = sqrt(sum(weight1 .* (thick1 - mean_w).^2) / sum(weight1));
med_w= weightedMedian(thick,weight);  % Weighted median 

mean_wt = mean(nonzeros(weight1));
sd_wt = std(nonzeros(weight1));

end
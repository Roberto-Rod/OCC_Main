clear
[file, path] = uigetfile('*.csv');
if file == 0
    fprintf('No file selected\n')
    return
end
fprintf('File opened: %s\n', file);



fpath = strcat(path, file);
data = dlmread(fpath);
scanRange=length(data);


i=1;
n=1;
for i=1:scanRange
    if data(i,14)>0
        weights(n)=data(i,14);
        thicknesses(n)=data(i,12);
        n=n+1;
    
    end
end


Thickness_meanw=((sum(thicknesses.*weights)/sum(weights))*1000)
Thickness_sdw=(std(thicknesses,weights)*1000)

median_t = median(thicknesses);
madse_t = median(abs(thicknesses - median_t)) ;
weight1 = nonzeros(weights);

outliers = 0;

    for i = 1: length(thicknesses)
        if (abs(thicknesses(i) - median_t) > 1.5 * madse_t)
            
            thicknesses(i) = median_t;
            weight1(i) = 0;
            outliers = outliers + 1;
        end
    end
    
    mean_t=mean(thicknesses);
sd_t = std(thicknesses);

thick_w = thicknesses.* weight1';
mean_w=sum(thick_w) / sum(weight1);  % Weighted mean 

sd_w = (sqrt(sum(weight1' .* (thicknesses - mean_w).^2) / sum(weight1)))*1000
mean_w=mean_w*1000



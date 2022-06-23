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

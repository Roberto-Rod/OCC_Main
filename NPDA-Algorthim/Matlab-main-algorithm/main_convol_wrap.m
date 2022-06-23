function  main_convol_wrap( filename )
% This is a wrapper for main_convol_test, in order to test out the effect
% of different block lengths for averaging. It is currently unclear which
% length is optimum, or even if the optimum length is data dependent.

% Input: Name of the data file.

n = [5, 6, 10, 12, 15, 20, 25, 30, 50];
m = floor(300 ./ n);

for i = 1:9
    [mean_w, sd_w, pp, qq] = main_convol_test(filename, 1, 1, n(i), m(i), 1);
    fprintf('%i %i: %3.2f%% good blocks; %3.2f%% outliers, Weighted mean %3.1f +/- %3.1f um\n', n(i), m(i), pp, qq, mean_w * 1000, sd_w * 1000);
end

end


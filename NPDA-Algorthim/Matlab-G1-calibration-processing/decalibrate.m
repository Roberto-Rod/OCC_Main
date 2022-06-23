function decalibrate(total)

% This function gets rid of the calibration applied by calibration coefficients

filepath = 'C:\Users\james\OneDrive\Documents\Occuity\LCI\Confocal branch\Calibration 1\';
f_lookup = strcat(filepath, 'Pre-cal lookup.csv');
m_lookup = csvread(f_lookup, 1, 0);

n_conf = zeros(30, 1);  % Initialise array

for i = 1:total
    fprintf('%i\n', i);
    s_conf = strcat(filepath, 'c', num2str(i), '-DataSummary.csv');
    m_conf = csvread(s_conf, 1, 10, [1 10 30 10]);
    
    for j = 1:30
        t = m_conf(j);
        k = 1;
        while (t > m_lookup(k, 2))
            k = k + 1;
        end
        n_conf(j) = k;
    end
    
    s_out = strcat(filepath, 'd', num2str(i), '-DataSummary.csv');
    csvwrite(s_out, n_conf);
    
end



end
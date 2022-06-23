function lookup_calibrate(total)

% This function creates a ookup table using the results (in mm) obtained 
% from the LCI arm as a basis for calibrating the confocal arm.
% The program takes measurements in mm from the LCI arm and measurements
% in encoder counts from the confocal arm and relateds the two to one
% another, then uses cubic spline interpolation to create a lookup table
% from this data.

% Note that, due to an error, the results from the confocal arm were taken 
% with the previous quadratic compensation applied. As a consequence the
% program decalibrate.m has been written to convert the P1 peak positions back
% into encoder counts and save the results in a set of files. This program 
% works on the basis of these sets of encoder count files (prefix d). Note
% that these files include only the encoder count positions for P1.

filepath = 'C:\Users\james\OneDrive\Documents\Occuity\LCI\Confocal branch\Calibration 2\';
f_lookup = strcat(filepath, 'Calibration lookup 2.csv');

means = zeros(total, 2);  % Initialise array

l_table = zeros(5000, 2);

for i = 1:total
   
    % Get data from the two channels
    lci_channel = strcat(filepath, 'i', num2str(i), '-DataSummary.csv');
    conf_channel = strcat(filepath, 'c', num2str(i), '-DataSummary.csv');
    lci_data = csvread(lci_channel, 2, 10, [2 10 30 10]);
    conf_data = csvread(conf_channel, 2, 10, [2 10 30 10]);
    
    % Calculate the mean peak positions (and get visual check of any
    % irregularities)
    means(i, 1) = mean(lci_data);
    means(i, 2) = mean(conf_data);
    a = std(lci_data);
    b = std(conf_data);
    fprintf('%i\t%f\t%f\t%f\t%f\n', i, means(i, 2), means(i, 1), b, a);
    
end

plot(means(:, 2), means(:, 1));
% Calculate the lookup table by cubic spline
encoder = 0.001:0.001:5;
conf_pos = spline(means(:, 2), means(:, 1), encoder);
l_table(:, 1) = encoder;
l_table(:, 2) = 6 - conf_pos;
csvwrite(f_lookup, l_table);
    
    
     
end

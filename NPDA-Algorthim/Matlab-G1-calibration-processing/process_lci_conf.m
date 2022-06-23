function process_lci_conf(filepath, lci, mag, look, total)

% This function combines and processes data from the confocal and LCI arms
% of the combined system.

f_lci = strcat(filepath, '\', lci);
f_mag = strcat(filepath, '\', mag);
f_look = strcat(filepath, '\', look);

results = zeros(total, 9);  % Initialise array

for i = 1:total
    fprintf('%i\n', i);
    s_lci = strcat(f_lci, num2str(i), '-DataSummary.csv');
    s_mag = strcat(f_mag, num2str(i), '-DataSummary.csv');
    s_look = strncat(f_look, num2str(i), '-DataSummary.csv');
    
    % Get the separation data
    m_lci = csvread(s_lci, 2, 19);
    m_conf = csvread(s_conf, 2, 19);
    
    results(i, 1) = i;              % Set no.
    results(i, 2) = mean(m_lci);    % LCI mean
    results(i, 3) = std(m_lci, 1);  % LCI SD
    results(i, 4) = mean(m_conf);   % Confocal mean
    results(i, 5) = std(m_conf, 1); % Confocal SD
    
    % Calculate thickness and refractive index
    thickness = sqrt(m_lci .* m_conf);
    ri = sqrt(m_lci ./ m_conf);
    
    results(i, 6) = mean(thickness);    % Mean thickness
    results(i, 7) = std(thickness, 1);  % SD thickness
    results(i, 8) = mean(ri);           % Mean refractive index
    results(i, 9) = std(ri);            % SD refractive index
    
end

outfile = strcat(filepath, '\', lci, conf, '-summary.csv');
csvwrite(outfile, results);

end
    
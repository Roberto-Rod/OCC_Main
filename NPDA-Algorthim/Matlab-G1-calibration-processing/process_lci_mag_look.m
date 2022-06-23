function process_lci_mag_look(filepath, lci, mag, look, total)

% This function combines and processes data from the confocal and LCI arms
% of the combined system.

f_lci = strcat(filepath, '\', lci);
f_mag = strcat(filepath, '\', mag);
f_look = strcat(filepath, '\', look);

results = zeros(total, 7);  % Initialise array

for i = 1:total
    fprintf('%i\n', i);
    %s_lci = strcat(f_lci, num2str(i), '-DataSummary.csv');
    s_mag = strcat(f_mag, num2str(i), '-DataSummary.csv');
    s_look = strcat(f_look, num2str(i), '-DataSummary.csv');
    
    % Get the separation data
    col = 9;
    %m_lci = csvread(s_lci, 2, col, [2 col 30 col]);
    m_mag = csvread(s_mag, 2, col, [2 col 30 col]);
    m_look = csvread(s_look, 2, col, [2 col 30 col]);
    %m_lci = hampel(m_lci);
    m_mag = hampel(m_mag);
    m_look = hampel(m_look);
    
    results(i, 1) = i;              % Set no.
    %results(i, 2) = mean(m_lci);    % LCI mean
    %results(i, 3) = std(m_lci, 1);  % LCI SD
    results(i, 4) = mean(m_mag);   % Confocal mean with mag
    results(i, 5) = std(m_mag, 1); % Confocal SD with mag
    
    % Calculate thickness and refractive index
    %thickness = sqrt(m_lci .* m_conf);
    %ri = sqrt(m_lci ./ m_conf);
    
    results(i, 6) = mean(m_look);    % Confocal mean with lookup
    results(i, 7) = std(m_look, 1);  % Confocal SD with lookup
    
    
end

outfile = strcat(filepath, '\', lci, mag, look, '-summary.csv');
csvwrite(outfile, results);

end

function a = hampel(b)

    m = median(b);
    q = abs(b - m);
    mad = median(q);
    
    for j = 1:length(b)
        if (q(j) > 3.7 * mad)
            a(j) = m;
        else
            a(j) = b(j);
        end
    end
end
    
    

    
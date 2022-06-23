function simulated_data_generator(a, step)

filepath = 'X:\LeinCompanyData\Personal Folders\GKitteridge\AutomaticCalibartion\002-CalibrationData\Simulation';
for i = step:step:4999
    simfile = zeros(5000, 2);
    n = num2str(i, '%04i');
    q = i/1000;
    fwhm1 = -1.43 * q * q + 9.57 * q +42.9;
    q = q + 0.723;
    fwhm2 = -1.43 * q * q + 9.57 * q +42.9;
    maxpos = 1;
    maxvalue = 0;
    fwhm1 = 50;
    
    gamma01 = fwhm1 / 2;
    gamma02 = fwhm2 / 2;
    gamma_left1 = 2 * gamma01 / (1 + exp(-a * gamma01));
    gamma_right1 = 2 * gamma01 / (1 + exp(a * gamma01));
    gamma_sf1 = fwhm1 / (gamma_left1 + gamma_right1);
    
        filename = strcat(n(1), '-', n(2:4), 'mm-Raw.csv');
    for j = 1:5000
        simfile(j, 1) = (j - 1) / 1000;
        x = (-4.067e-8 * j^2 + 1.191e-3 * j) * 1000;
        x = j;
        gamma1 = 2 * gamma01 / (1 + exp(a * (x - i)));
        gamma2 = 2 * gamma02 / (1 + exp(a * (x - i - 500)));
        %simfile(j, 2) = gamma1 / ((x - i)^2 + gamma1 * gamma1) + gamma2 / ((x - i - 500)^2 + gamma2 * gamma2);
        simfile(j, 2) = gamma1^1.67 / ((x - i)^2 + gamma1^2);
        if simfile(j, 2) > simfile(maxpos, 2)
            maxpos = j;
            maxvalue = simfile(j, 2);
        end    
    end
    
    % Find FWHM points of front peak
    j = 1;
    halfvalue = maxvalue / 2;
    while simfile(j, 2) <= halfvalue
        j = j + 1;
        if j > 5000
            break
        end
    end
    
    LHS = j - 1;
    j = maxpos;
    while simfile(j, 2) >= halfvalue
        j = j + 1;
        if j > 5000
            break
        end
    end
    
    RHS = j - 1;
    fwhm_meas = RHS - LHS;
    asym = (RHS + LHS - 2 * maxpos) / fwhm_meas;
    
    %outfile = strcat(filepath, '\', filename);
    %dlmwrite(outfile, simfile);
    fprintf('%f\t%f\n', gamma_left1, gamma_right1);
    fprintf('%i\t%i\t%i\n', LHS, maxpos, RHS);
    fprintf('%i\t%f\t%i\t%f\n', i, fwhm1, fwhm_meas, asym);
end
end

    
    
    
    

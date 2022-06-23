function scans_out = reconstruct_saturation(scans_in)
%reconstruct_saturation.m Reconstructs peak in saturated data
%   This file reconstructs the AC peak in the data that shows saturation.
% Inputs:
%   scans_in    : an n by 5000 matrix of n scans
% Outputs:
%   scans_out   : an n by 5000 matrix of n scans with reconstructed saturated peaks

  scans_out = zeros(size(scans_in));

  for i=1:size(scans_in, 1)
    scan = scans_in(i,:);
    reconstruction_flag = 0;
    for j=1:size(scans_in, 2)
      if scan(j) ~= 65535
        reconstruction_flag = 0;
        scans_out(i, j) = scan(j);
      else
        if reconstruction_flag == 0
          k = j + 1;
          while scan(k) == 65535
            k = k + 1;
          end
          peak_width = k - j;
          if peak_width == 1
            scans_out(i, j) = scan(j);
          else
            estimated_peak_height = 65535 + 20.27 * peak_width^2 - 41.014 * peak_width;
            pl = (k + j) / 2; % peak location
            coeffs = polyfit([j, pl, k], [65535, estimated_peak_height, 65535], 2);
            scans_out(i, j) = scan(j);
            reconstruction_flag = 1;
          end
        else
          scans_out(i, j) = coeffs(1)*j^2 + coeffs(2)*j + coeffs(3);
        end
      end
    end
  end
end
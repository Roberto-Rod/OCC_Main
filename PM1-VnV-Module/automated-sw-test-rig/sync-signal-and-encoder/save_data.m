function [] = save_data(path, A, B, Z, S, D, F)
%save_data.m Saves encoder data into a .csv file that can be interpreted by
%the automated software test rig
%   This file saves encoder and analogue signal data to a .csv file. The
%   output file format contains: first line specifies the data rate, second
%   line describes each column of data and any consecutive line contains
%   comma-separated data.
% Inputs:
%   A    : a vector representing channel A encoder signals (either 1 or 0)
%   B    : a vector representing channel B encoder signals (either 1 or 0)
%   Z    : a vector representing Z pole encoder signals (either 1 or 0)
%   S    : a vector representing analogue signals (in Volts)
%   D    : a vector representing divisions of the file into smaller chunks (either 1 or 0, change from 0 to 1 or conversely represents chunk boundary)
%   F    : a scalar representing sampling frequency
% Outputs:
%   none
  [filepath,~,~] = fileparts(path);
  if ~exist(filepath, 'dir')
    mkdir(filepath)
  end
  fp = fopen(path, "w");
  fprintf(fp, "# rate=%.0fHz\n", F);
  fprintf(fp, "A (binary), B (binary), Z (binary), signal (V fed to PDC via 5M1R on LDA), separate bundles (binary)\n");
  for i=1:length(A)
    fprintf(fp, "%d,%d,%d,%.5f,%d\n", A(i), B(i), Z(i), S(i), D(i));
  end
  fclose(fp);
end
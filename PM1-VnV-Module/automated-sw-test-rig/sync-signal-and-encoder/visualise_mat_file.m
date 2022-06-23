function visualise_mat_file(fname)
%visualise_mat_file.m Visualises data stored in mat file collected by picoscope as per PM1-SOF-ECD
%   This file visualises data stored in a mat file, assuming it was collected as per guidance
%   in PM1-SOF-ECD
% Inputs:
%   fname       : a string containing path to the file to be visualised 
% Outputs:
%   none
  load(fname)
  A = D0;
  B = D1;
  Z = D2;
  S = zeros(1,length(D0));
  D = zeros(1,length(D0));
  
  [position, direction] = decode_encoder(A, B);

  visualise_data(position, direction, Z, S, D)

end
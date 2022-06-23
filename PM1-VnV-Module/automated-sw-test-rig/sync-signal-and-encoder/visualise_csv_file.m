function visualise_csv_file(fname)
%visualise_csv_file.m Visualises data stored in csv file created by the
%sync-signal-and-encoder tool
%   This file visualises data stored in csv file (specified by
%   fname) and created by the sync-signal-and-encoder tool.
% Inputs:
%   fname       : a string containing path to the file to be visualised 
% Outputs:
%   none

  data = dlmread(fname,",",2,0);
  A = data(:,1);
  B = data(:,2);
  Z = data(:,3);
  S = data(:,4);
  D = data(:,5);
  
  [A_rec, B_rec] = reconstruct_encoder(A, B);

  [position, direction] = decode_encoder(A_rec, B_rec);

  [position] = sample_down(position, 2);
  position = position(1:length(Z));
  [direction] = sample_down(direction, 2);
  direction = direction(1:length(Z));
  
  visualise_data(position, direction, Z, S, D)
  %Use the below only if offset is known
  %hold on
  %z_offset = -551;
  %z_pole_spacing = 2;
  %position_adjusted = zero_offset_position(position, direction, Z, z_offset, z_pole_spacing);
  %plot(position_adjusted);

end
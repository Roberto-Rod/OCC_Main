function [] = save_as_mat_file(A, B, Z, T)

  D0 = A';
  D1 = B';
  D2 = Z';
  
  ExtraSamples = 0;
  Length = length(A);
  RequestedLength = Length;
  Tinterval = T;

  Tstart = 0.00;
  Version=char('6.14.44.5870')';
  save("tuning.mat", 'D0', 'D1', 'D2', 'ExtraSamples', 'Length', 'RequestedLength', 'Tinterval', 'Tstart', 'Version')
end
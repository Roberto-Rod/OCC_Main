function [A_rec, B_rec] = reconstruct_encoder(A, B)
%reconstruct_encoder.m reconstructs true sequence of encoder events
%   This function reconstructs the true sequence of encoder events. This
%   means it accounts for the fact that in the automated test rig the
%   A channel is 0.5 cycle ahead of B.
% Inputs:
%   A           : a vector representing encoder channel A signals
%   B           : a vector representing encoder channel B signals
% Outputs:
%   A_rec       : a vector representing encoder channel A signals after reconstruction
%   B_rec       : a vector representing encoder channel B signals after reconstruction

  %This code resamples the A and B with double the sampling frequency
  N = 2; 
  A_rec = reshape(repmat(A(:).',N,1),1,[]);
  B_rec = reshape(repmat(B(:).',N,1),1,[]);
  
  %This code shifts B with respect to A by one sample
  A_rec = [A_rec A(end)];  
  B_rec = [B(1) B_rec];

end
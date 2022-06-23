function [var_sampled_down] = sample_down(var, f)
%sample_down.m Samples the data down by a factor of f
%   This file re-samples the vector v down by using avery f-th element in
%   the vector.
% Inputs:
%   var              : a vector of data
%   f                : a scalar, factor for scaling down
% Outputs:
%   var_sampled_down : a vector corresponding to the variable var sampled down by a factor f

  t = 1:length(var);
  t_new = 1:f:length(var);
  var_sampled_down = interp1(t,var,t_new);
end
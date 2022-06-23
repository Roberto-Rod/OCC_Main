function [] = visualise_data(position, direction, Z, signal, D)
%visualise_data.m Visualises position, direction, signal, Z pole and bundle data
% Inputs:
%   position   : a vector containing lens carriage position 
%   direction  : a vector containing lens carriage direction of motion
%   Z          : a vector containing information on Z poles location
%   signal     : a vector containing information on data bundles
% Outputs:
%   none
  figure;
  hold on;
  x=zeros(1,sum(Z));
  y=zeros(1,sum(Z));
  counter = 1;
  for i=1:length(Z)
    if Z(i) == 1
      x(counter) = i;
      y(counter) = position(i);
      counter=counter+1;
    end
  end
  plot(x,y,'.')
  plot(position)
  plot(direction.*2000)
  %plot(signal./12)
  plot(signal.*500)
  plot(D.*2000)
end
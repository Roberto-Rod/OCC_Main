function [start, stop] = find_enc_active_state(position, direction, range)
%find_enc_active_state.m Finds active state of the encoder
%   This file finds such start and stop indices that the lens 
%   carriage between start and stop is oscillating with at least
%   the desired scan range.
% Inputs:
%   position    : a vector representing position of the lens carriage over time
%   direction   : a vector representing drection of the lens carriage motion over time
%   range       : a scalar representing the desired minimum range of the lens carriage
% Outputs:
%   start       : a scalar representing the start of the active range of oscillations
%   stop        : a scalar representing the stop of the active range of oscillations

  amplitude = zeros(1, length(position));
  min_pos = NaN;
  max_pos = NaN;
  cycle_state = 0;
  for i = 2:length(position)
    if cycle_state == 0
      if direction(i) ~= direction(i-1)
        if direction(i) == 0
          cycle_state = 1;
        else
          cycle_state = 2;
        end
      end
      amplitude(i) = amplitude(i-1);
    elseif cycle_state == 1
      if direction(i) == 0
        if isnan(min_pos)
          min_pos=position(i);
        elseif position(i) < min_pos
          min_pos=position(i);
        end
        if isnan(max_pos)
          max_pos=position(i);
        elseif position(i) > max_pos
          max_pos=position(i);
        end
        amplitude(i) = amplitude(i-1);
      else
        if ~isnan(min_pos) && ~isnan(max_pos)
            amplitude(i) = max_pos - min_pos;
        else
          amplitude(i) = amplitude(i-1);
        end
        cycle_state = 2;
        min_pos = NaN;
        max_pos = NaN;
      end
    elseif cycle_state == 2
      if direction(i) == 1
        if isnan(min_pos)
          min_pos=position(i);
        elseif position(i) < min_pos
          min_pos=position(i);
        end
        if isnan(max_pos)
          max_pos=position(i);
        elseif position(i) > max_pos
          max_pos=position(i);
        end
        amplitude(i) = amplitude(i-1);
      else
        if ~isnan(min_pos) && ~isnan(max_pos)
          amplitude(i) = max_pos - min_pos;
        else
          amplitude(i) = amplitude(i-1);
        end
        cycle_state = 1;
        min_pos = NaN;
        max_pos = NaN;
      end
    end
  end
  start = 1;
  %set start when amplitude increases to range
  while(amplitude(start) < range*1000)
    start = start + 1;
  end
  
  stop = length(amplitude)-1;
  while(amplitude(stop)>amplitude(stop+1) || amplitude(stop)<5000)
    stop = stop - 1;
  end
  
  %plot(position);
  %hold on
  %plot(amplitude);
  %plot([start start], [0 5000]);
  %plot([stop stop], [0 5000]);
end
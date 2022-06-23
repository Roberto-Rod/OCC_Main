function [corrected_pos] = zero_offset_position(position, direction, Z, offset, z_pole_spacing)
%zero_offset_position.m Corrects position data for the offset using Z pole information
%   This file corrects the position of the signal according to Z pole positions
% Inputs:
%   position       : a vector containing position of the lens carriage
%   direction      : a vector containing direction of the lens carriage motion
%   Z              : a vector containing Z pole information
%   offset         : a scalar representing offset of the centre of oscillation with respect to the Z pole
%   z_pole_spacing : a scalar representing distance between consecutive Z poles
% Outputs:
%   corrected_pos  : a vector representing corrected position with respect to the Z pole
  min_pos = NaN;
  max_pos = NaN;
  pos_offset = 0;
  cycle_state = 0;
  autocentre = 0;
  corrected_pos = zeros(1,length(position));
  for i = 2:length(position)
    if cycle_state == 0
      if direction(i) ~= direction(i-1)
        if direction(i) == 0
          cycle_state = 1;
        else
          cycle_state = 2;
        end
      end
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
        if Z(i) == 1
          if abs(position(i) - autocentre - offset) < z_pole_spacing/4*1000
            pos_offset = position(i) - offset;
          end
        end
      else
        if ~isnan(min_pos) && ~isnan(max_pos)
            autocentre = (min_pos + max_pos)/2;
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
        if Z(i) == 1
          if abs(position(i) - autocentre - offset) < z_pole_spacing/4*1000
            pos_offset = position(i) - offset;
          end
        end
      else
        if ~isnan(min_pos) && ~isnan(max_pos)
            autocentre = (min_pos + max_pos)/2;
        end
        cycle_state = 1;
        min_pos = NaN;
        max_pos = NaN;
      end
    end
    corrected_pos(i) = position(i) - pos_offset;
  end
  %Test code
  %plot(position)
  %hold on
  %plot(corrected_pos)
end
function offset = find_offset(position, direction, Z)
%find_offset.m Finds offset of centre of oscillation with respect to Z-pole.
%   This file processes position and direction as well as Z-pole signals
%   to work out offset of centre of lens carriage oscillation with respect
%   to an absolute position (Z-pole location).
% Inputs:
%   position    : a vector representing the lens carriage position
%   direction   : a vector representing the lens carriage direction of motion
%   Z           : a vector representing Z poles pulses
% Outputs:
%   offset      : a scalar representing the offset of the centre of oscillation from the nearest Z pole
  pos_offset = 0;
  offset_vect = [];
  cycle_state = 0;
  min_pos = NaN;
  max_pos = NaN;
  cycle_count = 0;
  z_pos = [];
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
          z_pos(end+1) = position(i) - pos_offset;  
        end
      else
        cycle_count = cycle_count + 1;
        if ~isnan(min_pos) && ~isnan(max_pos)
            pos_offset = (min_pos + max_pos)/2;
        end
        if ~isempty(z_pos)
          offset_vect(end+1) = z_pos(abs(z_pos) == min(abs(z_pos)));
        end
        z_pos=[];
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
          z_pos(end+1) = position(i) - pos_offset;  
        end
      else
        cycle_count = cycle_count + 1;
        if ~isnan(min_pos) && ~isnan(max_pos)
            pos_offset = (min_pos + max_pos)/2;
        end
        if ~isempty(z_pos)
          offset_vect(end+1) = z_pos(abs(z_pos) == min(abs(z_pos)));
        end
        z_pos=[];
        cycle_state = 1;
        min_pos = NaN;
        max_pos = NaN;
      end
    end
  end
  if mod(offset_vect,2) == 0
    offset_vect = offset_vect(1:end-1);
  end
  offset=round(median(offset_vect));
end

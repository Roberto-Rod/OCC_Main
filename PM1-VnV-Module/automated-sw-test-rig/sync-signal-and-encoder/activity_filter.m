function [S0_out, S1_out, S2_out] = activity_filter(S0, S1, S2, window)
%activity_filter.m Truncates the three channels of encoder data.
%   This function filters the three channels of data simultaneously by
%   removing such portions of the signals where there are no signals longer
%   than the filter window.
% Inputs:
%   S0      : a vector containig first channel of information
%   S1      : a vector containig second channel of information
%   S2      : a vector containig third channel of information
%   window  : a scalar; any activity shorther than window will be filtered out
% Outputs:
%   S0_out  : a vector containig first channel of information (truncated)
%   S1_out  : a vector containig second channel of information (truncated)
%   S2_out  : a vector containig third channel of information (truncated)
  
  %% Check if all signals are of the same length
  if length(S0) ~= length(S1) || length(S1) ~= length(S2)
    error("Signals of different length!")
  end
  
  %% Mark places where the signals change (i.e. are active)
  lth = length(S0);
  signal_present_unfiltered = zeros(1, lth);
  for idx = 2:lth
    if S0(idx-1) ~= S0(idx) || S1(idx-1) ~= S1(idx) || S2(idx-1) ~= S2(idx)
      signal_present_unfiltered(idx) = 1;
    end
  end
  
  %% Combine areas where signals are active into segments
  signal_present_segmented = zeros(1, lth);
  state = 0; %0 -> inactive; 1 -> active
  i = 1;
  while i < lth-1
    if state == 0
      if signal_present_unfiltered(i) == 1
        state = 1;
        signal_present_segmented(i) = 1;
      end
    else
      if signal_present_unfiltered(i) == 0
        if ~any(signal_present_unfiltered(i+1:min(lth,i+window)))
          state = 0;
          i = min(lth,i+window);
        else
          new_i=min(lth,i+window);
          while(signal_present_unfiltered(new_i)==0)
            new_i = new_i - 1;
          end
          signal_present_segmented(i:new_i) = ones(1,length(i:new_i));
          i = new_i - 1;
        end
      else
        signal_present_segmented(i) = 1;
      end
    end
    i=i+1;
  end

  %% Find the beginning and the end of the signal
  n = 1;
  signal_start = find_nth(signal_present_segmented,n);
  while signal_present_segmented(signal_start+5*window) == 0
    n = n + 1;
    signal_start = find_nth(signal_present_segmented,n);
  end

  signal_end = find(signal_present_segmented, 1, 'last');
  
  S0_out = S0(signal_start:signal_end);
  S1_out = S1(signal_start:signal_end);
  S2_out = S2(signal_start:signal_end);

end

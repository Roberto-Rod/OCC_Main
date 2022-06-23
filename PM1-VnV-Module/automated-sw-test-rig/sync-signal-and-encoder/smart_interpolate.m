function [A_int, B_int, Z_int] = smart_interpolate(A, B, Z, old_sampling_T, new_sampling_T)
%smart_interpolate.m Samples down encoder signals in a smart way.
%   This file processes the encoder signals, originally sampled every 
%   old_sampling_T. The code re-samples the encoder signals to
%   new_sampling_T, however it ensures that in case of undersampling, the
%   sequence of the ch A and ch B changes is maintained. In this code, it 
%   is assumed that signal B at index "i" is updated later than signal A at
%   the same index "i".
% Inputs:
%   A              : a vector, contains channel A encoder signals
%   B              : a vector, contains channel B encoder signals
%   Z              : a vector, contains Z pole encoder signals
%   old_samplong_T : a scalar, represents the original sampling frequency
%   new_samplong_T : a scalar, represents the new sampling frequency
% Outputs:
%   A_int          : re-sampled encoder signal from channel A
%   B_int          : re-sampled encoder signal from channel B
%   Z_int          : re-sampled encoder signal from channel Z
  t_old = old_sampling_T * [0:length(A)-1];
  t_new = 0:new_sampling_T:t_old(end);
  new_lth = length(t_new);

  A_int = zeros(1,new_lth);
  B_int = zeros(1,new_lth);
  Z_int = zeros(1,new_lth);
  A_int(1) = A(1);
  B_int(1) = B(1);
  Z_int(1) = Z(1);
  A_old = A(1);
  B_old = B(1);
  CH_queue = [];
  val_queue = [];
  Z_flag = 0;
  last_old_idx = 1;
  current_old_idx = 1;
  last_Z_flag = 0;
  for i=2:new_lth
    current_time = (i-1)*new_sampling_T;
    while t_old(current_old_idx) < current_time
      current_old_idx = current_old_idx + 1;
    end
    for j = last_old_idx:current_old_idx
      if A(j) ~= A_old
        CH_queue(end+1) = 1;
        val_queue(end+1) = A(j);
        A_old = A(j);
      end
      if B(j) ~= B_old
        CH_queue(end+1) = 2;
        val_queue(end+1) = B(j);
        B_old = B(j);
      end
      if Z(j) == 1
        Z_flag = 1;
      end
    end
    last_old_idx = current_old_idx;
    if ~isempty(CH_queue)
      double_change_flag=0;
      if CH_queue(1) == 1
        A_int(i) = val_queue(1);
        if length(CH_queue) > 1
          if CH_queue(2) ~= 1
            B_int(i) = val_queue(2);
            double_change_flag=1;
          else
            B_int(i) = B_int(i-1);
          end
        else
          B_int(i) = B_int(i-1);
        end
      else
        A_int(i) = A_int(i-1);
        B_int(i) = val_queue(1);
      end
      if length(CH_queue) > 1
        if double_change_flag == 1
          if length(CH_queue) > 2
            CH_queue = CH_queue(3:end);
            val_queue = val_queue(3:end);
          else
            CH_queue = [];
            val_queue = [];
          end
        else
          CH_queue = CH_queue(2:end);
          val_queue = val_queue(2:end);
        end
      else
        CH_queue = [];
        val_queue = [];
      end
    else
      A_int(i) = A_int(i-1);
      B_int(i) = B_int(i-1);
    end
    
    if Z_flag == 1
      if last_Z_flag == 0
        Z_int(i) = 1;
      end
      Z_flag = 0;
      last_Z_flag = 1;
    else
      last_Z_flag = 0;
    end
  end
end

%% The above perform the smart interpolation with deterministic A/B
% sequence (assumes B occurs later than A)
% The below is a version of the interpolation above, however it assumes
% that A and B channels change at the same time.
% function [A_int, B_int, Z_int] = smart_interpolate(A, B, Z, old_sampling_T, new_sampling_T)
%   t_old = old_sampling_T * [0:length(A)-1];
%   t_new = 0:new_sampling_T:t_old(end);
%   new_lth = length(t_new);
% 
%   A_int = zeros(1,new_lth);
%   B_int = zeros(1,new_lth);
%   Z_int = zeros(1,new_lth);
%   A_int(1) = A(1);
%   B_int(1) = B(1);
%   Z_int(1) = Z(1);
%   A_old = A(1);
%   B_old = B(1);
%   Z_old = Z(1);
%   CH_queue = [];
%   val_queue = [];
%   Z_flag = 0;
%   last_old_idx = 1;
%   current_old_idx = 1;
%   last_Z_flag = 0;
%   for i=2:new_lth
%     current_time = (i-1)*new_sampling_T;
%     while t_old(current_old_idx) < current_time
%       current_old_idx = current_old_idx + 1;
%     end
%     for j = last_old_idx:current_old_idx
%       if A(j) ~= A_old
%         CH_queue(end+1) = 1;
%         val_queue(end+1) = A(j);
%         A_old = A(j);
%       end
%       if B(j) ~= B_old
%         CH_queue(end+1) = 2;
%         val_queue(end+1) = B(j);
%         B_old = B(j);
%       end
%       if Z(j) ~= Z_old
%         Z_flag = 1;
%       end
%     end
%     last_old_idx = current_old_idx;
%     if ~isempty(CH_queue)
%       if CH_queue(1) == 1
%         A_int(i) = val_queue(1);
%         B_int(i) = B_int(i-1);
%       else
%         A_int(i) = A_int(i-1);
%         B_int(i) = val_queue(1);
%       end
%       if length(CH_queue) > 1
%         CH_queue = CH_queue(2:end);
%         val_queue = val_queue(2:end);
%       else
%         CH_queue = [];
%         val_queue = [];
%       end
%     else
%       A_int(i) = A_int(i-1);
%       B_int(i) = B_int(i-1);
%     end
%     
%     if Z_flag == 1
%       if last_Z_flag == 0
%         Z_int(i) = 1;
%       end
%       Z_flag = 0;
%       last_Z_flag = 1;
%     else
%       last_Z_flag = 0;
%     end
%   end
% end
% 

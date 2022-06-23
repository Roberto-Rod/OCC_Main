function [A_adj, B_adj, Z_adj, signal_adj, D] = align_encoder_and_signal(A, B, Z, pos, dir, scans, start, stop, scan_range)
%align_encoder_and_signal.m Synchronises enocoder with signal data.
%   This file processes the encoder and analogue signals, synchronises them
%   together.
% Inputs:
%   A           : a vector, represents channel A encoder signal
%   B           : a vector, represents channel B encoder signal
%   Z           : a vector, represents Z pole encoder signal
%   pos         : a vector, represents position of the lens carriage
%   dir         : a vector, represents direction of the lens carriage motion
%   scans       : an n x 5000 matrix, represents n scans, each consisting 5000 points
%   start       : a scalar, indicates index at which the encoder signal achieves active state
%   stop        : a scalar, indicates index at which the tail of the encoder signal begins
%   scan_range  : a scalar, indicates scan range in mm
% Outputs:
%   A_adj       : a vector, represents channel A encoder signal after alignment with analogue signal
%   B_adj       : a vector, represents channel B encoder signal after alignment with analogue signal
%   Z_adj       : a vector, represents Z pole encoder signal after alignment with analogue signal
%   signal_adj  : a vector, represents analogue signal after alignment with encoder
%   D_adj       : a vector, represents chunks of signal that should not be interrupted


  % first_scan_dir = 1 means the first scan is played forwad
  % first_scan_dir = 0 means the first scan is played backward
  first_scan_dir = 0;
  scan_range = scan_range * 1000;
  
  %% Identify range where the scans can repeat (ignore the first 25 cycles)
  %move start by 20 cycles
  for i = 1:20
    start = start + 1;
    while (~(pos(start-1) > 0 && pos(start) <= 0))
      start = start + 1;
    end
  end
  %start now points at a point in time when the position decreases (the
  %first 20 cycles are rejected by the system)
  
  %move repetition start by another 5 cycles (usually the amplitude is
  %stable after 25 cycles)
  repetition_start = start;
  repetition_stop = stop;
  for i = 1:5
    repetition_start = repetition_start + 1;
    while (~(pos(repetition_start - 1) > 0 && pos(repetition_start) <= 0))
      repetition_start = repetition_start + 1;
    end
  end %repetition_start points at a point in time when the position decreases

  while(~(pos(repetition_stop - 1) > 0 && pos(repetition_stop) <= 0))
    repetition_stop = repetition_stop - 1;
  end %repetition_stop points at a point in time when the position decreases

  %% Create A/B/Z/D and analogue signals for the period where the scan range is below 5000
  offset = 0;
  signal_adj(1) = scans(1,1);
  signal_time(1) = 1;
  A_adj(1) = A(1);
  B_adj(1) = B(1);
  Z_adj(1) = Z(1);
  D(1) = 0;
  t = 2;
  while t < start
    if first_scan_dir == 1
      signal_adj(end+1) = scans(1,1);
    else
      signal_adj(end+1) = scans(1,end);
    end
    A_adj(end + 1) = A(t - offset);
    B_adj(end + 1) = B(t - offset);
    Z_adj(end + 1) = Z(t - offset);
    D(end + 1) = 0;
    signal_time(end+1) = t;
    t = t + 1;
  end
  while dir(t - offset) ~= 1 || abs(pos(t - offset)) > scan_range / 2 + 2
    if first_scan_dir == 1
      signal_adj(end + 1) = scans(1, 1);
    else
      signal_adj(end + 1) = scans(1, end);
    end
    A_adj(end + 1) = A(t - offset);
    B_adj(end + 1) = B(t - offset);
    Z_adj(end + 1) = Z(t - offset);
    signal_time(end+1) = t;
    D(end + 1) = 0;
    t = t + 1;
    if t - offset > repetition_stop
      offset = offset + repetition_stop - repetition_start;
    end
  end
  %At this point of code t is at the point in time that 20 cycles have
  %elapsed since the first cycle >5000 in amplitude and 
  current_D = 0;
  
  %% Feed scan data
  for i=1:size(scans, 1)
    %Feed the scan itself
    for j=1:size(scans, 2)
      while dir(t - offset) == 1 && pos(t - offset) < - scan_range / 2 + j || dir(t - offset) == 0 && pos(t - offset) > scan_range / 2 - j
        A_adj(end + 1) = A(t - offset);
        B_adj(end + 1) = B(t - offset);
        Z_adj(end + 1) = Z(t - offset);
        D(end + 1) = current_D;
        t = t + 1;
        if (pos(t - offset - 1) > 0 && pos(t - offset) <= 0) && mod(i, 20) == 0 && size(scans, 1)-i > 20
          current_D = mod(current_D + 1, 2);
        end
        if t - offset > repetition_stop
          offset = offset + repetition_stop - repetition_start;
        end
      end
      if dir(t - offset) == first_scan_dir
        if signal_time(end) ~= t
          signal_adj(end + 1) = scans(i, j);
          signal_time(end + 1) = t;
        end
      else
        if signal_time(end) ~= t
          signal_adj(end + 1) = scans(i, size(scans, 2) - j + 1);
          signal_time(end + 1) = t;
        end
      end
    end
    %Next, rewind to the beginning of the consecutive scan
    end_of_scan_dir = dir(t - offset);
    while dir(t - offset) == end_of_scan_dir || abs(pos(t - offset)) > scan_range / 2 + 1
      A_adj(end + 1) = A(t - offset);
      B_adj(end + 1) = B(t - offset);
      Z_adj(end + 1) = Z(t - offset);
      D(end + 1) = current_D;
      t = t + 1;
      if t - offset > repetition_stop
        offset = offset + repetition_stop - repetition_start;
      end
    end
  end

  %% Finally, add the A/B/Z/D and analogue signals from the tail of the encoder data

  %First, get to the point that we can begin the tail
  while (~(pos(t - offset - 1) > 0 && pos(t - offset) <= 0))
    signal_adj(end+1) = signal_adj(end);
    A_adj(end + 1) = A(t - offset);
    B_adj(end + 1) = B(t - offset);
    Z_adj(end + 1) = Z(t - offset);
    D(end + 1) = current_D;
    signal_time(end + 1) = t;
    t = t + 1;
    if t - offset > repetition_stop
      offset = offset + repetition_stop - repetition_start;
    end
  end

  current_D = mod(current_D + 1, 2);
  %Then, feed the tail
  offset = t - repetition_stop;
  while t - offset < length(A)
    signal_adj(end + 1) = signal_adj(end);
    A_adj(end + 1) = A(t - offset);
    B_adj(end + 1) = B(t - offset);
    Z_adj(end + 1) = Z(t - offset);
    D(end + 1) = current_D;
    signal_time(end + 1) = t;
    t = t + 1;
  end
  
  signal_adj = interp1(signal_time, signal_adj, 1:length(A_adj));

  %% Test code
  %Process the encoder data
  %[A_rec, B_rec] = reconstruct_encoder(A_adj, B_adj);

  %[pos_res, dir_res] = decode_encoder(A_rec, B_rec);
  %[pos_res] = sample_down(pos_res);
  %pos_res = pos_res(1:length(A_adj));
  %[dir_res] = sample_down(dir_res);
  %dir_res = dir_res(1:length(A_adj));
    
  %plot(A_adj.*200)
  %hold on
  %plot(B_adj.*200+300)

  %plot(pos_res)
  %plot(pos)
  %plot(dir_res)
  
  %plot(signal_adj/12)
  
end

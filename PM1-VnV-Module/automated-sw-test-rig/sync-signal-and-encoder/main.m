function [] = main(varargin)
%main.m Synchronises enocoder with signal data and produces files accepted
%by the automated software test rig
%   This file processes the encoder and analogue signals, synchronises them
%   and saves to .csv file. In case no, or incomplete inputs are supplied,
%   the code will ask for specifying the correct paths with a UI.
% Inputs:
%   varargin{1} : a string, optional, path to encoder files
%   varargin{2} : a string, optional, path to spatial data files
%   varargin{3} : a string, optional, path to output synchronised files
% Outputs:
%   none

%% Set up some fundamental variables
  sampling_freq_out = 1000000; %1MHz sampling frequency
  scan_range = 5; %mm
  z_pole_spacing = 2; %mm
  scan_speed = 100; %Hz
  offset = 2.5; % Offset voltage in V
  
  %% Verify the input variables
  if nargin > 3
    error("Too many input parameters")
  end

  if nargin > 0
    if ~ischar(varargin{1})
      error("Parameter 1 is not a character array.")
    end
    encoder_path = varargin{1};
  else
    encoder_path = uigetdir("C:/Users/PiotrLaszczak/Occuity Limited/Occuity - Documents/Projects/P1 Pachymeter/Software documentation/Software Verification/Automated sw test rig/Encoder database", "Select folder with encoder information");
    if encoder_path == 0
      error("No encoder information path selected.")
    end
  end
  if encoder_path(end) == '/' || encoder_path(end) == '\'
    encoder_folder = regexp(encoder_path, '[\\/]([^\\/\f\n\r\t\v]+)[\\/]$','tokens');
  else
    encoder_folder = regexp(encoder_path, '[\\/]([^\\/\f\n\r\t\v]+)$','tokens');
  end
  encoder_folder = encoder_folder{1}{1};
  
  if nargin > 1
    if ~ischar(varargin{2})
      error("Parameter 2 is not a character array.")
    end
    scan_path = varargin{2};
  else
    scan_path = uigetdir("C:/Users/PiotrLaszczak/Occuity Limited/Occuity - Documents/Projects/P1 Pachymeter/Software documentation/Software Verification/Automated sw test rig/Scan database", "Select folder with scan information");
    if scan_path == 0
      error("No scan information path selected.")
    end
  end
  
  if scan_path(end) == '/' || scan_path(end) == '\'
    scan_folder = regexp(scan_path, '[\\/]([^\\/\f\n\r\t\v]+)[\\/]$','tokens');
  else
    scan_folder = regexp(scan_path, '[\\/]([^\\/\f\n\r\t\v]+)$','tokens');
  end
  scan_folder = scan_folder{1}{1};
    
  if nargin > 2
    if ~ischar(varargin{3})
      error("Parameter 3 is not a character array.")
    end
    out_path = varargin{3};
  else
    out_path = uigetdir("C:/Users/PiotrLaszczak/Occuity Limited/Occuity - Documents/Projects/P1 Pachymeter/Software documentation/Software Verification/Automated sw test rig/Processed database", "Select output folder");
    if out_path == 0
      error("No ouput folder selected.")
    end
  end
  
  clear varargin
  
  %% Process the tuning in the encoder dataset
  %First load the encoder info
  if encoder_path(end) == '\' || encoder_path(end) == '/'
      tuning_file = strcat(encoder_path, "tuning.mat");
  else
      tuning_file = strcat(encoder_path, "/tuning.mat");
  end
  load(tuning_file);

  %Then truncate portions of the encoder data that are irrelevant
  filter_window = int32(round(1/scan_speed/scan_range*z_pole_spacing/Tinterval));
  [A, B, Z] = activity_filter(D0, D1, D2, filter_window);

  %%%%%%%%%%%%%%%%%%%%%%%%%%
  %Test code - makes processing quicker
  %l = round(length(A)/5);
  %A = A(1:l);
  %B = B(1:l);
  %Z = Z(1:l);
  %%%%%%%%%%%%%%%%%%%%%%%%%%%

  %Then interpolate data to achieve correct sampling frequency, as
  %specified in sampling_freq_out
  [A_int, B_int, Z_int] = smart_interpolate(A, B, Z, Tinterval, 1/sampling_freq_out);
  
  %Finally find the absolute position of the oscillation center
  [A_rec, B_rec] = reconstruct_encoder(A_int, B_int);

  [position, direction] = decode_encoder(A_rec, B_rec);
  [pos_res] = sample_down(position, 2);
  pos_res = pos_res(1:length(Z_int));
  [dir_res] = sample_down(direction, 2);
  dir_res = dir_res(1:length(Z_int));
  
  %visualise_data(pos_res, dir_res, Z_int, zeros(1,length(pos_res)))
  
  z_offset = find_offset(pos_res, dir_res, Z_int);
  
  %% Save the tuning output
  if out_path(end) ~= '\' && out_path(end) ~= '/'
    out_tuning_file = strcat(out_path, "/");
  else
    out_tuning_file = out_path;
  end
  out_tuning_file = strcat(out_tuning_file, scan_folder);
  out_tuning_file = strcat(out_tuning_file, "/tuning.csv");
  save_data(out_tuning_file,A_int,B_int,Z_int,ones(1,length(A_int))*offset,zeros(1,length(A_int)),sampling_freq_out);

  %Clean up - clear all varialbles related to tuning.
  clear D0 D1 D2 ExtraSamples Length RequestedLength Tinterval Tstart Version A B Z A_int B_int A_rec B_rec Z_int position pos_res direction dir_res filter_window

  %% Find all scan information
  if scan_path(end) == '\' || scan_path(end) == '/'
    scan_files = dir(strcat(scan_path,'*.csv'));
  else
    scan_files = dir(strcat(scan_path,'/*.csv'));
  end

  encoder_date = regexp(encoder_folder, '^([0-9]{4}-[0-9]{2}-[0-9]{2})','tokens');
  encoder_date = encoder_date{1}{1};
  
  %% Iterate over all scan files and convert spatial data to temporal data
  for i = 1:size(scan_files)
    %Inform about the progress
    fprintf("Processing file: %s\n", scan_files(i).name);
    
    %Load the scan file
    scan_file_name(i) = strcat(scan_files(i).folder, "\", scan_files(i).name);
    fprintf("Path to input scan file: %s\n", scan_file_name(i));
    data = dlmread(scan_file_name(i));

    [scans, ~, gain, ~] = validate_scan_data(data);

    %Reconstruct the original signal
    scans = reconstruct_saturation(scans);
    scans = normalise_scans(scans, gain);

    %Load the encoder data
    if encoder_path(end) == '\' || encoder_path(end) == '/'
      encoder_file = sprintf("%s%s-%04d.mat", encoder_path, erase(encoder_date, "-"), i);
    else
      encoder_file = sprintf("%s/%s-%04d.mat", encoder_path, erase(encoder_date, "-"), i);
    end
    load(encoder_file);
    filter_window = int32(round(1/scan_speed/scan_range*z_pole_spacing/Tinterval));
    [A, B, Z] = activity_filter(D0, D1, D2, filter_window);
    
    [A_int, B_int, Z_int] = smart_interpolate(A, B, Z, Tinterval, 1/sampling_freq_out);
  
    %Process the encoder data
    [A_rec, B_rec] = reconstruct_encoder(A_int, B_int);

    [position, direction] = decode_encoder(A_rec, B_rec);
    [pos_res] = sample_down(position, 2);
    pos_res = pos_res(1:length(Z_int));
    [dir_res] = sample_down(direction, 2);
    dir_res = dir_res(1:length(Z_int));
    
    %Offset the raw encoder data, so that it position is centred about
    %middle of the scan range, using Z signal as reference.
    pos_res = zero_offset_position(pos_res, dir_res, Z_int, z_offset, z_pole_spacing);
    
    %visualise_data(pos_res, dir_res, Z_int, zeros(1,length(pos_res)))
    
    %Readjust the encoder data to the number of scans
    [start_cnt, stop_cnt] = find_enc_active_state(pos_res, dir_res, scan_range);
    
    [A_adj, B_adj, Z_adj, signal, D_adj] = align_encoder_and_signal(A_int, B_int, Z_int, pos_res, dir_res, scans, start_cnt, stop_cnt, scan_range);
    
    %Test code
    %[A_rec, B_rec] = reconstruct_encoder(A_adj, B_adj);

    %[pos_res, dir_res] = decode_encoder(A_rec, B_rec);
    %[pos_res] = sample_down(pos_res, 2);
    %pos_res = pos_res(1:length(A_adj));
    %[dir_res] = sample_down(dir_res, 2);
    %dir_res = dir_res(1:length(A_adj));
    %visualise_data(pos_res, dir_res, Z_adj, signal);

    %Process scan data back up the amplifier chain
    signal = simulate_signal(signal, sampling_freq_out, offset);

    %Save the data to play back
    if out_path(end) ~= '\' && out_path(end) ~= '/'
      out_data_file = strcat(out_path, "/");
    else
      out_data_file = out_path;
    end
    out_data_file = sprintf("%s%s/%03d-%s", out_data_file, scan_folder, i, scan_files(i).name);

    save_data(out_data_file, A_adj, B_adj, Z_adj, signal, D_adj, sampling_freq_out);    
    clear D0 D1 D2 ExtraSamples Length RequestedLength Tinterval Tstart Version A A_adj A_int A_rec B B_adj B_int B_rec Z Z_adj Z_int D_adj position pos_res direction dir_res gain scans signal start_cnt stop_cnt filter_window data encoder_file scan_file_name

  end
  
end

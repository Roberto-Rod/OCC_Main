%%pkg load control
close all
clear all

%%First, establish the amplifier chain model

%Stage 1 - transimpedance amplifier
%Stage 2 - non-inverting amplifier
%Stage 3 - Butterworth filter (Sallen-Key topology) stage 1
%Stage 4 - Butterworth filter (Sallen-Key topology) stage 2

%Stage 4:
C23 = 27*10^(-12); %27pF
R16 = 18*10^(3); %18k
R17 = 18*10^(3); %18k
C22 = 68*10^(-12); %68pF

H4 = tf(1, [C22*C23*R16*R17, C23*(R16+R17), 1]);
%Caluclating inverse of this transfer function actuall causes a lot of problems.
%First, inverse has less poles than zeros, and hence the TF is improper. This
%can be alleviated by adding poles very form zero. Unfortunately, even then,
%using inverse of the Butterworth filter can cause a lot of problems. Signal
%coming out of the amplifier chain should be, theoretically, very well filtered.
%However, there are sources of noise after the amplifier chain, e.g. IC9 (diffe-
%rential amplifier) or IC10 (ADC). This noise is then amplified by the inverse
%of the filter, which leads to very noisy result. Instead, it is suggested to
%model the filter with all-pass filter. This allows to simulate the phase shift
%induced by the Butterworth filter, but keeps the gain equal to 1. This means
%that the noise on the signal is not unnecessarily amplified. The filter below
%has been experimentally selected tomatch the phase shift of the Butterworth
%filter, particularly in the lower frequency range. Note that the Bode plot is
%created on the inverse of H4_inv. This is because direct use of H4_inv proved
%unstable. Therefore, to apply reversed phase shift, we will use the H4_inv on 
%data in reverse order, and then reverse it back.
H4_inv = tf([-1, 1.5*10^6], [1, 1.5*10^6]);

%[mag, pha, w] = bode (inv(H4_inv));
%[mag_act, pha_act, w_act] = bode (inv(H4));

%figure;
%plot(w(w<19000000), mag(w<19000000), 'b') %19000000 corresponds to ~300kHz
%hold on;
%plot(w_act(w_act<19000000), mag_act(w_act<19000000), 'r')
%xlabel("Frequency (rad/s)")
%ylabel("Magnitude (db)")
%set(gca, 'YScale', 'log');

%figure;
%plot(w(w<19000000), pha(w<19000000), 'b')
%hold on;
%plot(w_act(w_act<19000000), pha_act(w_act<19000000), 'r')
%xlabel("Frequency (rad/s)")
%ylabel("Phase shift (deg)")

%Stage 3:
C20 = 47*10^(-12); %47pF
R14 = 18*10^(3); %18k
R15 = 18*10^(3); %18k
C19 = 56*10^(-12); %56pF

H3 = tf(1, [C19*C20*R14*R15, C20*(R14+R15), 1]);
H3_inv = tf([-1, 1.5*10^6], [1, 1.5*10^6]);

%Stage 2:
R13 = 10*10^(3); %10k
R11 = 100; %100R
RDPOT = 5*10^(3); %5k

H2 = tf(R11 + RDPOT + R13, R11 + RDPOT);
H2_inv = inv(H2);

%Stage 1:
RIN = 5.1*10^(6); %5.1M
Rf = 330*10^(3); %330k =R3=R4=R5=R6
Cf = 5.6*10^(-12); %5.6p =C4=C5=C6=C7

H1 = tf(-4, [Cf*RIN, RIN/Rf]);
%Inverse of H3 would yield improper transfer function. Therefore, we add a zero
%far from coordinate center. We also multiply the transfer function by an all
%pass filter. The resulting transfer function is a good compromise: it has
%similar amplification for the relevant frequencies, but the amplification does
%not continue to increase for grequencies higher than required. At the same time
%the phase shift is inverse of the required phase shift. Therefore, applying
%this transfer function on flipped data will have the desired effect.
H1_inv = inv(H1*tf([1, 10^6], 10^6)*tf([-1, -10^6], [1, -10^6]));

%[mag, pha, w] = bode (inv(H1_inv));
%[mag_act, pha_act, w_act] = bode (inv(H1));

%figure;
%plot(w(w<19000000), mag(w<19000000), 'b') %19000000 corresponds to ~300kHz
%hold on;
%plot(w_act(w_act<19000000), mag_act(w_act<19000000), 'r')
%xlabel("Frequency (rad/s)")
%ylabel("Magnitude (db)")
%set(gca, 'YScale', 'log');

%figure;
%plot(w(w<19000000), pha(w<19000000), 'b')
%hold on;
%plot(w_act(w_act<19000000), pha_act(w_act<19000000), 'r')
%xlabel("Frequency (rad/s)")
%ylabel("Phase shift (deg)")


%%Next, read the sweep files and process them
i=1;

%for file_id = 1:57
for file_id = 1:5
  %%Read the csv file ending with file_id
  clear data Vin_real Vout_real Vin_simulated Vout_simulated
  file_name = sprintf("../CSV_Files/20210706-0002-CHA-TP14-CHB-PDC-VIA-5M1-SWEEP-200Hz-300kHz-1kHz-3ms-1.85V-0.15V-%d.csv", file_id)

  %%data = dlmread(file_name, ",", [0, 0, 200000, 3]);
  data = dlmread(file_name, ",", 'A1..C2000');
  %data = dlmread(file_name, ",");

  time = data(:,1);
  time = (time - time(1))*0.001; %In .csv file the time is in ms, this converts the units to seconds
  interp_time = linspace(0,time(end),round(time(end)*10000000)+1); %interpotating to 10MHz sampling frequency

  Vin_real = data(:,3);
  Vout_real = data(:,2);
  Vin_real = interp1(time, Vin_real, interp_time)'; %interpotating to 10MHz sampling frequency
  Vout_real = interp1(time, Vout_real, interp_time)'; %interpotating to 10MHz sampling frequency
  time = interp_time';
  
  %%Perform simulation of amplifier chain using the transfer function derived earlier
  %Note that offset is removed, to avoid transients
  V_TP4_simulated = lsim(H1, Vin_real - Vin_real(1), time);
  V_TP3_simulated = lsim(H2, V_TP4_simulated, time);
  V_TP7_simulated = lsim(H3, V_TP3_simulated, time);
  Vout_simulated = lsim(H4, V_TP7_simulated, time);
  %Add the offset back
  Vout_simulated = Vout_simulated + Vin_real(1) * (R11 + RDPOT + R13) / (R11 + RDPOT) / -4;

  %Calculate inverse relationship. Note that the data is flipped, as H4_inv,
  %H3_inv and H1_inv transfer functions remove phase shift, instead of adding.
  V_TP7_simulated_inv = flip(lsim(H4_inv, flip(Vout_real) - Vout_real(end), time));
  V_TP3_simulated_inv = flip(lsim(H3_inv, flip(V_TP7_simulated_inv), time));
  V_TP4_simulated_inv = lsim(H2_inv, V_TP3_simulated_inv, time);
  Vin_simulated = flip(lsim(H1_inv, flip(V_TP4_simulated_inv), time));
  %Add the offset back
  Vin_simulated = Vin_simulated + Vout_real(end) / (R11 + RDPOT + R13) * (R11 + RDPOT) * -4;

  figure
  plot(time, Vin_real, 'r')
  hold on
  plot(time, Vout_real, 'b')
  plot(time, Vout_simulated, 'k')
  plot(time, Vin_simulated, 'k')
  xlabel ("Time (s)");
  ylabel ("Voltage (V)");

  %%Evaluate the quality of the transfer function estimation on selected 'snippets' of data

  t_start = 3000;
  t_end = 18000;

  while length(time) > t_end
    %Select a subsection of the data
    Vout_real_sub = Vout_real(t_start:t_end);
    Vout_simulated_sub = Vout_simulated(t_start:t_end);
    Vin_real_sub = Vin_real(t_start:t_end);
    Vin_simulated_sub = Vin_simulated(t_start:t_end);
    time_sub = time(t_start:t_end);
    time_sub = time_sub - time_sub(1);

    %Find approximate period of the waveform
    Vout_max = max(Vout_real_sub); % Max of y
    Vout_min = min(Vout_real_sub); % Min of y
    Vout_range = (Vout_max-Vout_min); % Range of y
    Vout_zeroed = Vout_real_sub-Vout_max+(Vout_range/2); 
    zero_crossings = time_sub(Vout_zeroed .* circshift(Vout_zeroed,[1 0]) <= 0); % Find zero-crossings
    period = 2*max(diff(zero_crossings)); % Estimate period

    %Further constrain the selection and only take 8 periods of data
    Vout_real_sub = Vout_real_sub(time_sub <= 8*period);
    Vout_simulated_sub = Vout_simulated_sub(time_sub <= 8*period);
    Vin_real_sub = Vin_real_sub(time_sub <= 8*period);
    Vin_simulated_sub = Vin_simulated_sub(time_sub <= 8*period);
    time_sub = time_sub(time_sub <= 8*period);

    %Estimate frequency, amplitude and phase of the real Vout signal
    params_Vout_real = find_sin_params(time_sub, Vout_real_sub, -1);
    frequency(i) = params_Vout_real(2);
    amplitude_Vout_real = params_Vout_real(1);
    phase_shift_Vout_real = params_Vout_real(3);
    
    %Estimate frequency, amplitude and phase of the simulated Vout signal
    params_Vout_simulated = find_sin_params(time_sub, Vout_simulated_sub, frequency(i));
    amplitude_Vout_simulated = params_Vout_simulated(1);
    phase_shift_Vout_simulated = params_Vout_simulated(3);

    %Estimate frequency, amplitude and phase of the real Vin signal
    params_Vin_real = find_sin_params(time_sub, Vin_real_sub, frequency(i));
    amplitude_Vin_real = params_Vin_real(1);
    phase_shift_Vin_real = params_Vin_real(3);

    %Estimate frequency, amplitude and phase of the simulated Vin signal
    params_Vin_simulated = find_sin_params(time_sub, Vin_simulated_sub, frequency(i));
    amplitude_Vin_simulated = params_Vin_simulated(1);
    phase_shift_Vin_simulated = params_Vin_simulated(3);

    %Estimate amplitude and delay error on the Vout signal
    Vout_amplitude_error(i) = abs(amplitude_Vout_real - amplitude_Vout_simulated)*1000; % in mV
    Vout_delay_error(i) = abs(phase_shift_Vout_real - phase_shift_Vout_simulated);
    if Vout_delay_error(i) > 0.5
      Vout_delay_error(i) = 1 - Vout_delay_error(i);
    end
    Vout_delay_error(i) = Vout_delay_error(i) / frequency(i) * 1000000; %in us

    if Vout_delay_error(i) > 10
      disp("Vout high error!")
    end
      
    %Estimate amplitude and delay error on the Vout signal
    Vin_amplitude_error(i) = abs(amplitude_Vin_real - amplitude_Vin_simulated)*1000; % in mV
    Vin_delay_error(i) = abs(phase_shift_Vin_real - phase_shift_Vin_simulated);
    if Vin_delay_error(i) > 0.5
      Vin_delay_error(i) = 1 - Vin_delay_error(i);
    end
    Vin_delay_error(i) = Vin_delay_error(i) / frequency(i) * 1000000; %in us

    if Vin_delay_error(i) > 10
      disp("Vin high error!")
    end

    i = i + 1
    
    t_start = t_start + 15000;
    t_end = t_end + 15000;
  end
end

%%Plot fit errors as a function of frequency for Vout simulation
figure
[axes, hline1, hline2] = plotyy(frequency, Vout_amplitude_error, frequency, Vout_amplitude_error ./ 33);
set(hline1,'Marker','x');
set(hline1,'LineStyle','none');
set(hline2,'Marker','o');
set(hline2,'LineStyle','none');
ylabel (axes(1), "Vout amplitude error (mV)");
ylabel (axes(2), "Vout amplitude error (%)");
xlabel ("Frequency (Hz)")

figure
[axes, hline1, hline2] = plotyy(frequency, Vout_delay_error, frequency, Vout_delay_error .* 2500 .* 2 .* 3.14 .* 100 ./1000000);
set(hline1,'Marker','x');
set(hline1,'LineStyle','none');
set(hline2,'Marker','o');
set(hline2,'LineStyle','none');
ylabel (axes(1), "Vout delay error (us)");
ylabel (axes(2), "Vout delay error (um)");
xlabel ("Frequency (Hz)")

%%Plot fit errors as a function of frequency for Vin simulation
figure
[axes, hline1, hline2] = plotyy(frequency, Vin_amplitude_error, frequency, Vin_amplitude_error ./ 33);
set(hline1,'Marker','x');
set(hline1,'LineStyle','none');
set(hline2,'Marker','o');
set(hline2,'LineStyle','none');
ylabel (axes(1), "Vin amplitude error (mV)");
ylabel (axes(2), "Vin amplitude error (%)");
xlabel ("Frequency (Hz)")
xlim(axes(1), [0,40000]);
xlim(axes(2), [0,40000]);

figure
[axes, hline1, hline2] = plotyy(frequency, Vin_delay_error, frequency, Vin_delay_error .* 2500 .* 2 .* 3.14 .* 100 ./1000000);
set(hline1,'Marker','x');
set(hline1,'LineStyle','none');
set(hline2,'Marker','o');
set(hline2,'LineStyle','none');
ylabel (axes(1), "Vin delay error (us)");
ylabel (axes(2), "Vin delay error (um)");
xlabel ("Frequency (Hz)")

%%Save Vout fit errors as a function of frequency to file
fid = fopen('TP14-PDC-TF-error.csv','w');
fprintf(fid,"frequency [Hz], amplitude errror [mV], amplitude error [%% FSO], delay error [us], max delay error [um]\n");
fclose(fid);

csvwrite("TP14-TP4-TF-error.csv", [frequency', Vout_amplitude_error', Vout_amplitude_error' ./ 33, Vout_delay_error', Vout_delay_error' .* 2500 .* 2 .*3.14 .* 100 ./1000000], '-append');

%%Save Vin fit errors as a function of frequency to file
fid = fopen('TP4-TP14-TF-error.csv','w');
fprintf(fid,"frequency [Hz], amplitude errror [mV], amplitude error [%% FSO], delay error [us], max delay error [um]\n");
fclose(fid);

csvwrite("PDC-TP14-TF-error.csv", [frequency', Vin_amplitude_error', Vin_amplitude_error' ./ 33, Vin_delay_error', Vin_delay_error' .* 2500 .* 2 .*3.14 .* 100 ./1000000], '-append');

function [S_TF] = apply_TF(TF, F, S)
%apply_TF Applies Transfer Function (TF) to signal S, running at frequency F
%   Detailed explanation goes here

time = 0:(1/F):((1/F)*(length(S)-1));

interp_time = linspace(0,time(end),round(time(end)*10000000)+1)'; %interpotating to 10MHz sampling frequency

Vout_real = S;
Vout_real = interp1(time, Vout_real, interp_time)'; %interpotating to 10MHz sampling frequency

H1_inv = TF{1};
H2_inv = TF{2};
H3_inv = TF{3};
H4_inv = TF{4};

%Calculate inverse relationship. Note that the data is flipped, as H4_inv,
%H3_inv and H1_inv transfer functions remove phase shift, instead of adding.
V_TP7_simulated_inv = flip(lsim(H4_inv, flip(Vout_real) - Vout_real(end), interp_time));
V_TP3_simulated_inv = flip(lsim(H3_inv, flip(V_TP7_simulated_inv), interp_time));
V_TP4_simulated_inv = lsim(H2_inv, V_TP3_simulated_inv, interp_time);
Vin_simulated = flip(lsim(H1_inv, flip(V_TP4_simulated_inv), interp_time));

S_TF = interp1(interp_time, Vin_simulated, time); %interpotating to time back again

% %Add the offset back
% R13 = 10*10^(3); %10k
% R11 = 100; %100R
% RDPOT = 5*10^(3); %5k
% %Vin_simulated = Vin_simulated + Vout_real(end) / (R11 + RDPOT + R13) * (R11 + RDPOT) * -4;


end
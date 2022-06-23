function signal_out = simulate_signal(signal_in, F, offset)
%simulate_signal.m Simulates signal fed into the LDA amplifier chain based
%on the output from the LDA
%   This function transforms the signal. It is fed with signal measured at
%   the end of the amplifier chain and transoforms it to the signal that was
%   fed into the amplifier chain.
% Inputs:
%   signal_in   : a vector, temporal signal measured at the end of the LDA amplifier chain
%   F           : a scalar, sampling frequency of the signal_in
% Outputs:
%   signal_out  : a vector, temporal signal fed into the LDA amplifier chain to produce signal_in

  %V_AMP = Voltage going in to the amplifier (differential):
  %1) Normalise to 16 bit resolution
  %2) Account for 2.5V ADC input range
  V_AMP = signal_in ./ (2^16) .* 2.5;

  %V_TP14 = Voltage at TP14:
  %1) Inverse the signal
  %2) Account for gain of IC9 amplifier (3.3/2)
  V_TP14 = 3.3 - V_AMP .* 2 ./ 3.3 ;

  %PDC = Voltage at PDC - simplified, assume just gain, no phase shift
  %Gain of 1.307 taken from LT spice simulation
  TF = create_TF();
  V_PDC = apply_TF(TF, F, V_TP14);

  V_PDC = V_PDC + ones(1,length(V_PDC)).*offset;

  signal_out = V_PDC;
  
  if any(signal_out > 5) || any(signal_out < -5)
    error("Signal out of range!")
  end
end
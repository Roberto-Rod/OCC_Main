function [out] = create_TF()
%create_TF Creates the Transfer Functions for LDA amplifier chain
%   Detailed explanation goes here

%Stage 1 - transimpedance amplifier
%Stage 2 - non-inverting amplifier
%Stage 3 - Butterworth filter (Sallen-Key topology) stage 1
%Stage 4 - Butterworth filter (Sallen-Key topology) stage 2

%Stage 4:
C23 = 27*10^(-12); %27pF
R16 = 18*10^(3); %18k
R17 = 18*10^(3); %18k
C22 = 68*10^(-12); %68pF

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

out = {H1_inv, H2_inv, H3_inv, H4_inv};

end
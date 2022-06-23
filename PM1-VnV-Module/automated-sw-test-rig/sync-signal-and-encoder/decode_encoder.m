function [position, direction] = decode_encoder(A, B)
%decode_encoder.m Decodes A/B encoder signals into position and direction
%   This file decodes encoder signals from channel A and channel B inot
%   position and direction.
% Inputs:
%   A           : a vector, represens channel A encoder signals
%   B           : a vector, represens channel B encoder signals
% Outputs:
%   position    : a vector, represens position decoded from the encoder signals
%   direction   : a vector, represens direction of motion decoded from the encoder signals

  position = zeros(1,length(A));
  direction = zeros(1,length(A));
  A = int8(A);
  B = int8(B);
  counter_lut = [
        %Direction = 1
        0, % 00 to 00
       -1, % 00 to 01
       +1, % 00 to 10
       +2, % 00 to 11

       +1, % 01 to 00
        0, % 01 to 01
       +2, % 01 to 10
       -1, % 01 to 11

       -1, % 10 to 00
       +2, % 10 to 01
        0, % 10 to 10
       +1, % 10 to 11

       +2, % 11 to 00
       +1, % 11 to 01
       -1, % 11 to 10
        0, % 11 to 11

        %Direction = 0
        0, % 00 to 00
       -1, % 00 to 01
       +1, % 00 to 10
       -2, % 00 to 11

       +1, % 01 to 00
        0, % 01 to 01
       -2, % 01 to 10
       -1, % 01 to 11

       -1, % 10 to 00
       -2, % 10 to 01
        0, % 10 to 10
       +1, % 10 to 11

       -2, % 11 to 00
       +1, % 11 to 01
       -1, % 11 to 10
        0, % 11 to 11
        ];
  lut_index = int8(0);
  for i=2:length(A)
    if A(i) ~= A(i-1) || B(i) ~= B(i-1)
       lut_index = bitor(lut_index, bitor(bitshift(A(i),1), B(i)));
       position(i) = position(i-1) + int16(counter_lut(lut_index+1));
 
       if counter_lut(lut_index+1) == 2
         disp("Encoder error!")
         %Test code
         %sta = max(i-50,1);
         %sto = min(i+50,length(A));
         %plot(sta:sto,A(sta:sto))
         %hold on
         %plot(sta:sto,B(sta:sto))
         %disp("Encoder error!")
       end
 
       if counter_lut(lut_index+1) == 0
         direction(i) = direction(i-1);
       else
         direction(i) = counter_lut(lut_index+1) > 0;
       end
       
       lut_index = bitor(bitand(bitshift(lut_index,2), int8(0b1100)), bitshift(direction(i),4));
     else
       position(i) = position(i-1);
       direction(i) = direction(i-1);
     end
  end
end

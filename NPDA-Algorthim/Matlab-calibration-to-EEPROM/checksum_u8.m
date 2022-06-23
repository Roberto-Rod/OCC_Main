function [chk] = checksum_u8(data, start_idx, end_idx)
%calculates checksum for uint8 array
%  = ~sum_mod_u8(data(start:len)
    
           sum = uint32(0);
           
           data_u8= uint8(data(:));
           
           if end_idx == -1
               
              end_idx = length(data_u8); 
               
           end 
          
           
           for i = start_idx:end_idx
               
               sum = uint32(data_u8(i)) + sum; 
               
           end
           
           chk = bitcmp(uint8(bitand (sum, uint32(0xff)))); 
           
           
end


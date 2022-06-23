require "rubyserial"

COM_FILE = "./Environment-Firmware.X/test/hw-test/com.txt"
if File.exists? COM_FILE 
    com_port = File.read COM_FILE
    response = `"#{ENV['XC16_PATH']}/bin/xc16-bin2hex" "./Environment-Firmware.X/ceedling-build/test/test-build.elf"`
    response = `"#{ENV['MPLAB_PATH']}/mplab_platform/mplab_ipe/ipecmd" -P24FJ64GA702 -TPICD4 -E`
    begin  
        my_serial = Serial.new(com_port, baude_rate = 115200, data_bits = 8)
    rescue StandardError => e  
        puts "Cannot open port #{com_port}"
    end  
    response = `"#{ENV['MPLAB_PATH']}/mplab_platform/mplab_ipe/ipecmd" -P24FJ64GA702 -TPICD4 -M -OV -F"./Environment-Firmware.X/ceedling-build/test/test-build.hex" -OL`
	start = Time.now
	data = ""
	while Time.now - start < 3
		data = data + my_serial.read(8192)
	end
    print data
    my_serial.close
    my_serial = nil
else
    puts "Cannot find file #{COM_FILE}"
end

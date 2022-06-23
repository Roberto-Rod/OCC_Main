# Running a compiled test test-build.elf within the embedded hardware
# NOTE:RZ: ipecmd.sh on Linux by default uses the current version (whatever installed) of Java, 
# but it only seems to support JVM 1.8 (8) so I had to modify it to point to the correct version.
# My version now looks like this:
#
# #!/bin/sh
# export here=`dirname $0`
# export mplabx_dir=$here/..
# export netbeans_dir=$mplabx_dir
# export ipecmd_jar=$mplabx_dir/mplab_ipe/ipecmd.jar
# # if you are using bash you can simply do:
# # source ../etc/mplab_ide.conf
# # the following line gets replaced during install
# #jdkhome="/path/to/jdk"

# # With current java
# #export jvm=$jdkhome/bin/java
# #$jvm -jar $ipecmd_jar $@

# # With java-8
# /usr/lib/jvm/java-1.8.0-openjdk-amd64/bin/java -jar $ipecmd_jar $@

require "rubyserial"

print "Running test...\n"
COM_FILE = "test/hw-test/com.txt"
if File.exists? COM_FILE 
    com_port = File.read COM_FILE

    print "Converting ELF to HEX...\n"
    response = `"#{ENV['XC32_PATH']}/bin/xc32-bin2hex" "./ceedling-build/test/test-build.elf"`

    if RUBY_PLATFORM =~ /linux/ then
        print "Erasing device platform LINUX...\n"
        response = `"#{ENV['MPLAB_PATH']}/mplab_platform/mplab_ipe/ipecmd.sh" -P32MZ2048EFH100 -TPICD4 -E`
    elsif RUBY_PLATFORM =~ /mswin32/ then
        print "Erasing device platform WINDOWS...\n"
        response = `"#{ENV['MPLAB_PATH']}/mplab_platform/mplab_ipe/ipecmd" -P32MZ2048EFH100 -TPICD4 -E`
    elsif RUBY_PLATFORM =~ /x64-mingw32/ then
        print "Programming device - platform MINGW32...\n"
        response = `"#{ENV['MPLAB_PATH']}/mplab_platform/mplab_ipe/ipecmd" -P32MZ2048EFH100 -TPICD4 -M -OV -F"./ceedling-build/test/test-build.hex" -OL`
    else
        puts "ERROR: Unknown platform #{RUBY_PLATFORM}"
    end

    print "Connecting serial port at ", com_port, "...\n"
    begin  
        my_serial = Serial.new(com_port, baude_rate = 115200, data_bits = 8)
    rescue StandardError => e  
        puts "ERROR: Cannot open port #{com_port}"
        puts "Code: #{e}"
    end

    if RUBY_PLATFORM =~ /linux/ then
        print "Programming device - platform LINUX...\n"
        response = `"#{ENV['MPLAB_PATH']}/mplab_platform/mplab_ipe/ipecmd.sh" -P32MZ2048EFH100 -TPICD4 -M -OV -F"./ceedling-build/test/test-build.hex" -OL`
    elsif RUBY_PLATFORM =~ /mswin32/ then
        print "Programming device - platform WINDOWS...\n"
        response = `"#{ENV['MPLAB_PATH']}/mplab_platform/mplab_ipe/ipecmd" -P32MZ2048EFH100 -TPICD4 -M -OV -F"./ceedling-build/test/test-build.hex" -OL`
    elsif RUBY_PLATFORM =~ /x64-mingw32/ then
        print "Programming device - platform MINGW32...\n"
        response = `"#{ENV['MPLAB_PATH']}/mplab_platform/mplab_ipe/ipecmd" -P32MZ2048EFH100 -TPICD4 -M -OV -F"./ceedling-build/test/test-build.hex" -OL`
    else
        puts "ERROR: Unknown platform #{RUBY_PLATFORM}"
    end

    print "Waiting for output...\n"
	start = Time.now
	data = ""
	while Time.now - start < 5
		data = data + my_serial.read(8192)
	end
    print "Test output -----\n"
    print data
    print "-----------------\n"
    my_serial.close
    my_serial = nil
else
    puts "Cannot find file #{COM_FILE}"
end





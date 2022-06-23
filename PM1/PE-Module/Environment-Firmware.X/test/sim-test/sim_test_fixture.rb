OUT_FILE = "Environment-Firmware.X/test/sim-test/out.txt"
File.delete OUT_FILE if File.exists? OUT_FILE 
response = `"#{ENV['MPLAB_PATH']}/mplab_platform/bin/mdb" Environment-Firmware.X/test/sim-test/mdb_instructions.txt`
sleep 1
if File.exists? OUT_FILE 
    file_contents = File.read OUT_FILE
    print file_contents
else
    puts "Cannot find file #{OUT_FILE}"
end

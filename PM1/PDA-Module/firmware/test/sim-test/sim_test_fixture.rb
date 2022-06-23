print "Running test...\n"

OUT_FILE = "test/sim-test/out.txt"
File.delete OUT_FILE if File.exists? OUT_FILE 
if RUBY_PLATFORM =~ /linux/ then
    print "Running code in simulator in linux...\n"
    response = `"#{ENV['MPLAB_PATH']}/mplab_platform/bin/mdb.sh" test/sim-test/mdb_instructions.txt`
elsif RUBY_PLATFORM =~ /mswin32/ then
    print "Running code in simulator in WINDOWS...\n"
    response = `"#{ENV['MPLAB_PATH']}/mplab_platform/bin/mdb.bat" test/sim-test/mdb_instructions.txt`
elsif RUBY_PLATFORM =~ /x64-mingw32/ then
    print "Running code in simulator in WINDOWS...\n"
    response = `"#{ENV['MPLAB_PATH']}/mplab_platform/bin/mdb.bat" test/sim-test/mdb_instructions.txt`
else
    puts "ERROR: Unknown platform #{RUBY_PLATFORM}"
end

sleep 1

if File.exists? OUT_FILE 
    file_contents = File.read OUT_FILE
    print "Test output -----\n"
    print file_contents
    print "-----------------\n"
else
    print "-----------------\n"
    puts "ERROR: Cannot find simulator output file #{OUT_FILE}"
    print "-----------------\n"
end

PROJECT_CEEDLING_ROOT = "vendor/ceedling"
load "#{PROJECT_CEEDLING_ROOT}/lib/ceedling/rakefile.rb"
puts "Project Ceedling root : #{PROJECT_CEEDLING_ROOT}"

task :default => %w[ test:all]

namespace :report do
  desc "Run gcov then lcov"
  task :coverage => [:generateCoverage] 
end

namespace :inject do
  desc "Inject version number from CI server"
  task :version => [:injectVersion]
end


task :generateCoverage do
  puts "test"
end

task :injectVersion do
  # puts get_tag_info("v0.09")
  puts injectVersionNumber()
end

namespace :test do
    desc "PicoOnboard unit test only"
    task :unit do
        task("test:path").invoke('unit_test')
    end

    desc "PicoOnboard acceptance test only"
    task :pico do
        task("test:pattern").invoke('HET')
    end
end

# Modify version.h file to inject CI build version number
# and Git tags information.
def injectVersionNumber
  jenkinsBuildId = ENV['BUILD_ID']
  gitInfo = get_tag_info()
  
  file_name = 'source/common/Version.h'

  text = File.read(file_name)
  new_contents = text.gsub(/<gitInfo>/, gitInfo)
  puts "Injecting Git info: #{gitInfo}"
    
  unless jenkinsBuildId.nil?
      new_contents = new_contents.gsub(/<buildId>/, jenkinsBuildId)
      puts "Injecting build id: #{jenkinsBuildId}"
  end

  # To merely print the contents of the file, use:
  #puts new_contents

  # To write changes to the file, use:
  File.open(file_name, "w") {|file| file.puts new_contents }
end

#modified from https://gist.github.com/whylom/1448530
def get_tag_info
  info = `git describe --tags`.chomp
  
  if info[/(.*)-(\d+)-g([a-z0-9]{7})/]
    matches = Regexp.last_match
    last_tag = matches[1]
    commits_since_tag = matches[2]
    noun = (commits_since_tag.to_i == 1) ? 'commit' : 'commits'
    #"#{last_tag}+#{commits_since_tag} #{noun}"
    "#{last_tag}+#{commits_since_tag}"
  else
    info
  end
end
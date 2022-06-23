PROJECT_CEEDLING_ROOT = "vendor/ceedling"
load "#{PROJECT_CEEDLING_ROOT}/lib/ceedling/rakefile.rb"

task :default => %w[ test:all]

namespace :report do
  desc "Run gcov then lcov"
  task :coverage => [:generateCoverage] 
end

task :generateCoverage do
    puts "test"
end

namespace :test do
    desc "PM1 unit test only"
    task :unit do
        task("test:path").invoke('unit_test')
    end

end
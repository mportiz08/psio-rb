require 'rake'
require 'rake/testtask'
require 'rake/clean'

desc 'Builds the psutil gem.'
task :build do
  sh 'gem build psutil.gemspec'
end

desc 'Installs the psutil gem.'
task :install => :build do
  sh 'gem install psutil-0.0.1.gem'
end

desc 'Open an irb session preloaded with psutil.'
task :console => :install do
  sh 'irb -I lib/ -r psutil'
end

task :default => :console

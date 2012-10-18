$:.unshift File.expand_path("../lib", __FILE__)
require 'rake'
require 'rake/testtask'
require 'rake/clean'
require 'psutil/version'

desc 'Builds the psutil gem.'
task :build do
  sh 'gem build psutil.gemspec'
end

desc 'Installs the psutil gem.'
task :install => :build do
  sh "gem install psutil-#{Psutil::VERSION}.gem"
end

desc 'Open an irb session preloaded with psutil.'
task :console => :install do
  sh 'irb -I lib/ -r psutil'
end

task :default => :console

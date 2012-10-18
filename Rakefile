$:.unshift File.expand_path('../lib', __FILE__)
require 'rake'
require 'rake/testtask'
require 'rake/clean'
require 'psio/version'

desc 'Builds the psio gem.'
task :build do
  sh 'gem build psio.gemspec'
end

desc 'Installs the psio gem.'
task :install => :build do
  sh "gem install psio-#{Psio::VERSION}.gem"
end

desc 'Open an irb session preloaded with psio.'
task :console => :install do
  sh 'irb -I lib/ -r psio'
end

task :default => :console

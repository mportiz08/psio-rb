$:.unshift File.expand_path('../lib', __FILE__)
require 'psio/version'

Gem::Specification.new do |s|
  s.name        = 'psio'
  s.version     = Psio::VERSION
  s.summary     = 'ruby library for system metrics'
  s.description = s.summary
  s.author      = 'Marcus Ortiz'
  s.email       = 'mportiz08@gmail.com'
  s.homepage    = 'https://github.com/mportiz08/psio'
  s.files       = Dir["README.md", "LICENSE.md", "lib/**/*.rb"] +
                  Dir['ext/**/*.{c,h,rb}']
  s.extensions  = ['ext/psio/extconf.rb']
end

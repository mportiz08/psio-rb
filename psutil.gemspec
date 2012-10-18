$:.unshift File.expand_path("../lib", __FILE__)
require 'psutil/version'

Gem::Specification.new do |s|
  s.name        = 'psutil'
  s.version     = Psutil::VERSION
  s.summary     = 'ruby bindings for the psutil library'
  s.description = s.summary
  s.author      = 'Marcus Ortiz'
  s.email       = 'mportiz08@gmail.com'
  s.homepage    = 'https://github.com/mportiz08/psutil'
  s.files       = Dir["README.md", "LICENSE.md", "lib/**/*.rb"] +
                  Dir['ext/**/*.{c,h,rb}']
  s.extensions  = ['ext/psutil/extconf.rb']
end

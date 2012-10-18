require 'mkmf'

ARCH        = RbConfig::CONFIG['arch']
# LIBDIR      = RbConfig::CONFIG['libdir']
# INCLUDEDIR  = RbConfig::CONFIG['includedir']

IS_OSX      = ARCH.include?('darwin')

# HEADER_DIRS = [
#   # First search /opt/local for macports
#   '/opt/local/include',
#   # Then search /usr/local for people that installed from source
#   '/usr/local/include',
#   # Check the ruby install locations
#   INCLUDEDIR,
#   # Finally fall back to /usr
#   '/usr/include',
# ]

# LIB_DIRS = [
#   # First search /opt/local for macports
#   '/opt/local/lib',
#   # Then search /usr/local for people that installed from source
#   '/usr/local/lib',
#   # Check the ruby install locations
#   LIBDIR,
#   # Finally fall back to /usr
#   '/usr/lib',
# ]

# dir_config('psio', HEADER_DIRS, LIB_DIRS)

# OSX_FRAMEWORKS = %w(CoreFoundation)

unless IS_OSX
  abort 'OSX is the only platform supported right now.'
end

# OSX_FRAMEWORKS.each do |fw|
#   unless have_framework(fw)
#     abort "A required framework (#{fw}) is missing."
#   end
# end

create_makefile('psio/psio')

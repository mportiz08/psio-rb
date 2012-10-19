require 'psio/psio'

require 'psio/version'
require 'psio/cpu'
require 'psio/process'

module Psio
  def self.processes_for_user(user)
    self.processes.select { |proc| proc.user == user }
  end
  
  def self.processes_for_current_user
    self.processes_for_user(ENV['USER'])
  end
end

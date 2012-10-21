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
  
  def self.process(pid)
    self.processes.detect { |p| p.pid == pid }
  end
  
  def self.processes_with_name(regexp)
    self.processes.reject { |p| p.name.match(regexp).nil? }
  end
end

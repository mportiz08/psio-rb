require 'ostruct'

module Psio
  class Process
    attr_reader :pid, :uid, :user, :status, :exe, :cpu_usage
    
    def name
      self.exe.split(/\//).last
    end
    
    def memory
      OpenStruct.new(@memory)
    end
  end
end

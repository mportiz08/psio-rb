module Psio
  class Process
    attr_reader :pid, :uid, :user, :status, :exe
    
    def name
      self.exe.split(/\//).last
    end
  end
end

# psio-rb

access process/cpu infomation with ruby

## usage

    require 'psio'

cpus

    >> c = Psio.cpus.first
    => #<Psio::Cpu:0x007fc8e195eb18 @user=10216.0, @nice=0.0, @system=8724.0, @idle=146967.0>
    >> c.user
    => 10216.0
    >> c.system
    => 8724.0
    >> c.idle
    => 146967.0
    >> c.nice
    => 0.0

processes

    >> p = Psio.processes.first
    => #<Psio::Process:0x007fc8e1807878 @pid=63608, @uid=501, @user="marcus", @exe="/Users/marcus/.rbenv/versions/1.9.3-p194/bin/ruby", @status="disk sleep", @cpu_usage=0.0, @memory={"virtual"=>1350869167, "resident"=>438707}>
    >> p.pid
    => 63608
    >> p.name
    => "ruby"
    >> p.uid
    => 501
    >> p.user
    => "marcus"
    >> p.exe
    => "/Users/marcus/.rbenv/versions/1.9.3-p194/bin/ruby"
    >> p.status
    => "disk sleep"
    >> p.cpu_usage
    => 0.0
    >> p.memory.virtual
    => 1350869167
    >> p.memory.resident
    => 438707

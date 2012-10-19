require 'psio'
require 'test/unit'

class PsioTest < Test::Unit::TestCase
  def test_cpus
    cpus = Psio.cpus
    
    assert_kind_of Array, cpus
    refute_empty cpus
    
    cpus.each { |cpu| assert_kind_of Psio::Cpu, cpu }
  end
  
  def test_processes
    procs = Psio.processes
    
    assert_kind_of Array, procs
    refute_empty procs
    
    procs.each { |p| assert_kind_of Psio::Process, p }
  end
end

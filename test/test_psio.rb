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
  
  def test_process_ruby
    this_proc = Psio.process($$)
    assert_not_nil this_proc
    assert_equal 'ruby', this_proc.name
  end
  
  def test_process_with_name
    procs = Psio.processes_with_name(/ruby/)
    
    assert_kind_of Array, procs
    refute_empty procs
    
    procs.each { |p| assert_not_nil p.name.match(/ruby/) }
  end
end

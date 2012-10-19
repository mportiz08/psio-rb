#include <psio.h>

VALUE mPsio;

void
Init_psio(void)
{
  mPsio = rb_define_module("Psio");
  rb_define_singleton_method(mPsio, "cpus", psio_cpus, 0);
}

static VALUE
psio_cpus(void)
{
  int i;
  VALUE ret;
  natural_t cpu_count;
  processor_info_array_t info_array;
  mach_msg_type_number_t info_count;
  kern_return_t error;
  processor_cpu_load_info_data_t* cpu_load_info = NULL;
  
  error = host_processor_info(mach_host_self(), PROCESSOR_CPU_LOAD_INFO,
                              &cpu_count, &info_array, &info_count);
  if(error != KERN_SUCCESS) {
    fprintf(stderr, "something bad happened");
  }
  cpu_load_info = (processor_cpu_load_info_data_t *)info_array;
  
  ret = rb_ary_new();
  for(i = 0; i < cpu_count; i++) {
    rb_ary_push(ret, psio_cpu_new(cpu_load_info[i]));
  }
  
  return ret;
}

static VALUE
psio_cpu_new(processor_cpu_load_info_data_t cpu_load_info)
{
  VALUE cCpu, cpu;
  float tmp_time;
  
  cCpu = rb_const_get(mPsio, rb_intern("Cpu"));
  cpu  = rb_class_new_instance(0, NULL, cCpu);
  
  tmp_time = cpu_load_info.cpu_ticks[CPU_STATE_USER] / CLK_TCK;
  rb_iv_set(cpu, "@user", rb_float_new(tmp_time));
  
  tmp_time = cpu_load_info.cpu_ticks[CPU_STATE_NICE] / CLK_TCK;
  rb_iv_set(cpu, "@nice", rb_float_new(tmp_time));
  
  tmp_time = cpu_load_info.cpu_ticks[CPU_STATE_SYSTEM] / CLK_TCK;
  rb_iv_set(cpu, "@system", rb_float_new(tmp_time));
  
  tmp_time = cpu_load_info.cpu_ticks[CPU_STATE_IDLE] / CLK_TCK;
  rb_iv_set(cpu, "@idle", rb_float_new(tmp_time));
  
  return cpu;
}

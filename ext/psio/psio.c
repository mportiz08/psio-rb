#include <psio.h>

VALUE mPsio;

void
Init_psio(void)
{
  mPsio = rb_define_module("Psio");
  rb_define_singleton_method(mPsio, "cpus", psio_cpus, 0);
  rb_define_singleton_method(mPsio, "processes", psio_processes, 0);
}

static VALUE
psio_cpus(void)
{
  unsigned int i;
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
    return Qnil;
  }
  cpu_load_info = (processor_cpu_load_info_data_t *)info_array;
  
  ret = rb_ary_new();
  for(i = 0; i < cpu_count; i++) {
    rb_ary_push(ret, psio_cpu_new(cpu_load_info[i]));
  }
  
  return ret;
}

static VALUE
psio_processes(void)
{
  static const int mib3[3] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL };
  size_t size, num_procs;
  void *data;
  kinfo_proc_t *procs, *tmp_procs;
  VALUE proc_ary;
  unsigned int i;
  
  // call sysctl first to get required size for buffer
  size = 0;
  if(sysctl((int *)mib3, 3, NULL, &size, NULL, 0) == -1) {
    fprintf(stderr, "something bad happened");
    return Qnil;
  }
  num_procs = size / sizeof(kinfo_proc_t);
  data      = malloc(size);
  
  // call sysctl again to get procs data
  if(sysctl((int *)mib3, 3, data, &size, NULL, 0) == -1) {
    fprintf(stderr, "something bad happened");
    free(data);
    return Qnil;
  }
  procs = (kinfo_proc_t *)data;
  
  tmp_procs = procs;
  proc_ary = rb_ary_new();
  for(i = 0; i < num_procs; i++) {
    rb_ary_push(proc_ary, psio_process_new(tmp_procs));
    tmp_procs++;
  }
  free(procs);
  
  return proc_ary;
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

static VALUE
psio_process_new(kinfo_proc_t *proc_info)
{
  VALUE cProcess, proc, status;
  uid_t uid;
  char *user, *name;
  
  cProcess = rb_const_get(mPsio, rb_intern("Process"));
  proc     = rb_class_new_instance(0, NULL, cProcess);
  
  rb_iv_set(proc, "@pid", INT2FIX((*proc_info).kp_proc.p_pid));
  
  uid  = (*proc_info).kp_eproc.e_pcred.p_ruid;
  user = user_from_uid(uid, 0);
  rb_iv_set(proc, "@uid", INT2FIX(uid));
  rb_iv_set(proc, "@user", rb_str_new_cstr(user));
  
  status = psio_status_str_from_code((*proc_info).kp_proc.p_stat);
  rb_iv_set(proc, "@status", status);
  
  name = (*proc_info).kp_proc.p_comm;
  rb_iv_set(proc, "@name", rb_str_new_cstr(name));
  
  return proc;
}

static VALUE
psio_status_str_from_code(char code)
{
  VALUE ret = rb_str_new_cstr("?");
  
  switch((int)code) {
    case 0:
      ret = rb_str_new_cstr("running");
      break;
    case 1:
      ret = rb_str_new_cstr("sleeping");
      break;
    case 2:
      ret = rb_str_new_cstr("disk sleep");
      break;
    case 3:
      ret = rb_str_new_cstr("stopped");
      break;
    case 4:
      ret = rb_str_new_cstr("tracing stop");
      break;
    case 5:
      ret = rb_str_new_cstr("zombie");
      break;
    case 6:
      ret = rb_str_new_cstr("dead");
      break;
    case 7:
      ret = rb_str_new_cstr("wake kill");
      break;
    case 8:
      ret = rb_str_new_cstr("waking");
      break;
    case 9:
      ret = rb_str_new_cstr("idle");
      break;
    case 10:
      ret = rb_str_new_cstr("locked");
      break;
    case 11:
      ret = rb_str_new_cstr("waiting");
      break;
  }
  
  return ret;
}

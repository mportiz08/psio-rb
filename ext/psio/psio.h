#ifndef RUBY_PSIO
#define RUBY_PSIO

#include <ruby.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/sysctl.h>

#include <mach/mach.h>
#include <mach/task.h>
#include <mach/mach_init.h>
#include <mach/host_info.h>
#include <mach/mach_host.h>
#include <mach/mach_traps.h>
#include <mach/mach_vm.h>
#include <mach/shared_region.h>

typedef struct kinfo_proc kinfo_proc_t;

extern VALUE mPsio;

void         Init_psio(void);
static VALUE psio_cpus(void);
static VALUE psio_processes(void);

static VALUE psio_cpu_new(processor_cpu_load_info_data_t cpu_load_info);
static VALUE psio_process_new(kinfo_proc_t *proc);
static VALUE psio_status_str_from_code(char code);

#endif

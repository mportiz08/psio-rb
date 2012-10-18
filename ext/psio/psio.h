#ifndef RUBY_PSIO
#define RUBY_PSIO

#include <ruby.h>
#include <sys/sysctl.h>

#include <psio_cpu.h>

extern VALUE mPsio;

void Init_psio(void);

#endif

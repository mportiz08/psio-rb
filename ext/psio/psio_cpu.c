#include <psio_cpu.h>

void
Init_psio_cpu(void)
{
  VALUE cPsioCpu = rb_define_class_under(mPsio, "Cpu", rb_cObject);
}

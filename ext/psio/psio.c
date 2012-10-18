#include <psio.h>

VALUE mPsio;

void
Init_psio(void)
{
  mPsio = rb_define_module("Psio");
  Init_psio_cpu();
}

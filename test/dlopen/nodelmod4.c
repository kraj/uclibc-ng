extern int fini_ran;

int var_in_mod4 = 99;

static void
__attribute__ ((__destructor__))
destr (void)
{
  fini_ran = 1;
}

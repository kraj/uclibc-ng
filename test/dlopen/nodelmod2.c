extern int fini_ran;

int var2 = 100;

static void
__attribute__ ((__destructor__))
destr (void)
{
  fini_ran = 1;
}

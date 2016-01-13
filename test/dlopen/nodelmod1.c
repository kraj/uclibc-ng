extern int fini_ran;

int var1 = 42;

static void
__attribute__ ((__destructor__))
destr (void)
{
  fini_ran = 1;
}

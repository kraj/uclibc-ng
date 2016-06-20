#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>


int fini_ran;

#define LIBNAME1	"nodelmod1.so"

static int
do_test (void)
{
  /* Verify ability to reload RTLD_NODELETE libraries.
   */
  void *p;

  p = dlopen (LIBNAME1, RTLD_NOW);
  if (p == NULL)
  {
      printf ("failed to load "LIBNAME1": %s\n", dlerror ());
      exit (1);
  }

  if (dlclose (p) != 0)
  {
      puts ("failed to close "LIBNAME1"");
      exit (1);
  }

  p = dlopen (LIBNAME1, RTLD_LAZY);
  if (p == NULL)
  {
      printf ("failed to load "LIBNAME1": %s\n", dlerror ());
      exit (1);
  }

  if (dlclose (p) != 0)
  {
      puts ("failed to close "LIBNAME1"");
      exit (1);
  }

  p = dlopen ("nodelmod2.so", RTLD_LAZY);
  if (p == NULL)
  {
      printf ("failed to load \"nodelmod2.so\": %s\n", dlerror ());
      exit (1);
  }
  if (dlclose (p) != 0)
  {
      puts ("failed to close \"nodelmod2.so\"");
      exit (1);
  }

  return 0;
}

#define TEST_FUNCTION do_test ()
#include "../test-skeleton.c"

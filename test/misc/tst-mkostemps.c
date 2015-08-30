/*
 * Test application for mkstemp/mkstemps/mkostemp/mkostemps
 * Copyright (C) 2015 by Romain Naour <romain.naour@openwide.fr>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define assert(x) \
  if (!(x)) \
    { \
      fputs ("test failed: " #x "\n", stderr); \
      retval = 1; \
      goto the_end; \
    }

int
main (int argc, char *argv[])
{
  char name[256];
  char name_suffix[256];
  FILE *fp = NULL;
  int retval = 0;
  int fd;
  int flags = O_RDONLY | O_CLOEXEC;
  struct stat sb_f1;
  struct stat sb_f2;

  /* mkstemp test */
  sprintf(name, "/tmp/%s-uClibc-test.XXXXXX", __FILE__);

  fd = mkstemp(name);

  fstat(fd, &sb_f1);
  assert ((sb_f1.st_mode & S_IFMT) == S_IFREG)

  stat(name, &sb_f2);
  assert ((sb_f2.st_mode & S_IFMT) == S_IFREG)

  assert (sb_f1.st_ino == sb_f2.st_ino)

  close(fd);
  unlink (name);

  /* mkstemps test */
  sprintf(name_suffix, "/tmp/%s-uClibc-test.XXXXXX.txt", __FILE__);

  fd = mkstemps(name_suffix, 4);

  fstat(fd, &sb_f1);
  assert ((sb_f1.st_mode & S_IFMT) == S_IFREG)

  stat(name_suffix, &sb_f2);
  assert ((sb_f2.st_mode & S_IFMT) == S_IFREG)

  assert (sb_f1.st_ino == sb_f2.st_ino)

  close(fd);
  unlink (name_suffix);

  /* mkostemp test */
  sprintf(name, "/tmp/%s-uClibc-test.XXXXXX", __FILE__);

  fd = mkostemp(name, flags);

  fstat(fd, &sb_f1);
  assert ((sb_f1.st_mode & S_IFMT) == S_IFREG)

  stat(name, &sb_f2);
  assert ((sb_f2.st_mode & S_IFMT) == S_IFREG)

  assert (sb_f1.st_ino == sb_f2.st_ino)
  assert (sb_f1.st_mode == sb_f2.st_mode)

  close(fd);
  unlink (name);

  /* mkostemps test */
  sprintf(name_suffix, "/tmp/%s-uClibc-test.XXXXXX.txt", __FILE__);

  fd = mkostemps(name_suffix, 4, flags);

  fstat(fd, &sb_f1);
  assert ((sb_f1.st_mode & S_IFMT) == S_IFREG)

  stat(name_suffix, &sb_f2);
  assert ((sb_f2.st_mode & S_IFMT) == S_IFREG)

  assert (sb_f1.st_ino == sb_f2.st_ino)
  assert (sb_f1.st_mode == sb_f2.st_mode)

  close(fd);
  unlink (name_suffix);

  /* suffixlen = 0 */
  sprintf(name_suffix, "/tmp/%s-uClibc-test.XXXXXX", __FILE__);

  fd = mkostemps(name_suffix, 0, flags);

  fstat(fd, &sb_f1);
  assert ((sb_f1.st_mode & S_IFMT) == S_IFREG)

  stat(name_suffix, &sb_f2);
  assert ((sb_f2.st_mode & S_IFMT) == S_IFREG)

  assert (sb_f1.st_ino == sb_f2.st_ino)
  assert (sb_f1.st_mode == sb_f2.st_mode)

  close(fd);
  unlink (name_suffix);

  /* stress tests */

  /* template len < 6 */
  sprintf(name, "XXXXX");

  fd = mkstemp(name);

  assert(fd == -1);
  assert(errno == EINVAL);

  /* suffixlen < 0 */
  sprintf(name_suffix, "/tmp/%s-uClibc-test.XXXXXX.txt", __FILE__);

  fd = mkostemps(name_suffix, -1, flags);

  assert(fd == -1);
  assert(errno == EINVAL);

  /* Missing one X */
  sprintf(name_suffix, "/tmp/%s-uClibc-test.XXXXX.txt", __FILE__);

  fd = mkostemps(name_suffix, 4, flags);

  assert(fd == -1);
  assert(errno == EINVAL);

  /* wrong suffixlen */
  sprintf(name_suffix, "/tmp/%s-uClibc-test.XXXXXX.txt", __FILE__);

  fd = mkostemps(name_suffix, 2, flags);

  assert(fd == -1);
  assert(errno == EINVAL);

the_end:
  if (fp != NULL)
    assert (fclose (fp) == 0);
  unlink (name);
  unlink (name_suffix);

  return retval;
}

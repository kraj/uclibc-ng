/*
 * getrlimit() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <sys/resource.h>
#include <bits/wordsize.h>
#include <stddef.h> // needed for NULL to be defined

/* Only wrap getrlimit if the new ugetrlimit is not present and getrlimit sucks */

#if defined(__NR_ugetrlimit)

/* just call ugetrlimit() */
# define __NR___syscall_ugetrlimit __NR_ugetrlimit
static __always_inline
_syscall2(int, __syscall_ugetrlimit, enum __rlimit_resource, resource,
          struct rlimit *, rlim)
int getrlimit(__rlimit_resource_t resource, struct rlimit *rlimits)
{
	return __syscall_ugetrlimit(resource, rlimits);
}

#else

# if !defined(__UCLIBC_HANDLE_OLDER_RLIMIT__)

#  if defined(__NR_prlimit64)
int getrlimit(__rlimit_resource_t resource, struct rlimit *rlimits)
{
	return INLINE_SYSCALL (prlimit64, 4, 0, resource, NULL, rlimits);
}
#  else
/* We don't need to wrap getrlimit() */
_syscall2(int, getrlimit, __rlimit_resource_t, resource,
	  struct rlimit *, rlim)
#  endif

# else

/* we have to handle old style getrlimit() */
#  define __NR___syscall_getrlimit __NR_getrlimit
static __always_inline
_syscall2(int, __syscall_getrlimit, int, resource, struct rlimit *, rlim)

int getrlimit(__rlimit_resource_t resource, struct rlimit *rlimits)
{
	int result;

#  if defined(__NR_prlimit64)
	result = INLINE_SYSCALL (prlimit64, 4, 0, resource, NULL, rlimits);
#  else
	result = __syscall_getrlimit(resource, rlimits);
#  endif

	if (result == -1)
		return result;

	/* We might have to correct the limits values.  Since the old values
	 * were signed the infinity value is too small.  */
	if (rlimits->rlim_cur == RLIM_INFINITY >> 1)
		rlimits->rlim_cur = RLIM_INFINITY;
	if (rlimits->rlim_max == RLIM_INFINITY >> 1)
		rlimits->rlim_max = RLIM_INFINITY;
	return result;
}
# endif
#endif
libc_hidden_def(getrlimit)

#if __WORDSIZE == 64
strong_alias_untyped(getrlimit, getrlimit64)
#endif

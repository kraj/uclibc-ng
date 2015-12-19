/* Copyright (C) 1996-1998,2001,2002,2003,2006 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1996.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <features.h>

#ifdef __USE_XOPEN2K

#include <sys/syscall.h>
#include <sys/select.h>
#include <sys/time.h>
#include <signal.h>
#include <cancel.h>

static int __NC(pselect)(int nfds, fd_set *readfds, fd_set *writefds,
			 fd_set *exceptfds, const struct timespec *timeout,
			 const sigset_t *sigmask)
{
#ifdef __NR_pselect6
#define NSEC_PER_SEC 1000000000L
	struct timespec _ts, *ts = 0;
	if (timeout) {
		/* The Linux kernel can in some situations update the timeout value.
		 * We do not want that so use a local variable.
		 */
		_ts = *timeout;

		/* GNU extension: allow for timespec values where the sub-sec
		* field is equal to or more than 1 second.  The kernel will
		* reject this on us, so take care of the time shift ourself.
		* Some applications (like readline and linphone) do this.
		* See 'clarification on select() type calls and invalid timeouts'
		* on the POSIX general list for more information.
		*/
		if (_ts.tv_nsec >= NSEC_PER_SEC) {
			_ts.tv_sec += _ts.tv_nsec / NSEC_PER_SEC;
			_ts.tv_nsec %= NSEC_PER_SEC;
		}

		ts = &_ts;
	}

	/* The pselect6 syscall API is strange. It wants a 7th arg to be
	 * the sizeof(*sigmask). However syscalls with > 6 arguments aren't
	 * supported on linux. So arguments 6 and 7 are stuffed in a struct
	 * and a pointer to that struct is passed as the 6th argument to
	 * the syscall.
	 * Glibc stuffs arguments 6 and 7 in a ulong[2]. Linux reads
	 * them as if there were a struct { sigset_t*; size_t } in
	 * userspace. There woudl be trouble if userspace and the kernel are
	 * compiled differently enough that size_t isn't the same as ulong,
	 * but not enough to trigger the compat layer in linux. I can't
	 * think of such a case, so I'm using linux's struct.
	 * Furthermore Glibc sets the sigsetsize to _NSIG/8. However linux
	 * checks for sizeof(sigset_t), which internally is a ulong array.
	 * This means that if _NSIG isn't a multiple of BITS_PER_LONG then
	 * linux will refuse glibc's value. So I prefer sizeof(sigset_t) for
	 * the value of sigsetsize.
	 */
	struct {
		const sigset_t *sigmask;
		size_t sigsetsize;
	} args67 = {
		sigmask,
		sizeof(sigset_t),
	};

	return INLINE_SYSCALL(pselect6, 6, nfds, readfds, writefds, exceptfds, ts, &args67);
#else
	struct timeval tval;
	int retval;
	sigset_t savemask;

	/* Change nanosecond number to microseconds.  This might mean losing
	   precision and therefore the `pselect` should be available.  But
	   for now it is hardly found.  */
	if (timeout != NULL)
		TIMESPEC_TO_TIMEVAL (&tval, timeout);

	/* The setting and restoring of the signal mask and the select call
	   should be an atomic operation.  This can't be done without kernel
	   help.  */
	if (sigmask != NULL)
		sigprocmask (SIG_SETMASK, sigmask, &savemask);

	/* The comment below does not apply on uClibc, since we use __select_nocancel */
	/* Note the pselect() is a cancellation point.  But since we call
	   select() which itself is a cancellation point we do not have
	   to do anything here.  */
	retval = __NC(select)(nfds, readfds, writefds, exceptfds,
			timeout != NULL ? &tval : NULL);

	if (sigmask != NULL)
		sigprocmask (SIG_SETMASK, &savemask, NULL);

	return retval;
#endif
}
CANCELLABLE_SYSCALL(int, pselect, (int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
				   const struct timespec *timeout, const sigset_t *sigmask),
		    (nfds, readfds, writefds, exceptfds, timeout, sigmask))

#endif

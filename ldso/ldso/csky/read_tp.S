#include <sysdep.h>

#ifndef NOT_IN_libc
.global __read_tp
#else
.hidden __read_tp
#endif

ENTRY (__read_tp)
#ifdef __CSKYABIV2__
	mov	a0, tls
#else
	trap 3
#endif
	rts
END (__read_tp)


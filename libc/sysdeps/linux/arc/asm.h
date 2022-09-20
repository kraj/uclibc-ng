/*
 * Copyright (C) 2022, Synopsys, Inc. (www.synopsys.com)
 *
 * Licensed under the LGPL v2.1 or later, see the file COPYING.LIB in this tarball.
 */

#ifndef _ARC_ASM_H
#define _ARC_ASM_H

#if defined (__ARC64_ARCH32__)

.macro PUSHR reg
	push	\reg
.endm

.macro PUSHR_S reg
	push	\reg
.endm

.macro POPR reg
	pop	\reg
.endm

.macro POPR_S reg
	pop	\reg
.endm

#elif defined (__ARC64_ARCH64__)

# error ARCv3 64-bit is not supported by uClibc-ng

#else /* ARCHS || ARC700 */

.macro PUSHR reg
	push	\reg
.endm

.macro PUSHR_S reg
	push_s	\reg
.endm

.macro POPR reg
	pop	\reg
.endm

.macro POPR_S reg
	pop_s	\reg
.endm

#endif

#endif /* _ARC_ASM_H  */

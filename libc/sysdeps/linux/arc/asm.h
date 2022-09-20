/*
 * Copyright (C) 2022, Synopsys, Inc. (www.synopsys.com)
 *
 * Licensed under the LGPL v2.1 or later, see the file COPYING.LIB in this tarball.
 */

#ifndef _ARC_ASM_H
#define _ARC_ASM_H


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


#endif /* _ARC_ASM_H  */

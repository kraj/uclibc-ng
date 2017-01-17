/*
 * Copyright (C) 2016-2017 Andes Technology, Inc.
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

/* Copyright (C) 2013 Free Software Foundation, Inc.

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

#include <tls.h>

/* Save the PID value.  */
#define SAVE_PID \
	lwi  	$r1, [$r25 + PID_OFFSET];/* Get the thread pointer.  */	\
	subri	$r1, $r1, 0x0;		 /* Negate it.  */		\
	bnez	$r1, 1f;		 /* If it was zero... */		\
	sethi	$r1, 0x80000;		 /* use 0x80000000 instead.  */	\
1:	swi	$r1, [$r25 + PID_OFFSET];/* Store the temporary PID.  */

/* Restore the old PID value in the parent.  */
#define RESTORE_PID \
	beqz	$r0, 1f;		/* If we are the parent... */	\
	lwi  	$r1, [$r25 + PID_OFFSET];/* Get the thread pointer.  */	\
	subri	$r1, $r1, 0x0;		/* Re-negate it.  */		\
	sethi	$r2, 0x80000;		/* Load 0x80000000... */	\
	bne	$r1, $r2, 2f;		/* ... compare against it... */	\
	movi	$r1, 0;			/* ... use 0 instead.  */	\
2:	swi	$r1, [$r25 + PID_OFFSET];/* Restore the PID.  */		\
1:

#include <../../../../../../../libc/sysdeps/linux/nds32/vfork.S>

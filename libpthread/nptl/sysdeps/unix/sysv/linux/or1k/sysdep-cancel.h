/* Copyright (C) 2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#include <sysdep.h>
#include <tls.h>
#ifndef __ASSEMBLER__
# include <pthreadP.h>
#endif

#if !defined NOT_IN_libc || defined IS_IN_libpthread || defined IS_IN_librt

# undef PSEUDO
# define PSEUDO(name, syscall_name, args)                                     \
ENTRY(__##syscall_name##_nocancel);                                           \
L(pseudo_nocancel):                                                           \
  DO_CALL(syscall_name);                                                      \
  l.j     L(pseudo_finish);                                                   \
   l.nop;                                                                     \
END(__##syscall_name##_nocancel);                                             \
ENTRY(name);                                                                  \
  SINGLE_THREAD_P(r13);                                                       \
  l.sfeq  r13,r0;                                                             \
  l.bnf   L(pseudo_nocancel);                                                 \
   l.nop;                                                                     \
  /* Reserve the same amount of stack space, effectivly disregarding          \
   * how many args we're supposed to push. This makes the code easier. */     \
  l.addi  r1,r1,-28;                                                          \
  cfi_adjust_cfa_offset(28);                                                  \
  PUSHARGS_##args; /* CENABLE is a function call, save args for syscall. */   \
  CENABLE;                                                                    \
  l.sw    24(r1),r11;                                                         \
  POPARGS_##args;                                                             \
  DO_CALL(syscall_name);                                                      \
  l.lwz   r3,24(r1); /* pass return value from CENABLE to CDISABLE. */        \
  l.sw    24(r1),r11; /* save syscall return value for after CDISABLE. */     \
  CDISABLE;                                                                   \
  l.lwz   r11,24(r1); /* restore syscall return value. */                     \
  cfi_adjust_cfa_offset(-28);                                                 \
  l.addi  r1,r1,28;                                                           \
L(pseudo_finish):                                                             \
  /* if -4096 < ret < 0 holds, it's an error */                               \
  l.sfgeui r11,0xf001;                                                        \
  l.bf    L(pseudo_end);                                                      \
   l.nop

# undef PSEUDO_END
# define PSEUDO_END(name) \
L(pseudo_end): \
  l.j SYSCALL_ERROR_NAME; \
  l.ori r3,r11,0; \
  END(name)

# define PUSHARGS_0     /* nothing to do */
# define PUSHARGS_1     PUSHARGS_0 l.sw   0(r1),r3;
# define PUSHARGS_2     PUSHARGS_1 l.sw   4(r1),r4;
# define PUSHARGS_3     PUSHARGS_2 l.sw   8(r1),r5;
# define PUSHARGS_4     PUSHARGS_3 l.sw   12(r1),r6;
# define PUSHARGS_5     PUSHARGS_4 l.sw   16(r1),r7;
# define PUSHARGS_6     PUSHARGS_5 l.sw   20(r1),r8;

# define POPARGS_0      /* nothing to do */
# define POPARGS_1      POPARGS_0 l.lwz   r3,0(r1);
# define POPARGS_2      POPARGS_1 l.lwz   r4,4(r1);
# define POPARGS_3      POPARGS_2 l.lwz   r5,8(r1);
# define POPARGS_4      POPARGS_3 l.lwz   r6,12(r1);
# define POPARGS_5      POPARGS_4 l.lwz   r7,16(r1);
# define POPARGS_6      POPARGS_5 l.lwz   r8,20(r1);

# define PSEUDO_JMP(sym) l.jal sym; l.nop;

# ifdef IS_IN_libpthread
#  define CENABLE       PSEUDO_JMP (__pthread_enable_asynccancel)
#  define CDISABLE      PSEUDO_JMP (__pthread_disable_asynccancel)
# elif defined IS_IN_librt
#  define CENABLE       PSEUDO_JMP (__librt_enable_asynccancel)
#  define CDISABLE      PSEUDO_JMP (__librt_disable_asynccancel)
# else
#  define CENABLE       PSEUDO_JMP (__libc_enable_asynccancel)
#  define CDISABLE      PSEUDO_JMP (__libc_disable_asynccancel)
# endif

# ifndef __ASSEMBLER__
#  define SINGLE_THREAD_P \
  __builtin_expect (THREAD_GETMEM (THREAD_SELF, \
                                   header.multiple_threads) == 0, 1)
# else
/* It's not super nice to have "r10" hardcoded here */
#  define SINGLE_THREAD_P(reg) l.lwz reg, MULTIPLE_THREADS_OFFSET(r10)
#endif

#elif !defined __ASSEMBLER__

# define SINGLE_THREAD_P 1
# define NO_CANCELLATION 1

#endif

#ifndef __ASSEMBLER__
# define RTLD_SINGLE_THREAD_P \
  __builtin_expect (THREAD_GETMEM (THREAD_SELF, \
                                   header.multiple_threads) == 0, 1)
#endif

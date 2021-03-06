/* Return current rounding direction.
   Copyright (C) 1997-2017 Free Software Foundation, Inc.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

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

#include <fenv.h>

int
fegetround (void)
{
  int cw;
  /* We only check the x87 FPU unit.  The SSE unit should be the same
     - and if it's not the same there's no way to signal it.  */

  __asm__ ("fnstcw %0" : "=m" (*&cw));

  return cw & 0xc00;
}

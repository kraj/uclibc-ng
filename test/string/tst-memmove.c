/*
 * Copyright (C) 2016 Rene Nielsen <rene.nielsen@microsemi.com>
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <string.h>
#include <stdio.h>

#define LEN 1024

int main(int argc, char *argv[])
{
    unsigned char a[LEN], exp;
    int i, move_len, move_src, err = 0;

    // Fill the array with increasing values from 0 to LEN - 1 (wrap is fine)
    for (i = 0; i < LEN; i++) {
        a[i] = i;
    }

    // move_src is the index into the array to move from.
    // move_len is the number of indices to move. Here, we take the remainder.
    move_src = LEN / 64;
    move_len = LEN - move_src;

    printf("Moving %d entries from index %d to 0\n", move_len, move_src);
    memmove(a, &a[move_src], sizeof(a[0]) * move_len);

    // Check that the memmove went well
    for (i = 0; i < LEN; i++) {
        // Expect that the first #move_len entries contain increasing values
        // starting at #move_src and the last #move_src entries are untouched.
        exp = i >= move_len ? i : i + move_src;
        if (a[i] != exp) {
            printf("Error: memmove() failed. Expected a[%d] = %u, got %u\n", i, exp, a[i]);
            err = 1;
        }
    }

    if (!err) {
       printf("memmove() succeeded\n");
    }

    return err;
}


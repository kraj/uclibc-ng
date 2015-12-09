#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char *text_input = "1 23 43";

static const char *good_answer = "1 529 1849 ";


static int
do_test (void)
{
    FILE *out, *in;
    int v, s;
    size_t size;
    char *ptr;

    in = fmemopen(text_input, strlen(text_input), "r");
    if (in == NULL) {
        perror("fmemopen");
	return 1;
    }

    out = open_memstream(&ptr, &size);
    if (out == NULL) {
        perror("open_memstream");
	return 1;
    }

    for (;;) {
        s = fscanf(in, "%d", &v);
        if (s <= 0)
            break;

        s = fprintf(out, "%d ", v * v);
        if (s == -1) {
            puts("fprintf failed");
	    exit(1);
	}
    }
    fclose(in);
    fclose(out);

    if (size != strlen(good_answer) || strcmp(good_answer, ptr) != 0) {
	printf("failed: size=%zu; ptr=%s\n", size, ptr);
	exit(1);
    }
    free(ptr);
    exit(0);
}

#define TEST_FUNCTION do_test ()
#include "../test-skeleton.c"

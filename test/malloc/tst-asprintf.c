#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

static void my_stats(void)
{
	malloc_stats();
	fprintf(stderr, "\n");
}

int main(int argc, char *argv[])
{
	char *a, *b;

	my_stats();
	asprintf(&b, "asdsadasd %ssdf\n", "AAAA");
	my_stats();
	asprintf(&a, "asdsadasd %ssdf\n", "AAAA");
	my_stats();
	free(a);
	free(b);
	my_stats();

	return 0;
}

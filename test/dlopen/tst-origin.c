#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

#ifdef __UCLIBC__
extern void _dlinfo(void);
#endif

int main(int argc, char **argv) {
	void *h1, *h2;
	int __attribute__((unused))(*mydltest)(const char *s);
	char *error;

	h1 = dlopen ("libtest31.so", RTLD_LAZY);
	if (!h1) {
		fprintf(stderr, "Could not open libtest31.so: %s\n", dlerror());
		exit(1);
	}

	h2 = dlopen ("libtest31.so", RTLD_NOLOAD);
	if (!h2) {
		fprintf(stderr, "Could not open libtest31.so(RTLD_NOLOAD): %s\n", dlerror());
		exit(1);
	}

	mydltest = dlsym(h1, "dltest");
	if ((error = dlerror()) != NULL)  {
		fprintf(stderr, "Could not locate symbol 'dltest': %s\n", error);
		exit(1);
	}

	dlclose(h2);
	dlclose(h1);

	return EXIT_SUCCESS;
}

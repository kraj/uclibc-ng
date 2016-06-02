#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	const char *buf = "hello world";
	char *ps = NULL, *pc = NULL, *ps2 = NULL;
	char s[6], c, s2[5];

	/* Check that %[...]/%c/%s work. */
	sscanf(buf, "%[a-z] %c %s", s, &c, s2);
	/* Check that %m[...]/%mc/%ms work. */
	sscanf(buf, "%m[a-z] %mc %ms", &ps, &pc, &ps2);

	if (strcmp(ps, "hello") != 0 || *pc != 'w' ||
	    strcmp(ps2, "orld") != 0 ||
	    strcmp(s, "hello") != 0 || c != 'w' ||
	    strcmp(s2, "orld") != 0)
		return 1;

	free(ps);
	free(pc);
	free(ps2);

	return 0;
}

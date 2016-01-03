#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>

int main(int argc, char *argv[])
{
    void *h;
    pid_t pid;

    h = dlopen("libatfork.so", RTLD_NOW);
    if (!h)
    {
        printf("Failed to open libatfork.so\n");
        return 1;
    }
    dlclose(h);

    if ((pid = fork()) < 0) {
	printf("Fork failed\n");
        return 1;
    }

    return 0;
}

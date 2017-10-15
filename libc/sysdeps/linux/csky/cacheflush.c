#include <sys/syscall.h>
_syscall3(int, cacheflush, void *, addr, int, nbytes, int, op)

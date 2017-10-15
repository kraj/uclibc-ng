#ifndef _SYS_CACHECTL_H
#define _SYS_CACHECTL_H	1

#include <asm/cachectl.h>

__BEGIN_DECLS
extern int cacheflush(void *addr, int nbytes, int flags);
__END_DECLS

#endif

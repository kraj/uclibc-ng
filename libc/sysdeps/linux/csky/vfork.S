#include <sysdep.h>
PSEUDO_ERRVAL(__vfork, vfork, 0)
PSEUDO_END_ERRVAL(__vfork)
weak_alias(__vfork, vfork)
libc_hidden_weak(vfork)


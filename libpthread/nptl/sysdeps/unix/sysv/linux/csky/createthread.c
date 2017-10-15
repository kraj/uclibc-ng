/* Value passed to 'clone' for initialization of the thread register.  */
#define TLS_VALUE (pd + 1)

/* Get the real implementation.	 */
#include <sysdeps/pthread/createthread.c>

/* Macros to support TLS testing in times of missing compiler support.  */

#define COMMON_INT_DEF(x) \
  __asm__ (".tls_common " #x ",4,4")
/* XXX Until we get compiler support we don't need declarations.  */
#define COMMON_INT_DECL(x)

/* XXX This definition will probably be machine specific, too.  */
#define VAR_INT_DEF(x) \
  __asm__ (".section .tdata\n\t"						      \
       ".globl " #x "\n"						      \
       ".balign 4\n"							      \
       #x ":\t.long 0\n\t"						      \
       ".size " #x ",4\n\t"						      \
       ".previous")
/* XXX Until we get compiler support we don't need declarations.  */
#define VAR_INT_DECL(x)

#ifdef __alpha__
#include <tls-macros-alpha.h>
#endif

#ifdef __arc__
#include <tls-macros-arc.h>
#endif

#ifdef __arm__
#ifdef __thumb__
#include <tls-macros-thumb.h>
#else
#include <tls-macros-arm.h>
#endif
#endif

#ifdef __i386__
#include <tls-macros-i386.h>
#endif

#ifdef __ia64__
#include <tls-macros-ia64.h>
#endif

#ifdef __metag__
#include <tls-macros-metag.h>
#endif

#ifdef __mips__
#include <tls-macros-mips.h>
#endif

#ifdef __powerpc__
#include <tls-macros-powerpc.h>
#endif

#ifdef __sh__
#include <tls-macros-sh.h>
#endif

#ifdef __sparc__
#include <tls-macros-sparc.h>
#endif

#ifdef __x86_64__
#include <tls-macros-x86_64.h>
#endif

#ifdef __xtensa__
#include <tls-macros-xtensa.h>
#endif

#if !defined TLS_LE || !defined TLS_IE \
      || !defined TLS_LD || !defined TLS_GD
# error "No support for this architecture so far."
#endif

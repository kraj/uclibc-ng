#define TLS_GD(x)					\
  ({ void *__result;					\
     extern void *__tls_get_addr (void *);		\
     __asm__ ("MOV %0, A1LbP\n\t"			\
	  "ADD %0, %0, #(" #x "@TLSGD)"			\
	  : "=d" (__result));				\
     (int *)__tls_get_addr (__result); })

#define TLS_LD(x)					\
  ({ void *__result;					\
     extern void *__tls_get_addr (void *);		\
     __asm__ ("MOV %0, A1LbP\n\t"			\
	  "ADD %0, %0, #(" #x "@TLSLDM)"		\
	  : "=d" (__result));				\
     __result = __tls_get_addr (__result);		\
     __asm__ ("ADDT %0,%0,#HI(" #x "@TLSLDO)\n\t"	\
	  "ADD %0,%0,#LO(" #x "@TLSLDO)"		\
	  : "+d" (__result));				\
     __result; })

#define TLS_IE(x)					\
  ({ void *__result;					\
     unsigned long __rel;				\
     extern void *__metag_load_tp (void);		\
     __asm__ ("GETD %0,[A1LbP+#(" #x "@TLSIE)]"		\
	  : "=d" (__rel));				\
     __result = __metag_load_tp();			\
     __result + __rel; })

#define TLS_LE(x)					\
  ({ void *__result;					\
     extern void *__metag_load_tp (void);		\
     __result = __metag_load_tp();			\
     __asm__ ("ADDT %0,%0,#HI(" #x "@TLSLE)\n\t"	\
	  "ADD %0,%0,#LO(" #x "@TLSLE)"			\
	  : "+d" (__result));				\
     __result; })


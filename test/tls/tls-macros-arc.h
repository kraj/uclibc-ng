/* For now */
#define TLS_LD(x)	TLS_IE(x)

#define TLS_GD(x)					\
  ({ int *__result;					\
     __asm__ ("add r0, pcl, @" #x "@tlsgd      \n"     	\
	  ".tls_gd_ld " #x "`bl __tls_get_addr@plt \n"	\
	  "mov %0, r0                    \n"		\
	  : "=&r" (__result)				\
	  ::"r0","r1","r2","r3","r4","r5","r6","r7",	\
	    "r8","r9","r10","r11","r12");		\
     __result; })

#define TLS_LE(x)					\
  ({ int *__result;					\
     void *tp = __builtin_thread_pointer();		                \
     __asm__ ("add %0, %1, @" #x "@tpoff   \n"		\
	  : "=r" (__result) : "r"(tp));	        \
     __result; })

#define TLS_IE(x)					\
  ({ int *__result;					\
     void *tp = __builtin_thread_pointer();		                \
     __asm__ ("ld %0, [pcl, @" #x "@tlsie]      \n"     \
	  "add %0, %1, %0                       \n"				\
	  : "=&r" (__result) : "r" (tp));		\
     __result; })


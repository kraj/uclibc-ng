#if defined(__XTENSA_WINDOWED_ABI__)
#define TLS_GD(x)							\
  ({ int *__l;								\
     __asm__ ("movi  a8, " #x "@TLSFUNC\n\t"				\
	  "movi a10, " #x "@TLSARG\n\t"					\
	  "callx8.tls a8, " #x "@TLSCALL\n\t"				\
	  "mov %0, a10\n\t"						\
	  : "=r" (__l)							\
	  :								\
	  : "a8", "a9", "a10", "a11", "a12", "a13", "a14", "a15");	\
      __l; })

#define TLS_LD(x)							\
  ({ int *__l;								\
     __asm__ ("movi  a8, _TLS_MODULE_BASE_@TLSFUNC\n\t"			\
	  "movi a10, _TLS_MODULE_BASE_@TLSARG\n\t"			\
	  "callx8.tls a8, _TLS_MODULE_BASE_@TLSCALL\n\t"		\
	  "movi %0, " #x "@TPOFF\n\t"					\
	  "add %0, %0, a10\n\t"						\
	  : "=r" (__l)							\
	  :								\
	  : "a8", "a9", "a10", "a11", "a12", "a13", "a14", "a15");	\
      __l; })
#elif defined(__XTENSA_CALL0_ABI__)
#define TLS_GD(x)							\
  ({ int *__l;								\
     __asm__ ("movi  a0, " #x "@TLSFUNC\n\t"				\
	  "movi a2, " #x "@TLSARG\n\t"					\
	  "callx0.tls a0, " #x "@TLSCALL\n\t"				\
	  "mov %0, a2\n\t"						\
	  : "=r" (__l)							\
	  :								\
	  : "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "a10", "a11");\
      __l; })

#define TLS_LD(x)							\
  ({ int *__l;								\
     __asm__ ("movi  a0, _TLS_MODULE_BASE_@TLSFUNC\n\t"			\
	  "movi a2, _TLS_MODULE_BASE_@TLSARG\n\t"			\
	  "callx0.tls a0, _TLS_MODULE_BASE_@TLSCALL\n\t"		\
	  "movi %0, " #x "@TPOFF\n\t"					\
	  "add %0, %0, a2\n\t"						\
	  : "=r" (__l)							\
	  :								\
	  : "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "a10", "a11");\
      __l; })
#else
#error Unsupported Xtensa ABI
#endif

#define TLS_IE(x) TLS_LE(x)

#define TLS_LE(x)							\
  ({ int *__l;								\
     int __t;								\
     __asm__ ("rur %0, threadptr\n\t"					\
	  "movi %1, " #x "@TPOFF\n\t"					\
	  "add %0, %0, %1\n\t"						\
	  : "=r" (__l), "=r" (__t) );					\
     __l; });								\


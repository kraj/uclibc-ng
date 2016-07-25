register void *__gp __asm__("$29");

# define TLS_LE(x) \
  ({ int *__l;								      \
     __asm__ ("call_pal 158\n\tlda $0," #x "($0)\t\t!tprel" : "=v"(__l));	      \
     __l; })

# define TLS_IE(x) \
  ({ char *__tp; unsigned long __o;					      \
     __asm__ ("call_pal 158\n\tldq %1," #x "($gp)\t\t!gottprel"		      \
	  : "=v"(__tp), "=r"(__o) : "r"(__gp));				      \
     (int *)(__tp + __o); })

# define TLS_LD(x) \
  ({ extern void *__tls_get_addr(void *); int *__l; void *__i;		      \
     __asm__ ("lda %0," #x "($gp)\t\t!tlsldm" : "=r" (__i) : "r"(__gp));	      \
     __i = __tls_get_addr(__i);						      \
     __asm__ ("lda %0, " #x "(%1)\t\t!dtprel" : "=r"(__l) : "r"(__i));	      \
     __l; })

# define TLS_GD(x) \
  ({ extern void *__tls_get_addr(void *); void *__i;			      \
     __asm__ ("lda %0," #x "($gp)\t\t!tlsgd" : "=r" (__i) : "r"(__gp));	      \
     (int *) __tls_get_addr(__i); })


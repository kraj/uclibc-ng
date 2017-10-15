/* Type used for the representation of TLS information in the GOT.  */
typedef struct
{
	unsigned long int ti_module;
	unsigned long int ti_offset;
} tls_index;

extern void *__tls_get_addr (tls_index *ti);


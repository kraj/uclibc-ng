#include <features.h>

#ifdef __CSKYABIV2__
#include "cskyv2/abiv2_memcpy.S"
#else
#include "cskyv1/memcpy.S"
#endif

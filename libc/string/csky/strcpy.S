#include <features.h>

#ifdef __CSKYABIV2__
#include "cskyv2/abiv2_strcpy.S"
#else
#include "cskyv1/strcpy.S"
#endif

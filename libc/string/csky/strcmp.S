#include <features.h>

#ifdef __CSKYABIV2__
#include "cskyv2/abiv2_strcmp.S"
#else
#include "cskyv1/strcmp.S"
#endif

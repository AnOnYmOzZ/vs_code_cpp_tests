#include "ctype.h"
#include "stdlib.h"
#include "string.h"


#ifndef STRLCPY_CUSTOM
#define STRLCPY_CUSTOM

size_t                  /* O - Length of string */
strlcpy(char *dst,        /* O - Destination string */
        const char *src,      /* I - Source string */
        size_t dstsize);     /* I - Size of destination string buffer */


#endif /* !STRLCPY_CUSTOM */

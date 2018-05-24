// $Id: strhash.c,v 1.6 2014-03-05 19:24:07-08 - - $
//usman zahid and alexander hoyt
//uzahid and adhoyt



#include <assert.h>
#include <stdio.h>
#include <sys/types.h>

#include "strhash.h"

size_t strhash (char *string) {
   assert (string != NULL);
   size_t hashcode = 0;
   while (*string) hashcode = (hashcode << 5) - hashcode + *string++;
   return hashcode;
}



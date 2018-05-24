// $Id: uninit.c,v 1.7 2014-05-07 15:18:25-07 - - $

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   int *pointer;
   printf ("pointer=%p\n", pointer);
   printf ("*pointer=%d\n", *pointer);
   int foo;
   printf ("foo=%d\n", foo);
}

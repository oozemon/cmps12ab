//usman zahid
//uzahid


#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <math.h>
#include "inssort.h"

#define ARRAY_SIZE 1000
char *progname = NULL;

int doublecmp (const void *this, const void *that) {
   double *thisdoub = (double*) this;
   double *thatdoub = (double*) that;
   return *thisdoub < *thatdoub ? -1 : *thisdoub > *thatdoub ? +1 : 0;
}

int main(int agrc, char **argv) {
   progname = basename (argv[0]);
   double array[ARRAY_SIZE];
   int count = 0;
   for (; ;count++) {
      if (count == ARRAY_SIZE) {
         //assert(count!=NULL);
        //printf("%s", "this is one iteration");
         break;
      } 
      double num;
      int rc = scanf("%lg",&num);
      if (rc == EOF) {
         break;
      } 
      if (rc != 0) {
         array[count] = num;
      } 
      else {
         //return NULL;
         return EXIT_FAILURE;
      }
   }
   int i = agrc; 
   i++;
   inssort(array, count, sizeof (double), doublecmp);
   for (int i = 0; i < count; i++) {
      printf("%20.15g\n",array[i]);
   }
}

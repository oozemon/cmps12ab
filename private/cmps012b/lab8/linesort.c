//Usman Zahid
//uzahid@ucsc.edu


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>


#include "inssort.h"

#define BUFFER_SIZE 1000
#define maxline 4096 


char* progname = NULL;



int strstrcmp (const void *this, const void *that) {
   char **thisstr = (char**) this;
   char **thatstr = (char**) that;
   return strcmp (*thisstr, *thatstr);
}




int main(int argc, char **argv){
   progname=basename(argv[0]);
   char line[maxline];
   char **buffer;
   int number = 0;
   buffer = (char**)malloc(sizeof(char*)*BUFFER_SIZE);
   number = 0;
   while(fgets(line,maxline,stdin)){
      if(feof(stdin)){
      //printf("this is working brothaaa");
      break;
      }
      buffer[number] = strdup(line);
      number++;
      if (number==BUFFER_SIZE){
        //printf("the buffersize is full");
        break;
      }
   }
   int index = argc;
   index++;
   inssort(buffer, number, sizeof(buffer[0]), strstrcmp);
   for (int index = 0; index <number; index++){
      printf("%s", buffer[index]);
   for (number = 0; number<BUFFER_SIZE; number++){
      free(buffer[number]);
   }
   free(buffer);
}
}


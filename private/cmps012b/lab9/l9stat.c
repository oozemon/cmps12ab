// Usman Zahid
// uzahid@ucsc.edu


#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <sys/stat.h>
#include <errno.h>

char *progname = NULL;
int exit_status = EXIT_SUCCESS;


//void program that runs 

void l9stat(char *filename) {
   struct stat buffer;
   int status = lstat(filename, &buffer);
   if (status != 0) {
      printf("stat fail\n");
      fflush (NULL);
      fprintf (stderr, "%s: %s: %s\n", progname,
               filename, strerror (errno));
      fflush (NULL);
      exit_status = EXIT_FAILURE;
   } else {
      printf("stat success\n");
      int size = (int)buffer.st_size;
      int mode = (int)buffer.st_mode;
      printf("%06o\t%d ", mode, size); 
      struct tm *tm = localtime(&buffer.st_mtime);
      time_t currtime;
      time(&currtime);
      double diff = difftime(buffer.st_mtime, currtime);
      char *format = NULL;
      if (diff < 0) diff = -diff;
      if (diff > 15552000) {
         format = "%b %d %y";
      } else {
         format = "%b %d %X";
      }
      char tbuff[1024];
      strftime(tbuff, sizeof(tbuff), format, tm);
      printf("%s %s", tbuff, filename);
      


//provides the name of the link is the file is not specified.

      char *linkname = NULL;
      linkname = malloc(buffer.st_size + 1);
      assert(linkname != NULL);
      int linkflag = readlink(filename, linkname, buffer.st_size + 1);

      if (linkflag != -1) {
         linkname[buffer.st_size] = '\0';
         printf(" --> %s", linkname);
      }
      printf("\n");
      free(linkname);
   }
}

//succint main function that calls the other functions in order 
//from the command line args
//"argc, and **argv.


int main(int argc, char **argv) {

   exit_status = EXIT_SUCCESS;
   progname = basename (argv[0]);

   if (argc == 1) {
      l9stat(".");
   } else {
      for (int i = 1; i < argc; i++) {
         char *filename = argv[i];
         l9stat(filename);
      }
   }   
}

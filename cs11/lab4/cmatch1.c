//Usman Zahid
//uzahid
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int exit_status = EXIT_SUCCESS;
char *program_name = NULL;
#define STDIN_NAME "-"
typedef struct options *options;
struct options {
   bool ignore_case;
   bool filenames_only;
   bool number_lines;
};

void scan_options (int argc, char **argv, options opts) {
   opts->ignore_case = false;
   opts->filenames_only = false;
   opts->number_lines = false;
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "iln");
      if (opt == EOF) break;
      switch (opt) {
         case 'i':
            opts->ignore_case = true;
            break;
         case 'l':
            opts->filenames_only = true;
            break;
         case 'n':
            opts->number_lines = true;
            break;
         default:
            exit_status = EXIT_FAILURE;
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                             program_name, optopt);
            break;
      }
   }
}

const char *strbool (bool value) {
   return value ? "true" : "false";
}

void catbyline (FILE *input, char *filename, char *stringstring) {
   char buffer[1024];
   for (int linenr = 1;; ++linenr) {
      char *buf = fgets (buffer, sizeof buffer, input);
      if (buf == NULL){
                    break;
      }
      if ((strstr(buf,stringstring) !=NULL)){
      printf ("%6d: %s", linenr, buf);
      }
   }
}

void filecat (FILE *input, char *filename, char *stringstring){
   char buffer[1024];
   int fCnt =0;
   for (int linenr = 1;; ++linenr){
      char *buf = fgets (buffer, sizeof buffer, input);
      if (buf == NULL){
          if (fCnt > 0) printf("Found in %s\n", filename);
             break;
          } 
          if ((strstr(buf,stringstring) !=NULL)){
             fCnt++;
          }
      }
}

void catall (FILE *input, char *filename, char *stringstring) {
    char buffer [1024];
    for (int linenr =1;; ++linenr) {
        char *buf = fgets(buffer, sizeof buffer, input);
        if (buf ==NULL) break;
        if ((strcasestr(buf,stringstring) !=NULL)){
        printf("%s \n", buf);
}
}
}

int main (int argc, char **argv) {
  char *stringstring = NULL;
  program_name = basename (argv[0]);
   if (argc <= 2) {
      fprintf(stderr, "Error, use -iln: %s\n", basename(argv[0]));
      fflush(NULL);
      exit (EXIT_FAILURE);
   }else {
      options opts = malloc(sizeof(options));
      scan_options (argc, argv, &opts);
      stringstring = argv[2];
      for (int argi = 3; argi < argc; ++argi) {
         char *filename = argv[argi];
         if (strcmp (filename, STDIN_NAME) == 0) {
            catbyline (stdin, STDIN_NAME, stringstring);
         }else {
            FILE *input = fopen (filename, "r");
            if (input != NULL) {
               if (opts->number_lines==true){
               catbyline (input, filename, stringstring);
               fclose (input);
              }
               if (opts->filenames_only== true){
                  catall(input, filename, stringstring);
              }
            }else {
               exit_status = EXIT_FAILURE;
               fflush (NULL);
               fprintf (stderr, "%s: %s: %s\n", program_name,
                        filename, strerror (errno));
               fflush (NULL);
            }
         }
      }
   }
   return exit_status;
}

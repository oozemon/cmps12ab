//Usman Zahid
//uzahid

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
char *program_name = NULL;
int exit_status = EXIT_SUCCESS;
#define STDIN_NAME "-"
//buffer means allocated ram
//will store file in incrmenets
typedef struct options {
   bool ignore_case;
   bool filenames_only;
   bool number_line;
} options;

void scan_options (int argc, char** argv, options 
*opts){
   opts->ignore_case = false;
   opts->filenames_only = false;
   opts->number_line = false;
   opterr = false;
   for (;;) {
       int opt = getopt(argc, argv, "iln");//takes args[], and optio
       if(opt == EOF) break;
       switch (opt) { 
         case 'i': 
            opts->ignore_case = true;
            break;
         case 'l': 
           opts->filenames_only = true;
            break;
         case 'n':
            opts->number_line = true;
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
   
void catbyline (FILE *input, char *filename,char *inWrd)  {
   char buffer[1024];
   for (int linenr = 1;; ++linenr) {
      char *buf = fgets (buffer, sizeof buffer, input);
        if (buf == NULL){ // if line is done
           break;
       }
      
        if( ( strstr(buf,inWrd) != NULL)){
        printf("line: %d: %s\n",linenr,buf);
      }
      if (buf == NULL){ 
           break;
       }
   }
}
void filecat (FILE *input, char *filename,char *inWrd)  {
   char buffer[1024];
   int fCnt =0;
   for (int linenr = 1;; ++linenr) {
      char *buf = fgets (buffer, sizeof buffer, input);
       if (buf == NULL){ 
          if(fCnt >0) printf("Found in %s\n", filename);
             break;
       }
        if( ( strstr(buf,inWrd) != NULL)){
         fCnt++;
          }   
   }
}
void catall (FILE *input, char *filename,char *inWrd)  {
   char buffer[1024];
   for (int linenr = 1;; ++linenr) {
      char *buf = fgets (buffer, sizeof buffer, input);
        if (buf == NULL) break;
        if( ( strcasestr(buf,inWrd) != NULL)){
        printf("%s \n", 
          buf);  
          } 
   }
} 
int main (int argc, char **argv) {
   options opts;
   char *inWrd = NULL;
  
   program_name = basename (argv[0]);
   if (argc <= 2) {
      fprintf (stderr, "ERROR, USE -ILN: %s\n", basename (argv[0]));
      fflush (NULL);
      exit (EXIT_FAILURE);
      
   }else {
     scan_options(argc,argv,&opts);
       inWrd = argv[2];
     
      if(opts.ignore_case == true){
      }
      for (int argi = 3; argi < argc; ++argi) {
         char *filename = argv[argi];
         if (strcmp (filename, STDIN_NAME) == 0) {
            catbyline (stdin, STDIN_NAME, inWrd);
         }else {
            FILE *input = fopen (filename, "r");
            if (input != NULL) {
             if(opts.number_line ==true){
               
               catbyline (input, filename, inWrd);
               fclose (input);
              } 
              if(opts.filenames_only == true){
                 filecat(input, filename, inWrd);  
                 }
              if(opts.ignore_case == true){
               catall(input, filename, inWrd); 
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
}

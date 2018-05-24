// $Id: spellchk.c,v 1.9 2014-05-15 21:07:47-07 - - $
//usman zahid and alexander hoyt
//uzahid@ucsc.edu and adhoyt@ucsc.edu	


#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "debug.h"
#include "hashset.h"
#include "yyextern.h"

#define STDIN_NAME "-"
#define DEFAULT_DICTNAME \
"/afs/cats.ucsc.edu/courses/cmps012b-wm/usr/dict/words"
#define DEFAULT_DICT_POS 0
#define EXTRA_DICT_POS 1
#define NUMBER_DICTS 2

// prints out the error messages
void print_error (char *object, char *message) {
  fflush (NULL);
  fprintf (stderr, "%s: %s: %s\n", Exec_Name, object, message);
  fflush (NULL);
  Exit_Status = EXIT_FAILURE;
}

// opens the file
FILE *open_infile (char *filename) {
  FILE *file = fopen (filename, "r");
  if (file == NULL) {
    print_error (filename, strerror (errno));
    Exit_Status = 2;
  }
  return file;
}

// checks for spelling by looking for word in hashtable
void spellcheck (char *filename, hashset *hashset) {
  yylineno = 1;
  for (char *text;;free(text)) {
    int token = yylex ();
    if (token == 0) break;
    text = strdup(yytext);
    // initial lookup
    if(has_hashset(hashset, text)) continue;
    text[0] = tolower(*yytext);
    // upper case lookup
    if(has_hashset(hashset, text)) continue;
    // if both lookups fail print error messages
    printf("%s: %d: %s\n", filename, yylineno, yytext);
    Exit_Status = 1;
  }
}

//Loads the dictionary and puts each word into the hashtable
void load_dictionary (char *dictionary_name, hashset *hashset) {
  if (dictionary_name == NULL) return;
  FILE *dictionary = open_infile(dictionary_name);
  char item[100];
  while (fgets (item, 100, dictionary) != NULL){
    // replaces new line characters with null
    item[strlen(item) - 1] = '\0';
    put_hashset(hashset , item);
  }
  fclose(dictionary);
}

int main (int argc, char **argv) {
  Exec_Name = basename (argv[0]);
  char *default_dictionary = DEFAULT_DICTNAME;
  char *user_dictionary = NULL;
  hashset *hashset = new_hashset ();
  yy_flex_debug = false;
  int debug_code = 0;
  // Scan the arguments and set flags.
  opterr = false;
  for (;;) {
    int option = getopt (argc, argv, "nxyd:@:");
    if (option == EOF) break;
    switch (option) {
      char optopt_string[16]; // used in default:
    case 'd': user_dictionary = optarg;
      break;
    case 'n': default_dictionary = NULL;
      break;
    case 'x': debug_code++;
      break;
    case 'y': yy_flex_debug = true;
      break;
    case '@': set_debugflags (optarg);
      if (strpbrk (optarg, "@y")) yy_flex_debug = true;
      break;
    default : sprintf (optopt_string, "-%c", optopt);
      print_error (optopt_string, "invalid option");
      break;
    }
  }

  // Load the dictionaries into the hash table.
  load_dictionary (default_dictionary, hashset);
  load_dictionary (user_dictionary, hashset);

  // Read and do spell checking on each of the files.
  if (optind >= argc) {
    yyin = stdin;
    spellcheck (STDIN_NAME, hashset);
  }else {
    for (int fileix = optind; fileix < argc; ++fileix) {
      char *filename = argv[fileix];
      if (strcmp (filename, STDIN_NAME) == 0) {
        yyin = stdin;
        spellcheck (STDIN_NAME, hashset);
      }else {
        yyin = open_infile (filename);
        if (yyin == NULL) continue;
        spellcheck (filename, hashset);
        fclose (yyin);
      }
    }
  }
  if(debug_code > 0) cluster_print (hashset);
  if(debug_code > 1) hash_dump(hashset);
  yylex_destroy ();
  free_hashset(hashset);
  return Exit_Status;
}



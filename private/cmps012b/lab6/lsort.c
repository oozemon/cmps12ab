//usman zahid and alex hoyt
//uzahid and adhoyt

#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#define INPUT stdin

char *progname = NULL;
int exit_status = EXIT_SUCCESS; 

struct options {
   bool debug;
};

typedef char *cstring;
typedef struct node *node_ref;
struct node {
    cstring item;
    node_ref link;
};

int leakfix(node_ref listhead) {
   while (listhead != NULL) {
      node_ref old = listhead;
      listhead = listhead->link;
      free(old->item);
      free(old);
   }
   return EXIT_SUCCESS;
}

int printall(node_ref ptr, struct options *opts) {
   if (opts->debug == true) {
      for (node_ref curr = ptr; curr != NULL; curr = curr->link) {
         printf ("%p -> struct node {item= %s, link= %p}\n",
                     (void*) curr, curr->item, (void*) curr->link);
      }
      return EXIT_SUCCESS;
   } else {
      node_ref curr = ptr;
      while (curr != NULL) {
         printf("%s\n", curr->item);
         curr = curr->link;
      }
      return EXIT_SUCCESS;
   }
}

void scan_options (int argc, char **argv, struct options *opts) {
   opts->debug = false;
   
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "d");
      if (opt == EOF) break;
      switch (opt) {
         case 'd':
            opts->debug = true;
            break;
         default : 
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                     progname, optopt);
            fflush (NULL);
            exit_status = EXIT_FAILURE;
       }
   }
}


int main (int argc, char **argv) {

   progname = basename (argv[0]);
   struct options opts;
   scan_options (argc, argv, &opts);
   if (exit_status == EXIT_FAILURE) return exit_status;
   
   node_ref head = NULL;
   char buffer[72];
   int linenr;
   for (linenr = 1; ; ++linenr) {

      char *gotline = fgets (buffer, sizeof buffer, stdin);
      if (gotline == NULL) break;

      char *nlpos = strchr (buffer, '\n');
      if (nlpos != NULL) {
         *nlpos = '\0';
      }else {
         exit_status = EXIT_FAILURE;
         fprintf (stderr, "%s: %d: unterminated line: %s\n",
                  progname, linenr, buffer);
      }
     
      node_ref new = malloc (sizeof(struct node));
      assert(new != NULL);
      new->item = strdup(buffer);
      
      node_ref prev = NULL;
      node_ref curr = head;
     
      while (curr != NULL) {
         int cmp = strcmp(curr->item, new->item);
         if (cmp > 0) break;
         prev = curr;
         curr = curr->link;
      }
    
      new->link = curr;
      if (prev == NULL) head = new;
         else prev->link = new;
   }
   printall(head, &opts);
   leakfix(head);
   return exit_status;
}


// $Id: hashset.c,v 1.9 2014-05-15 20:01:08-07 - - $
//usman zahid and alexander hoyt
//uzahid and adhoyt


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "hashset.h"
#include "strhash.h"
#define HASH_NEW_SIZE 15

typedef struct hashnode hashnode;
//typedef size_t size_t;
struct hashnode {
   char *word;
   hashnode *link;
};

struct hashset {
   size_t size;
   size_t load;
   hashnode **chains;
};

// Makes new hash table

hashset *new_hashset (void) {
   hashset *this = malloc (sizeof (struct hashset));
   assert (this != NULL);
   this->size = HASH_NEW_SIZE;
   this->load = 0;
   size_t sizeof_chains = this->size * sizeof (hashnode *);
   this->chains = malloc (sizeof_chains);
   assert (this->chains != NULL);
   memset (this->chains, 0, sizeof_chains);
   return this;
}

// Frees all allocated memory

void free_hashset (hashset *this) {
   for(size_t index = 0; index < this->size; index++){
      hashnode *temp = this->chains[index];
      while(temp != NULL){
         hashnode *next = temp->link;
         free(temp->word);
         free(temp);
         temp = next;
       }
   }
   free(this->chains);
   free(this);
}

// doubles array size

void doublearr(hashset *this){
   size_t length = this->size * 2 + 1;
   hashnode **newarr = calloc(length, sizeof(hashnode *));
   for(size_t index = 0; index < this->size; index++){
      hashnode *temp = this->chains[index];
      while (temp != NULL){
         size_t hash_index = strhash (temp->word) % length;
         hashnode *link = temp->link;
         temp->link = newarr[hash_index];
         newarr[hash_index] = temp;
         temp = link;
       }
   }
   free(this->chains);
   this->chains = newarr;
   this->size = length;
}

// puts word into hash table

void put_hashset (hashset *this, char *item) {
   if (this->load * 2 + 1 > this->size){
      doublearr (this);
   }
   size_t hash_index = strhash (item) % this->size;
   hashnode *curr = this->chains[hash_index];
   for(hashnode *newnode = curr; newnode != NULL; newnode = newnode->link){
      if (strcmp(newnode->word, item) == 0) return;
   }
   hashnode *n = malloc(sizeof (struct hashnode));
   n->link = this->chains[hash_index];
   n->word = strdup(item);
   this->chains[hash_index] = n;
   ++this->load;
}


bool has_hashset (hashset *this, char *item) {
   size_t hash_index = strhash (item) % this->size;
   hashnode *head = this->chains[hash_index];
   for (hashnode *top = head; top != NULL; top = top->link){
   int comp= strcmp(top->word, item);
      if( comp== 0) return true;
   }
   return false;
}

/*void print_hashset (hashset *this) {
   //printf("first\n");
   //STUBPRINTF ("hashset=%p, item=%s\n", this, item);;
   for (int i = 0; i < this->size; i++) {
      for (hashnode *newvar = this->chains[i]; newvar != NULL; newvar = newvar->link){
         printf("%s\n", newvar->word);    
      }
   }

}*/



void debugopt (hashset *this, int flag){
  size_t set = this->load;
  size_t array = this->size;
  printf("%zu words in the hash set\n", set);
  printf("%zu size of the hash array\n", array); 
  int *counter = calloc(50, sizeof(int));
  for(size_t j = 0; j < this->size; j++){
     int linknum = 0;
     hashnode *head = this->chains[j];
     for(hashnode *h = head; h != NULL; h = h->link) linknum++;
        counter[linknum]++;
   }
   int size = 50;
   for(int j = 1; j < size; j++){
      if(counter[j] != 0){
         printf("%5d chains of size %d\n", counter[j], j);
      }
   }
   free(counter);
   
   if(flag==2){
      char *equ= "=";
      for(size_t k=0; k< this->size;k++){
         hashnode *hash=this->chains[k];
         if(hash==NULL)continue;
         printf("array[%10zu]", k);
         printf("=%20lu \" %s\"\n", strhash(hash->word), hash->word);
         for(hashnode *curr=this->chains[k+1]; curr!=NULL;
            curr=curr->link){
            printf("%18s %20lu \"%s\"\n", equ, strhash(hash->word),
                   hash->word);
         }
         hash=hash->link;
       }
    }
}


void dumphash(hashset *this){
   for(size_t i = 0; i < this->size; i++){
      hashnode *temp = this->chains[i]; 
      if(temp != NULL){
         size_t code = strhash(temp->word);
         printf("array[%10d] = %12u \"%s\"\n",
             (int)i, (int)code, temp->word);
         temp = temp->link;
      }
    
    while(temp != NULL){
       size_t code = strhash(temp->word);
       printf("%18s= %12u \"%s\"\n", "" , (int)code, temp->word);
       temp = temp->link;
     }
  }
}

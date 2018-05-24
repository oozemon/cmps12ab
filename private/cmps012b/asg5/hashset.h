// $Id: hashset.h,v 1.3 2014-03-05 19:24:07-08 - - $
//usman zahid and alexander hoyt
//uzahid@ucsc.edu and adhoyt@ucsc.edu

#ifndef __HASHSET_H__
#define __HASHSET_H__

#include <stdbool.h>

typedef struct hashset hashset;

//
// Create a new hashset with a default number of elements.
//
hashset *new_hashset (void);

//
// Frees the hashset, and the words it points at.
//
void free_hashset (hashset *);

//
// Doubles the array size
//
void double_hash(hashset *);

//
// Inserts a new string into the hashset.
//
void put_hashset (hashset *, char*);

//
// Looks up the string in the hashset and returns true if found,
// false if not found.
//
bool has_hashset (hashset *, char*);

//
// Prints out a table including a cluster message for each
// different number of cluster sizes.
//
void cluster_print(hashset *);

//
// Prints out a dump of the hash set, printing out each
// entry with subscript, hash code, and string.
//
void hash_dump (hashset *);
#endif



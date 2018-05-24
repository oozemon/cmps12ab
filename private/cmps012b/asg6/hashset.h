// $Id: hashset.h,v 1.3 2014-03-05 19:24:07-08 - - $
//usman zahid and alexander hoyt
//uzahid@ucsc.edu and adhoyt@ucsc.edu

#ifndef __HASHSET_H__
#define __HASHSET_H__

#include <stdbool.h>

typedef struct hashset hashset;

hashset *new_hashset (void);
void debugopt(hashset *, int);
void dumphash (hashset *);
void free_hashset (hashset *);
void doublearr(hashset *);
void put_hashset (hashset *, char*);

bool has_hashset (hashset *, char*);

#endif



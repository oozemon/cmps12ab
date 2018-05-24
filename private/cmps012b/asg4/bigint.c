// $Id: bigint.c,v 1.13 2014-01-24 18:33:47-08 - - $
// Usman Zahid and Kara Ekiss
// uzahid and kekiss

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigint.h"
#include "debug.h"

#define MIN_CAPACITY 16

struct bigint {
   size_t capacity;
   size_t size;
   bool negative;
   char *digits;
};

static void trim_zeros (bigint *this) {
   while (this->size > 0) {
      size_t digitpos = this->size - 1;
      if (this->digits[digitpos] != 0) break;
      --this->size;
   }
}

bigint *new_bigint (size_t capacity) {
   bigint *this = malloc (sizeof (bigint));
   assert (this != NULL);
   this->capacity = capacity;
   this->size = 0;
   this->negative = false;
   this->digits = calloc (this->capacity, sizeof (char));
   assert (this->digits != NULL);
   DEBUGS ('b', show_bigint (this));
   return this;
}

bigint *new_string_bigint (char *string) {
   assert (string != NULL);
   size_t length = strlen (string);
   bigint *this = new_bigint (length > MIN_CAPACITY
                            ? length : MIN_CAPACITY);
   char *strdigit = &string[length - 1];
   if (*string == '_') {
      this->negative = true;
      ++string;
   }
   char *thisdigit = this->digits;
   while (strdigit >= string) {
      assert (isdigit (*strdigit));
      *thisdigit++ = *strdigit-- - '0';
   }
   this->size = thisdigit - this->digits;
   trim_zeros (this);
   DEBUGS ('b', show_bigint (this));
   return this;;
}


static bigint *do_add (bigint *this, bigint *that) {
  bigint *result = new_bigint(this->size + 1);
  result->size = this->size + 1;

  int digit = 0;
  int carry = 0; 
  
  int thisvalue = 0;
  int thatvalue = 0;

  for(int i = 0; i <=(int)(result->size); ++i){
    if((int)(this->size - 1) < i) thisvalue = 0;
    else thisvalue = this->digits[i];
    
    if ((int)(that->size - 1) < i) thatvalue = 0;
    else thatvalue = that->digits[i];
    
    digit = thisvalue + thatvalue + carry;
    result->digits[i] = digit % 10;
    carry = digit / 10;
  }

  trim_zeros(result);
  return result;
}

static bigint *do_sub (bigint *this, bigint *that) {
  bigint *result = new_bigint(this->size +1);
  result->size = this->size +1;
  
  int digit = 0;
  int borrow = 0;

  int thisvalue = 0;
  int thatvalue = 0;

  for(int i = 0; i < (int)(result->size); ++i){
    if((int)(this->size-1)<i) thisvalue = 0;
    else thisvalue = this->digits[i];
    
    if((int)(that->size-1) < i) thatvalue = 0;
    else thatvalue = that->digits[i];
    
    digit = thisvalue - thatvalue - borrow + 10;
    result->digits[i] = digit % 10;
    borrow = 1 - digit / 10;
  }

  trim_zeros(result);
  return result;
}

void free_bigint (bigint *this) {
   free (this->digits);
   free (this);
}

void print_bigint (bigint *this, FILE *file) {
  int lnW = 69;
  int printed = 0;

  if (this == NULL) {
    fprintf(file, "dc: bigint@%p is empty\n",this);
    return;
  }

  if (this->negative) {
    fprintf(file,"-");
    printed++;
  }

  for (int index = this->size -1; index >= 0; index--) {
    fprintf(file, "%d", this->digits[index]);
    printed++;
    if (printed >= lnW) {
      fprintf(file,"\\\n");
      printed = 0;
    }
  }
  fprintf(file,"\n");
}

bigint *add_bigint (bigint *this, bigint *that) {
  bigint *max = NULL;
  bigint *min = NULL;
  bigint *result = NULL;
  if (this->size > that->size) {
    max = this;
    min = that;
  } else {
    max = that;
    min = this;
  }

  if(this->negative == that->negative)
    result = do_add(max,min);
  else{
    result = do_sub(max,min);
  }

  result->negative = max->negative;
  return result;
}

bigint *sub_bigint (bigint *this, bigint *that) {
  bigint *max = NULL;
  bigint *min = NULL;
  bigint *result = NULL;
  if (this->size > that->size) {
    max = this;
    min = that;
  } else {
    max = that;
    min = this;
  }

  if(this->negative != that->negative){
    result = do_add(max,min);
    if (max->negative){
       result->negative = true;
    }
}
  else{
    result = do_sub(max,min);
    if (max == that) result->negative=true;
  }

  return result;
}

bigint *mul_bigint (bigint *this, bigint *that) {
   int carry = 0;
   int digit = 0;
   bigint *product = new_bigint(this->size + that->size);
   product->size = this->size + that->size;
   for (int i = 0; i < (int)(this->size); ++i){
       carry = 0;
         for(int j = 0; j < (int)(that->size); ++j){
         digit = product->digits[i+j] + this->digits[i]
 * that->digits[j] + carry;
         product->digits[i+j] = digit%10;
         carry = digit/10;
      }
      product->digits[i + that->size] = carry;
   }
   trim_zeros(product);
  if(this->negative != that->negative){
     product->negative = true;
  }
  return product;
}

void show_bigint (bigint *this) {
   fprintf (stderr, "bigint@%p->{%lu,%lu,%c,%p->", this,
            this->capacity, this->size, this->negative ? '-' : '+',
            this->digits);
   for (char *byte = &this->digits[this->size - 1];
        byte >= this->digits; --byte) {
      fprintf (stderr, "%d", *byte);
   }
   fprintf (stderr, "}\n");
}

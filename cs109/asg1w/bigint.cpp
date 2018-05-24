//Usman Zahid
//uzahid@ucsc.edu
//pa1

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "debug.h"
#include "relops.h"


bigint::bigint (long that): uvalue (that), is_negative (that < 0) {
   DEBUGF ('~', this << " -> " << uvalue)
   is_negative = false; 
   if((to_string(that).size() > 0) &&(to_string(that)[0] == '-')) {
        is_negative = true; //qualifying flag for neg flag
   }
   uvalue =  ubigint(to_string(that).substr(is_negative ? 1 : 0));  
}



bigint::bigint (const ubigint& uvalue, bool is_negative):
                uvalue(uvalue), is_negative(is_negative) {
}

bigint::bigint (const string& that) {
   is_negative = false;
   if((that.size() > 0) &&(that[0] == '_')) {
      is_negative = true;
   }
   uvalue = ubigint(that.substr(is_negative ? 1 : 0));
}


bigint bigint::operator+() const {  
   return *this;
}

bigint bigint::operator-() const {
    return -(*this);
}

//plus operator code
bigint bigint::operator+ (const bigint& that) const {
   ubigint result;
   bigint val;
   if(is_negative == that.is_negative){      
      result = uvalue + that.uvalue;
      val = result;
      val.is_negative = is_negative;
      return val;
   }
   else{
  	result = (*this < that) ? (uvalue - that.uvalue)
        : (that.uvalue - uvalue);
  	val = result;
  	if(*this < that){
  	   val.is_negative = is_negative;
  	}
        else{
            val.is_negative = that.is_negative;
  	}
  	    return val;
  	}
}
//code for minus operator
bigint bigint::operator- (const bigint& that) const {
   ubigint result;
   bigint val;
   if(is_negative == that.is_negative){ 
      result = (*this < that) ? (that.uvalue - uvalue)
      : (uvalue - that.uvalue);
      val = result;
      if(*this < that){
         val.is_negative = not that.is_negative;
         }else{
  	    val.is_negative = is_negative;
          }
      return val;
      }
      else{
         result = uvalue + that.uvalue;
         val = result;
         val.is_negative = is_negative;
         return val;
      }
}

bigint bigint::operator* (const bigint& that) const {
   ubigint result;
   bigint val;
   if(is_negative == that.is_negative){
      result = uvalue * that.uvalue;
      val = result;
      val.is_negative = false;
   }
   else{
   result = uvalue * that.uvalue;
   val = result;
   val.is_negative = true;  
   }
   return val;
}

bigint bigint::operator/ (const bigint& that) const {
   ubigint result;
   ubigint negOne(-1);
   bigint val;
   if(is_negative && !that.is_negative){
      result = (uvalue*negOne) / that.uvalue;
      val = result;
      val.is_negative = true;
      return val;
   }
   if(that.is_negative && !is_negative){
      result = uvalue / (that.uvalue*negOne);
      val = result;
      val.is_negative = true;
      return val;
   }
   if(that.is_negative && is_negative){
      result = (uvalue*negOne) / (that.uvalue*negOne);
      val = result;
      val.is_negative = false;
      return val;
   }else{
      result = uvalue / that.uvalue;
      val = result;
      val.is_negative = false;
      return val;
   }
      return val;
}
//division operator, most difficult to implement

bigint bigint::operator% (const bigint& that) const {
   ubigint result;
   ubigint negOne(-1);
   bigint val;
   
   if(is_negative && !that.is_negative){
      result = (uvalue*negOne) % that.uvalue;
      val = result;
      val.is_negative = true;
      return val;
   }
   if(that.is_negative && !is_negative){
      result = uvalue % (that.uvalue*negOne);
      val = result;
      val.is_negative = true;
      return val;
   }
   if(that.is_negative && is_negative){
      result = (uvalue*negOne) % (that.uvalue*negOne);
      val = result;
      val.is_negative = false;
      return val;
   }else{
      result = uvalue % that.uvalue;
      val = result;
      val.is_negative = false;
      return val;
   }
      return val;
}

bool bigint::operator== (const bigint& that) const {
   if (is_negative != that.is_negative){
      return false;
      //return true;
}
   return is_negative == that.is_negative
      and uvalue == that.uvalue;
}

bool bigint::operator< (const bigint& that) const {
   bool rb;
   if(is_negative){
      if(!that.is_negative){
      rb = true; //set flag
      }else{
      rb = that.uvalue < uvalue;
      }
   }else{
      if(that.is_negative){
      rb = false;
      }else{
      rb = uvalue < that.uvalue;
   } 
} 
   return rb;
}

ostream& operator<< (ostream& out, const bigint& that) {
   if (that.is_negative){
      out << '-';
   }
    out << that.uvalue;
   return out;
}



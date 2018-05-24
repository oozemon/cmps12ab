//Usman Zahid
//uzahid@Ucsc.edu
//pa1

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "ubigint.h"
#include "debug.h"

#include <limits>
#define LINE_LIMIT 69


ubigint::ubigint (unsigned long that): uvalue (that) {
   DEBUGF ('~', this << " -> " << uvalue)
 //int value += value;
   int value = 0;
   auto digit = to_string(that).cbegin();
   while (digit != to_string(that).cend()) {
     value = value * 10 + *digit++ - '0';
   }
   auto i  = to_string(that).crbegin();
   for (; i != to_string(that).crend() && *i != '-'; i++) {
      ubig_value.push_back(*i - '0');
   }
}
//comparing values for fns
ubigint::ubigint (const string& that){
   int value = 0;
   auto digit = that.cbegin();
   while (digit != that.cend()) {
      value = value * 10 + *digit++ - '0';
   }

   auto i  = that.crbegin();
   for (; i != that.crend() && *i != '_'; i++) {
      ubig_value.push_back(*i - '0');
   }
}

void ubigint::clean(){
   auto i = ubig_value.rbegin();
   for(;i != ubig_value.rend() ;i++){
    if(*i != 0){
        break;
    }
    ubig_value.pop_back();
  }
}

//Do Add
ubigint addVecs(const ubigint& left,const ubigint& right){
     
      ubigint sum;
      int carry =0;
      auto lit = left.ubig_value.begin();
      auto rit = right.ubig_value.begin();

      int art_size = 
      (left.ubig_value.size()>right.ubig_value.size()) ?
      left.ubig_value.size() : right.ubig_value.size();

       for(int i =0; i<art_size+1; i++){
          int l = carry;
          int r = 0;
          if(lit != left.ubig_value.end()){
           l += *lit;
            ++lit;
          }
          if(rit != right.ubig_value.end()){
            r += *rit;
             ++rit;
           }
          sum.ubig_value.push_back( (l+r) %10);
          carry = (l+r)/10;
       }
       sum.clean();  
       return sum;
}

ubigint ubigint::operator+ (const ubigint& that) const {
   ubigint sum;
   sum = addVecs(*this, that);
   return sum;
}

//subtraction
ubigint subVecs(const ubigint& left,const ubigint& right){
   ubigint diff;
   int carry = 0;
      auto lit = left.ubig_value.begin();
      auto rit = right.ubig_value.begin();
      int art_size = left.ubig_value.size();
      for(int i =0; i<art_size;i++){
       int a = 0;
       int b =0;
          if(lit != left.ubig_value.end()){
            a = *lit;
            ++lit;
          }
          if(rit != right.ubig_value.end()){
            b = *rit;
            ++rit;
          }
          if(a - b - carry < 0){
            a += 10; 
            diff.ubig_value.push_back(a-b-carry);
            carry = 1; 
          }else{
             diff.ubig_value.push_back (a-b-carry);
             carry = 0;
          }
       }
       diff.clean();
       return diff;
}

ubigint ubigint::operator- (const ubigint& that) const {
   ubigint diff;
   diff = subVecs(*this, that);
   return diff;
}

ubigint multVecs(const ubigint& left, const ubigint& right){
   ubigint ans{}; 
   int val {};
   ans.ubig_value.resize
   (left.ubig_value.size()+right.ubig_value.size() +1);

   auto lit = left.ubig_value.begin(); 

   for(int i = 0; 
      i<static_cast<int>(left.ubig_value.size())
      ;i++){
      int carry = 0;
      auto rit = right.ubig_value.begin();
//algorithm given from instructions in pa1
      for(int j =0;
         j < static_cast<int>(right.ubig_value.size()); j++){
         val = ans.ubig_value[i+j] + (*lit)*(*rit) + carry;
         ans.ubig_value[i+j] = val%10;
         carry = val/10;
         ++rit;
      }
      ans.ubig_value[i+right.ubig_value.size()] = carry;
      ++lit;
   }
   ans.clean();
   return ans;
}

ubigint ubigint::operator* (const ubigint& that) const {
   ubigint times;
   times = multVecs(*this, that);
   return times;
}

void ubigint::multiply_by_2() {
   ubig_value = addVecs(*this,*this).ubig_value;
   clean();
   
}

void ubigint::divide_by_2(){
   auto i = ubig_value.rbegin(); 
   auto last = ubig_value.rend();
   int carry = 0;
   for(;i != last ;i++){
      if(*i%2 == 1){
         *i = *i/2 + carry; 
         carry = 5;
      }else{
        *i = *i/2 + carry; 
         carry = 0;
      }
   }
   clean();
}

ubigint::quot_rem ubigint::divide (const ubigint& that) const {
   static const ubigint zero = 0;
   if (that == zero) throw domain_error ("ubigint::divide: by 0");
   ubigint power_of_2 = 1;
   ubigint divisor = that; // right operand, divisor
   ubigint quotient = 0;
   ubigint remainder = *this; // left operand, dividend
   while (divisor < remainder) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
   }
   while (power_of_2 > zero) {
      if (divisor <= remainder) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divisor.divide_by_2();
      power_of_2.divide_by_2();
   }
   return {quotient, remainder};
}

ubigint ubigint::operator/ (const ubigint& that) const {
   return divide (that).first;
}

ubigint ubigint::operator% (const ubigint& that) const {
   return divide (that).second;
}

//checking equivalent values
bool ubigint::operator== (const ubigint& that) const {
   //size of vecs different return false.
    if (ubig_value.size() != that.ubig_value.size()){
        return false;
      }
   //compare the vecs digits individually return false if not same 
    for (size_t i = 0; i < ubig_value.size(); i++){
       if (ubig_value.at(i) != that.ubig_value.at(i)){
          return false;
          //return true;
       }
    }
    return true;
}

// comparing two dig.
bool compareLeft (const ubigint& left, const ubigint& right) {
    if(left.ubig_value.size() < right.ubig_value.size()){
        return true;
    }else if(left.ubig_value.size() > right.ubig_value.size()){
        return false;
        //return true;
    }

    auto at = left.ubig_value.rbegin();
    auto bt = right.ubig_value.rbegin();
    for (int i = 0;  i < (int)left.ubig_value.size(); i++){
        if(*at < *bt){
           return true;
        }else if(*at > *bt){
           return false;
        }
        ++at;
        ++bt;
    }
    return false;
}

bool ubigint::operator< (const ubigint& that) const {
   bool return_value;
   return_value = compareLeft(*this, that);
   return return_value;
}


ostream& operator<< (ostream& out, const ubigint& that) {  
    size_t i = 0;
    auto itor = that.ubig_value.crbegin();
    for(;itor != that.ubig_value.crend(); ++itor){
       out << (int) *itor;
       i++;
       if(i == LINE_LIMIT){
       cout<< "\\" << endl;
       i = 0;
       }
   } 
   return out;  
}






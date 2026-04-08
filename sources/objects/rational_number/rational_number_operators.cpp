#include <iostream>
using namespace std;

#include "rational_number.hpp"
#include "rational_number_operators.hpp"

namespace rational_number
{
   RationalNumber operator+(const RationalNumber& a,const RationalNumber& b)
   {
      return a.add(b);
   }

   RationalNumber operator-(const RationalNumber& a,const RationalNumber& b)
   {
      return a.subtract(b);
   }

   RationalNumber operator*(const RationalNumber& a,const RationalNumber& b)
   {
      return a.multiply(b);
   }

   RationalNumber operator/(const RationalNumber& a,const RationalNumber& b)
   {
      return a.divide(b);
   }

   std::ostream& operator<<(std::ostream& os,const RationalNumber& r)
   {
      r.output(os);
      return os;
   }

   std::istream& operator>>(std::istream& is,RationalNumber& r)
   {
      r.input(is);
      return is;
   }
}

#include <iostream>
#include <numeric> // Because of gcd().
using namespace std;

#include "math_helper.hpp"
using namespace math_helper;

#include "rational_number.hpp"

namespace rational_number
{
   RationalNumber::RationalNumber(const intmax_t& n, const intmax_t& d):
            m_numerator { n }, m_denominator { d }
   {
      normalize();
   }

   RationalNumber RationalNumber::add(const RationalNumber& r) const
   {
      return { m_numerator * r.m_denominator 
               + m_denominator * r.m_numerator,
               m_denominator * r.m_denominator };
   }

   RationalNumber RationalNumber::subtract(const RationalNumber& r) const
   {
      return { m_numerator * r.m_denominator 
               - m_denominator * r.m_numerator,
               m_denominator * r.m_denominator };
   }

   RationalNumber RationalNumber:: multiply(const RationalNumber& r) const
   {
      return { m_numerator * r.m_numerator,
               m_denominator * r.m_denominator };
   }

   RationalNumber  RationalNumber::divide(const RationalNumber& r) const
   {
      return { m_numerator * r.m_denominator,
               m_denominator * r.m_numerator };
   }
   
   void RationalNumber::output(ostream& os) const
   {
      os << '('
         << m_numerator
         << '/'
         << m_denominator
         << ')'
         << flush;
   }

   void RationalNumber::input(istream& is)
   {
      char c;
      is >> c
         >> m_numerator
         >> c
         >> m_denominator
         >> c;
   }

   long double RationalNumber::toLongDouble() const
   {
      return static_cast<long double>(m_numerator) /
             static_cast<long double>(m_denominator);
   }

   RationalNumber RationalNumber::input()
   {
      intmax_t numerator { 0 },
               denominator { 1 };
      cout << "numerator: " << flush;
      cin >> numerator;
      do
      {
         cout << "denominator: " << flush;
         cin >> denominator;
         if (denominator == 0)
         {
            cerr << "Error, denominator may not be 0!" 
                 << endl;
         }
      } while (denominator == 0);
      return RationalNumber { numerator, denominator };
   }
   
   void RationalNumber::normalize()
   {
      intmax_t divisor = gcd(m_numerator,m_denominator);
      m_numerator = sign(m_numerator) * sign(m_denominator) 
                    * abs(m_numerator) / divisor;
      m_denominator = abs(m_denominator) / divisor;
   }
}

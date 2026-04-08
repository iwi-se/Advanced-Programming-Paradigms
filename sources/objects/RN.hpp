//RN.hpp by Ulrich Eisenecker, February 15, 2023

#ifndef RN_HPP
#define RN_HPP

#include <iostream>
#include <string>
#include <numeric> // Because of gcd()
#include <cstdlib> // Because of atoll()
#include <cstdint> // Because of maxint_t

intmax_t sign(const intmax_t& n)
{
   if (n < 0)
   {
      return -1;
   }
   if (n > 0)
   {
      return +1;
   }
   return 0;
}

class RationalNumber
{
   public:
      RationalNumber(const std::intmax_t& n = 0, const std::intmax_t& d = 1)
         : m_numerator { n }, m_denominator { d }
      {
         normalize();
      }
      explicit RationalNumber(const std::string& n,const std::string& d)
         : m_numerator { std::atoll(n.c_str()) }, 
           m_denominator { std::atoll(d.c_str()) }
      {
         normalize();
      }
      void output(std::ostream& os) const
      {
         os << '('
            << m_numerator
            << '/'
            << m_denominator
            << ')'
            << std::flush;
      }
   private:
      void normalize()
      {
         intmax_t divisor = std::gcd(m_numerator,m_denominator);
         m_numerator = sign(m_numerator) * sign(m_denominator) 
                       * std::abs(m_numerator) / divisor;
         m_denominator = std::abs(m_denominator) / divisor;
      }
      std::intmax_t  m_numerator { 0 },
                     m_denominator { 1 };
};
#endif // RN_HPP

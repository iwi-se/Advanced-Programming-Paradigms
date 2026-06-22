// Nodiscard.cpp by Ulrich Eisenecker, May 5, 2026

#include <cstdlib>
#include <cstdint> // Because of maxint_t

using namespace std;

class [[nodiscard]] RationalNumber
{
   public:
      RationalNumber(const intmax_t& n = 0,const intmax_t& d = 1):
         m_numerator { n },m_denominator { d }
      {}
      intmax_t numerator() const
      {
         return m_numerator;
      }
      intmax_t denominator() const
      {
         return m_denominator;
      }
      RationalNumber copy() const
      {
         return *this;

      }
   private:
      intmax_t m_numerator,
               m_denominator;
};

int main()
{
   RationalNumber rn { };
   rn.numerator();
   rn.denominator();
   rn.copy(); // Warning: return value not used
   RationalNumber { };     // Temporary not used
   RationalNumber { 1 };   // Temporary not used
   RationalNumber { 1,3 }; // Temporary not used
}

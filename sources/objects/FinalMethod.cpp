// FinalMethod.cpp by Ulrich Eisenecker, February 20, 2023

// Warning: This program does not compile on purpose. 
// It contains a syntactical error and a design error. 
// Fixing the design error also makes the syntactical 
// error disappear.

#include <iostream>
#include <cstdint> // Because of maxint_t

class AbstractRationalNumber
{
   public:
      virtual std::intmax_t numerator() const = 0;
      virtual std::intmax_t denominator() const = 0;
      virtual ~AbstractRationalNumber()
      {};
};

class RationalNumber1: public AbstractRationalNumber
{
   public:
      std::intmax_t numerator() const override
      {
         return 1ll;
      }
      std::intmax_t denominator() const final
      {
         return 1ll;
      }
};

class RationalNumber0: public RationalNumber1
{
   public:
      std::intmax_t numerator() const final
      {
         return 0ll;
      }
};

class RationalNumberI: public RationalNumber0
{
   public:
      RationalNumberI(const std::intmax_t numerator):m_numerator { numerator }
      {}
      std::intmax_t numerator() const final
      {
         return m_numerator;
      }
   private:
      std::intmax_t m_numerator;
};

void test(const AbstractRationalNumber& n)
{
   std::cout << '(' << n.numerator()
             << '/' << n.denominator()
             << ')' << std::endl;

}

int main()
{
   RationalNumber1 one;
   test(one);
   RationalNumber0 zero;
   test(zero);
   RationalNumberI answer { 42 };
   test(answer);
}

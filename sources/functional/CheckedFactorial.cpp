// CheckedFactorial.cpp by Ulrich Eisenecker, October 16, 2025

#include <iostream>
#include <stdexcept>

using ulli_t = unsigned long long int;

namespace variant1
{
   ulli_t checkedFactorial(ulli_t n,ulli_t limit = 20)
   {
      if (n > limit)
      {
         throw std::overflow_error("overflow");
      }
      ulli_t result { 1 };
      while (n)
      {
         result *= n--;
      }
      return result;
   }
}

namespace variant2
{
   ulli_t checkedFactorial(ulli_t n,ulli_t limit)
   {
      if (n > limit)
      {
         throw std::overflow_error("overflow");
      }
      ulli_t result { 1 };
      while (n)
      {
         result *= n--;
      }
      return result;
   }
   ulli_t factorial8b(ulli_t n)
   {
      return checkedFactorial(n,20);
   }
}

using namespace std;

int main()
{
   for (ulli_t i { 10 };i <= 22; ++i)
   {
      cout << i << '\t';
      try
      {
         cout << variant1::checkedFactorial(i,20);
      } catch (const runtime_error& e)
      {
         cout << e.what();
      }
      cout << '\t';
      try
      {
         cout << variant2::factorial8b(i);
      } catch (const runtime_error& e)
      {
         cout << e.what();
      }
      cout << endl;
   }
}



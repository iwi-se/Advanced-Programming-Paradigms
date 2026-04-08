// ComplexLambda.cpp by Ulrich Eisenecker, November 28, 2025

#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

int main()
{
   auto sqr
   {
      [] <class T> [[nodiscard]] (T n) noexcept -> T requires is_arithmetic_v<T>
      { return n * n; }
   };
   cout << sqr(2) << '\t' << sqr(2.1) << endl;
   sqr(1); // The compiler issues a warning.
}

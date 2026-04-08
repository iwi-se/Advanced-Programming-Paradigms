// Factorial.cpp by Ulrich Eisenecker, September 8, 2025

#include <iostream>

unsigned long long int factorial1(unsigned long long int n)
{
   if (n > 0)
   {
      return n * factorial1(n - 1);
   }
   return 1;
}

auto factorial2(unsigned long long int n) -> unsigned long long int
{
   if (n == 0)
   {
      return 1;
   }
   return n * factorial2(n - 1);
}

using namespace std;

int main()
{
   cout << factorial1(5) << endl;
   cout << factorial2(5) << endl;
   return 0;
}


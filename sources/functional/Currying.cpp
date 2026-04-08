// Currying.cpp by Ulrich Eisenecker, January 12, 2026

#include <cmath>
#include <iostream>

auto logarithm(double base,double number)
{
   return std::log(number) / std::log(base);
}

auto logarithm(double base)
{
   return [base](double number) { return std::log(number) / std::log(base); };
}

using namespace std;

int main()
{
   cout << logarithm(2.0,16.0) << endl;
   cout << logarithm(2.0)(16.0) << endl;
   // logarithm to the base 2.0
   auto ld { logarithm(2.0) };
   cout << ld(16.0) << endl;
   // logarithm to the base 10
   const auto log10 { logarithm(10.0) };
   cout << log10(10000.0) << endl;
}

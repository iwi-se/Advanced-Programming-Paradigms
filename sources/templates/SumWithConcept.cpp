// SumWithConcept.cpp by Ulrich Eisenecker, July 22, 2025

#include <iostream>
#include <string>
#include <concepts>

using namespace std;

template <typename T>
concept arithmetic =
   integral<T> ||
   floating_point<T>;

// or alternatively
/*
 template <typename T>
concept arithmetic =
   is_arithmetic_v<T>;
*/

auto sum(const arithmetic auto& ... pack)
{
   return (0.0 + ... + pack); 
}

int main()
{
   cout << sum(3,5.5,2.0,-9) << endl;
}

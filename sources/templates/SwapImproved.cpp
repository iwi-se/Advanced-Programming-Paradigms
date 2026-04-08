// SwapImproved.cpp by Ulrich Eisenecker, June 29, 2023
// Warning: Program does not compile!

#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
concept CanBeSwapped =  
   is_destructible_v<T> &&
   is_copy_constructible_v<T> && 
   is_assignable_v<T&,T>;

void swapVariables(CanBeSwapped auto& a,CanBeSwapped auto& b) 
   requires is_same_v<decltype(a),decltype(b)>
{
   CanBeSwapped auto temp { a };
   a = b;
   b = temp;
}

int main()
{
   double a { 99 };
   swapVariables(a,a); // legal
   int b { 42 };
   swapVariables(a,b); // illegal
}

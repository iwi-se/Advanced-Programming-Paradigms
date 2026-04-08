// SimplifiedLambda.cpp by Ulrich Eisenecker, November 28, 2025

#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

using namespace std;

int main()
{
   auto sqr { [] (arithmetic auto n) { return n * n; } };
   cout << sqr(2) << '\t' << sqr(2.1) << endl;
   sqr(1);
   // sqr("Ups"s); // does not compile.
}

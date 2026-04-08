// SimpleLegacyCasts.cpp by Ulrich Eisenecker, March 21, 2023

#include <iostream>
#include <type_traits>

using namespace std;

int main()
{
   // Traditional cast
   auto usi { (unsigned short int) 5 };
   cout << boolalpha
        << is_same_v<decltype(usi),short unsigned int>
        << endl;

   // Functional cast
   auto ssi { short(5) };
   cout << boolalpha
        << is_same_v<decltype(ssi),short signed int>
        << endl;
}

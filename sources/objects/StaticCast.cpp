// StaticCast.cpp by Ulrich Eisenecker, March 21, 2023

#include <iostream>
#include <type_traits>

using namespace std;

int main()
{
   // Formerly traditional cast, now static_cast
   auto usi { static_cast<unsigned short int>(5) };
   cout << boolalpha
        << is_same_v<decltype(usi),short unsigned int>
        << endl;

   // Formerly functional cast, now static_cast
   auto ssi { static_cast<short>(5) };
   cout << boolalpha
        << is_same_v<decltype(ssi),short signed int>
        << endl;
}

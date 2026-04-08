// TypeTraits.cpp by Ulrich Eisenecker, March 15, 2024

#include <iostream>
#include <type_traits> // Because of is_same_v<>.

using namespace std;

using int_t = int;
int_t i { };
unsigned long int l { };

int main()
{
   cout << "is type of i int? "
        << boolalpha
        << is_same_v<decltype(i),int>
        << endl
        << "is type of l int? "
        << is_same_v<decltype(l),int>
        << endl;
}

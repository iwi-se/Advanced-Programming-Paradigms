// TypeID.cpp by Ulrich Eisenecker, March 30, 2023

#include <iostream>
#include <typeinfo> // Because of typeid.

using namespace std;

using int_t = int;
int_t i { };
unsigned long int l { };

int main()
{
   cout << "is type of i int? "
        << boolalpha
        << (typeid(i) == typeid(int))
        << endl
        << "is type of l int? "
        << (typeid(l) == typeid(int))
        << endl;
}

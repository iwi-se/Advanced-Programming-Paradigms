// UsingConstructors.cpp by Ulrich Eisenecker, February 23, 2023

#include "RN.hpp"

class DerivedRationalNumber: public RationalNumber
{
   using RationalNumber::RationalNumber;
};

int main()
{
   using namespace std;
   DerivedRationalNumber a { 3,5 },
                         b { "4","-7" };
   a.output(cout);
   cout << endl;
   b.output(cout);
   cout << endl;
}

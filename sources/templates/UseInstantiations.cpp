// UseInstantiations.cpp by Ulrich Eisenecker, March 2, 2025

#include "header.hpp"

#include <iostream>
using namespace std;

int main()
{
   int a { 1 }, b { 2 };
   swapVariables(a,b);
   cout << ((a == 2) && (b == 1 )) << endl;

   RingBuffer<bool,3> c;
   c.put(true);
   c.put(false);
   c.put(true);
   cout << (c.get() == true) << endl;
   cout << (c.get() == false) << endl;
   cout << (c.get() == true) << endl;

   double d { 2.3 }, e { 4.5 };
   // swapVariables(d,e);

   // RingBuffer<bool,2> f;
}

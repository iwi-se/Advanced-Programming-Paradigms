// CaptureClause.cpp by Ulrich Eisenecker, November 19, 2025

#include <iomanip> // Because of boolalpha
#include <iostream>

using namespace std; 

int main()
{
   int a { 3 },
       b { 4 };
   cout << "a = " << a << " b = " << b
        << boolalpha << endl;

   cout << "Empty capture clause, smaller value: " <<
      [] (int a,int b) { return a < b ? a : b; } (a,b) << endl;

   cout << "Capturing all local variables by value, smaller value: " <<
      [=] () { return a < b ? a : b; }() << endl;

   cout << "Capturing a by value, larger value: " <<
      [a] (int b) { return a > b ? a : b; }(5) << endl;

   cout << "Capturing all local variables by reference, swapping a and b: ";
      [&] () { int c { a }; a = b; b = c; }();
      cout << a << ' ' << b << endl;

   cout << "As before, but providing c initialized with a, swapping a and b: " ;
      [&,c { a } ] () { a = b; b = c; }();
      cout << a << ' ' << b << endl;
}

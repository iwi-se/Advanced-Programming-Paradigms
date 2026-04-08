// StrictOrder.cpp by Ulrich Eisenecker, March 11, 2026

#include <cmath>
#include <iostream>

using namespace std;

int main()
{
   auto a { (cout << "a", sqrt(4.0)) };
   auto b { (cout << "b", 2 / 4.0) };
   auto c { (cout << "c", 0) };
   cout << (cout << "d",a + b) * c << endl;
}

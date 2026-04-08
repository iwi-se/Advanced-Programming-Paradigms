// ReferentialTransparency.cpp by Ulrich Eisenecker, March 12, 2026

#include <cmath>
#include <iostream>

using namespace std;

int main()
{
   cout << (cout << "d",
           (cout << "a", sqrt(4.0)) +
           (cout << "b", 2 / 4.0)) *
           (cout << "c", 0) << endl;
}

// SwapPointers.cpp by Ulrich Eisenecker, May 4, 2022

#include <iostream>
#include <string>
using namespace std;

template <typename T>
void swapVariables(T& a,T& b)
{
   T temp { a };
   a = b;
   b = temp;
}

int main()
{
   auto x { 42 },
        y { 13 };
   auto pX { &x },
        pY { &y };
   swapVariables(pX,pY);
   cout << x << '\n'<< y
        << endl;
}

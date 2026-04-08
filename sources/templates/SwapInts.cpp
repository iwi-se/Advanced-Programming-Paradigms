// SwapInts.cpp by Ulrich Eisenecker, April 29, 2022

#include <iostream>
using namespace std;

void swapVariables(int& a,int& b)
{
   int temp { a };
   a = b;
   b = temp;
}

int main()
{
   int i1,i2;
   cout << "i1 = ";
   cin >> i1;
   cout << "i2 = ";
   cin >> i2;
   swapVariables(i1,i2);
   cout << "i1 = " << i1
        << "\ni2 = " << i2
        << endl;
}

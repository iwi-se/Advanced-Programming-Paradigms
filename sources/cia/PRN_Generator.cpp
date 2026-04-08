// PRN_Generator.cpp by Ulrich Eisenecker, May 2, 2025

#include <iostream>
#include <random>

using namespace std;

int main()
{
   cout << "Mersenne Twister Engine 32 as pseudo random number generator" << endl;
   mt19937 generator { };
   for (int i { }; i < 5; ++i)
   {
      cout << generator() << endl;
   }
}

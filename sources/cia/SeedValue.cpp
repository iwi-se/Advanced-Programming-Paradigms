// SeedValue.cpp by Ulrich Eisenecker, May 2, 2025

#include <iostream>
#include <random>

using namespace std;

int main()
{ 
   cout << "Pseudo random number generator with seed value" << endl;
   mt19937 generator { random_device { }() }; // Creating temporary random
   for (int i { }; i < 5; ++i)                // device and obtaining a value
   {                                          // as a seed value.
      cout << generator() << endl;
   }
}

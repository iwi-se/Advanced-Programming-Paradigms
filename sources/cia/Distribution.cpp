// Distribution.cpp by Ulrich Eisenecker, May 4, 2025

#include <iostream>
#include <random>

using namespace std;

int main()
{
   cout << "Using normal_distribution without seed value." << endl;
   mt19937_64 generator { };
   normal_distribution bellCurve { };
   for (int i { }; i < 5; ++i)
   {
      cout << bellCurve(generator) << endl;
   }
}

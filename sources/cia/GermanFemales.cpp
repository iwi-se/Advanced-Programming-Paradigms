// GermanFemales.cpp by Ulrich Eisenecker, May 4, 2025

#include <iostream>
#include <random>

using namespace std;

int main()
{
   cout << "Distribution of german females, taken from\n"
        << "https://en.wikipedia.org/wiki/Average_human_height_by_country."
        << endl;
   mt19937 generator { random_device {}() };
   normal_distribution bellCurve { 165.0, 6.7 };
   for (int i { }; i < 5; ++i)
   {
      cout << bellCurve(generator) << endl;
   }
}

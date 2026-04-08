// MapWithDoubles.cpp by Ulrich Eisenecker, July 24, 2025

#include <iostream>
#include <map>

#include "extended_statistics.hpp"

using namespace std;
using namespace statistics;

int main()
{
   auto data { generateRndDtaAsMap<double>
      (normal_distribution { 165.0,6.7 },mt19937_64 { },100000) };
   auto results { calculateParameters(data) };
   outputParameters(cout,results);
   cout << endl;
}

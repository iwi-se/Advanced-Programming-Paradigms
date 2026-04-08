// WrongMean.cpp by Ulrich Eisenecker, July 24, 2025

#include <iostream>
#include <tuple>
#include <vector>

#include "extended_statistics.hpp"

using namespace std;
using namespace statistics;

int main()
{
   cout << "Size";
   for (size_t i { 10 };i <= 100000; i *= 10)
   {
      cout << '\t' << i;
   }
   cout << endl;
   cout << "Mean";
   for (size_t i { 10 };i <= 100000; i *= 10)
   {
      cout << '\t' << get<1>(calcParamsFaster(
                         generateRandomData<int,vector>
                         (normal_distribution { 165.0,6.7 },
                         mt19937_64 { },100000))).second;
   }
   cout << endl;
}

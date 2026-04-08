// StatisticsWithMap.cpp by Ulrich Eisenecker, July 23, 2025

#include <iostream>
#include <map>

#include "extended_statistics.hpp"

using namespace std;
using namespace statistics;

int main()
{
   auto femaleHeights
        { generateRndDtaAsMap<int>(normal_distribution { 165.0,6.7 },
                                   mt19937_64 { },10)
        };
   cout << "Heights of females in cm:" << endl;
   outputData(cout,femaleHeights);
   outputParameters(cout,calculateParameters(femaleHeights));
   cout << endl;
}

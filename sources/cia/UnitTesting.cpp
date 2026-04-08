// UnitTesting.cpp by Ulrich Eisenecker, July 24, 2025

#include <deque>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "extended_statistics.hpp"

using namespace std;
using namespace statistics;

TEST_CASE("Calculations")
{
   auto dv { generateRandomData<int,vector>
                (normal_distribution { 165.0,6.7 },
                                       mt19937_64 { },100000)
           };
   auto rv { calculateParameters(dv) };

   auto dd { generateRandomData<int,deque>
                (normal_distribution { 165.0,6.7 },
                                       mt19937_64 { },100000)
           };
   auto rd { calculateParameters(dd) };

   auto md { generateRndDtaAsMap<int>
                (normal_distribution { 165.0,6.7 },
                 mt19937_64 { },100000)
           };
   auto rm { calculateParameters(md) };

   auto fd { generateRandomData<int,vector>
                (normal_distribution { 165.0,6.7 },
                                       mt19937_64 { },100000)
           };
   auto rf { calcParamsFaster(fd) };

   cout << "\nResults from vector:\n";
   outputParameters(cout,rv);
   cout << "\nResults from deque:\n";
   outputParameters(cout,rd);
   cout << "\nResults from map:\n";
   outputParameters(cout,rm);
   cout << "\nResults from vector/faster:\n";
   outputParameters(cout,rf);
   cout << "\nThe results look identical, right?" << endl;

   REQUIRE(rv == rd);
   //REQUIRE(rv == rm); // Will probably fail.
   //REQUIRE(rv == rf); // Will probably fail.
   //REQUIRE(rd == rm); // Will probably fail.
   //REQUIRE(rd == rf); // Will probably fail.
   REQUIRE(rm == rf);

   ostringstream os;
   outputParameters(os,rv);
   auto rvs { os.str() };
   os.str("");
   outputParameters(os,rd);
   auto rds { os.str() };
   os.str("");
   outputParameters(os,rm);
   auto rms { os.str() };
   os.str("");
   outputParameters(os,rf);
   auto rfs { os.str() };

   REQUIRE(rvs == rds);
   REQUIRE(rvs == rms);
   REQUIRE(rvs == rfs);
   REQUIRE(rds == rms);
   REQUIRE(rds == rfs);
   REQUIRE(rms == rfs);
}


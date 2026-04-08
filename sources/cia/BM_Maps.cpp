// BM_Containers.cpp by Ulrich Eisenecker, July 21, 2025

#include <array>
#include <deque>
#include <list>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "extended_statistics.hpp"

using namespace std;
using namespace statistics;

TEST_CASE("Containers")
{
   BENCHMARK("vector")
   {
      return generateRandomData<int,vector>(normal_distribution { 165.0,6.7 },
                                           mt19937_64 { },100000);
   };
   BENCHMARK("deque")
   {
      return generateRandomData<int,deque>(normal_distribution { 165.0,6.7 },
                                           mt19937_64 { },100000);
   };
   BENCHMARK("list")
   {
      return generateRandomData<int,list>(normal_distribution { 165.0,6.7 },
                                           mt19937_64 { },100000);
   };
}


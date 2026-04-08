// BM_RandomData100.cpp by Ulrich Eisenecker, July 21, 2025

#include "statistics.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

using namespace std;
using namespace statistics;

TEST_CASE("RandomData")
{
   BENCHMARK("100")
   {
      return generateRandomData<int,vector>(normal_distribution { 165.0,6.7 },
                                            mt19937_64 { },10);
   };
}

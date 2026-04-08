// BM_Comprehensive.cpp by Ulrich Eisenecker, July 24, 2025

#include <deque>
#include <map>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

#include "extended_statistics.hpp"

using namespace std;
using namespace statistics;

TEST_CASE("Comprehensive")
{
   BENCHMARK_ADVANCED("vector")(Catch::Benchmark::Chronometer meter)
   {
      auto sample
         { generateRandomData<int,vector>(normal_distribution { 165.0,6.7 },
                                          mt19937_64 { },100000)
         };
      meter.measure([&sample]() { return calculateParameters(sample); });
   };
   BENCHMARK_ADVANCED("deque")(Catch::Benchmark::Chronometer meter)
   {
      auto sample
         { generateRandomData<int,deque>(normal_distribution { 165.0,6.7 },
                                         mt19937_64 { },100000)
         };
      meter.measure([&sample]() { return calculateParameters(sample); });
   };
   BENCHMARK_ADVANCED("map")(Catch::Benchmark::Chronometer meter)
   {
      auto sample
         { generateRndDtaAsMap<int>(normal_distribution { 165.0,6.7 },
                                    mt19937_64 { },100000)
         };
      meter.measure([&sample]() { return calculateParameters(sample); });
   };
   BENCHMARK_ADVANCED("faster")(Catch::Benchmark::Chronometer meter)
   {
      auto sample
         { generateRandomData<int,vector>(normal_distribution { 165.0,6.7 },
                                          mt19937_64 { },100000)
         };
      meter.measure([&sample]() { return calcParamsFaster(sample); });
   };
}

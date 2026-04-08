// BM_RandomData1_1000.cpp by Ulrich Eisenecker, July 21, 2025

#include "statistics.hpp"
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/generators/catch_generators.hpp>

using namespace std;
using namespace statistics;

TEST_CASE("RandomData")
{
   auto iterations { GENERATE(1,10,100,1000) };
   string name {  to_string(iterations) + 'x' +
                  to_string(100000 / iterations)
               };
   BENCHMARK(name.c_str())
   {
      for (size_t i { 0 };i < iterations;++i)
      {
         auto result { generateRandomData<int,vector>
                       (normal_distribution { 165.0,6.7 },
                        mt19937_64 { },100000 / iterations)
                     };
      }
   };
}

// BM_Comprehensive.cpp by Ulrich Eisenecker, July 23, 2025

#include <deque>
#include <map>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "extended_statistics.hpp"

using namespace std;
using namespace statistics;

TEST_CASE("Comprehensive")
{
      auto sample
         { generateRndDtaAsMap<int>(normal_distribution { 165.0,6.7 },
                                    mt19937_64 { },10)
         };
      outputParameters(cout,calculateParameters(sample));
}


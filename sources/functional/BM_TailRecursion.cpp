// BM_TailRecursion.cpp by Ulrich Eisenecker, September 8, 2025

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

unsigned long long int factorial1(unsigned long long int n)
{
   if (n > 0)
   {
      return n * factorial1(n - 1);
   }
   return 1;
}

unsigned long long int factorial_impl(unsigned long long int n,
                                      unsigned long long int& product)
{
   if (n == 0)
   {
      return product;
   }
   /* [[clang::musttail]] */ return factorial_impl(n - 1,product *= n);
}

unsigned long long int factorial2(unsigned long long int n)
{
   unsigned long long int product { 1 };
   return factorial_impl(n,product);
}

unsigned long long int factorial3(unsigned long long int n)
{
   auto product { 1 };
   while (n > 0)
   {
      product *= n--;
   }
   return product;
}

TEST_CASE("Factorial")
{
   BENCHMARK_ADVANCED("Recursion")(Catch::Benchmark::Chronometer meter)
   {
      meter.measure([]() { return factorial1(20); });
   };

   BENCHMARK_ADVANCED("Tail Recursion")(Catch::Benchmark::Chronometer meter)
   {
      meter.measure([]() { return factorial2(20); });
   };

   BENCHMARK_ADVANCED("Iterative")(Catch::Benchmark::Chronometer meter)
   {
      meter.measure([]() { return factorial3(20); });
   };
}

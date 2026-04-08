// FactorialMemo.cpp by Ulrich Eisenecker, October 8, 2025

#include <iostream>
#include <vector>
#include <array>

static_assert(sizeof(unsigned long long int) == 8);

unsigned long long int factorial3(unsigned long long int n)
{
   static std::vector results { 1ull, 1ull, 2ull, 6ull };
   for (auto i { size(results) }; i <= n; ++i)
   {
      results.push_back(results.back() * i);
   }
   return results[n];
}

constexpr auto factorial4(unsigned long long int n)
{
   constexpr static std::array<unsigned long long int,21> results =
      []() { std::array<unsigned long long int,21> f;
             f[0] = 1;
             for (unsigned long long int i { 1 };i <= 20; ++i)
             {
                f[i] = f[i - 1] * i;
             }
             return f;
           } ();
   return results[n];
}

using namespace std;

int main()
{
   for (unsigned long long int i { 0 }; i <= 20; ++i)
   {
      cout << i << '\t' << factorial3(i) << '\t' << factorial4(i) << endl;
   }
   return 0;
}

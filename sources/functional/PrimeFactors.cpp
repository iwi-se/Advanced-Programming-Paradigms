// PrimeFactors.cpp by Ulrich Eisenecker, March 18, 2026

#include <iostream>
#include <functional> // Because of std::multiplies<>()
#include <list>       // Because of list<>
#include <numeric>    // Because of std::accumulate<>()
#include <print>      // Because of println<>()
#include <ranges>
#include <tuple>      // Because of get<>()
#include <utility>    // Because of pair<>

using namespace std;

using ulli_t = unsigned long long int;

auto twoFactors(ulli_t n)
{
   auto factor { n / 2ull };
   while(factor && n % factor)
   {
      --factor;
   }
   return pair { factor,factor ? n / factor : 1 };
}

auto primeFactors(ulli_t n) -> list<ulli_t>
{
   list<ulli_t> primes { };
   auto factors { twoFactors(n) };
   if (factors.second > 1)
   {
      primes.prepend_range(primeFactors(factors.first));
      primes.push_front(factors.second);
   }
   return primes;
}

int main()
{
   auto f1 { views::zip(views::iota(0),
             views::iota(0) | views::transform(primeFactors))
                            | views::drop(2)
                            | views::take(20) };
   println("Numbers and prime factors:\n{}\n",f1);

   auto f2 { f1 | views::transform([](auto p) { return get<1>(p); }) };
   println("Only prime factors:\n{}\n",f2);

   auto f3 { f2 | views::transform([](auto f)
                                   { return accumulate(begin(f),end(f),1,
                                            multiplies<ulli_t>());
                                   }) };
   println("Only products:\n{}\n",f3);

   cout << "Number to calculate prime factors for: ";
   ulli_t n;
   cin >> n;
   println("Prime factors of {}: {}\n",n,
           views::iota(0) | views::transform(primeFactors)
                          | views::drop(n)
                          | views::take(1)
                          | views::join);

}

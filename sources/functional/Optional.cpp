// Optional.cpp by Ulrich Eisenecker, February 12, 2026

#include <iostream>
#include <optional>

using namespace std;

using ulli_t = unsigned long long int;

[[nodiscard]] optional<ulli_t> check(ulli_t n)
{
   if (n > 20ull)
   {
      return { };
   }
   return n;
}

[[nodiscard]] ulli_t plus1(ulli_t n)
{
   return n + 1ull;
}

ulli_t factorial(ulli_t n)
{
   return n ? n * factorial(n - 1) : 1;
}

[[nodiscard]] ulli_t output(ulli_t n)
{
   cout << n << endl;
   return n;
}

template <typename T>
auto operator/(const optional<T>& v,auto f)
{
   return v.transform(f);
}

template <typename T>
auto operator%(const optional<T>& v,auto f)
{
   return v.and_then(f);
}

int main()
{
   check(5ull).transform(plus1).and_then(check)
              .transform(output).transform(factorial)
              .transform(output);
   /* --> */ (check(5ull) / plus1).and_then(check) / output
                          / factorial / output;
   check(20ull).transform(output).transform(plus1)
               .transform(output).and_then(check).transform(factorial)
               .transform(output);
   /* --> */ check(20ull) / output / plus1 / output % check / output
                          / factorial / output;
}

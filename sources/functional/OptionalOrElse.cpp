// OptionalOrElse.cpp by Ulrich Eisenecker, February 12, 2026

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

[[nodiscard]] optional<ulli_t> error()
{
   cerr << "some error happened" << endl;
   return { };
}

[[nodiscard]] optional<ulli_t> truncate()
{
   return 20ull;
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

int main()
{
   check(21ull).or_else(error).transform(factorial).transform(output);

   check(5ull).transform(plus1).and_then(check)
              .or_else(error)
              .or_else(truncate)
              .transform(output).transform(factorial)
              .transform(output);

   check(20ull).transform(output).transform(plus1)
               .transform(output).and_then(check).transform(factorial)
               .transform(output).or_else(truncate)
               .transform(factorial).transform(output);
}

// Expected.cpp by Ulrich Eisenecker, February 12, 2026

#include <expected>
#include <iostream>
#include <string>

using namespace std;

using ulli_t = unsigned long long int;

using ulli_t_or_string = expected<ulli_t,string>;

[[nodiscard]] ulli_t_or_string check(ulli_t n)
{
   if (n > 20ull)
   {
      return unexpected { "argument "s + to_string(n) + " too large."s };
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

[[nodiscard]] ulli_t_or_string error(string s)
{
   cerr << s << endl;
   return unexpected { s };
}

int main()
{
   check(20ull).transform(output).transform(plus1)
               .transform(output).and_then(check).transform(factorial)
               .transform(output)
               .or_else(error);
}

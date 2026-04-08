// Functor.cpp by Ulrich Eisenecker, February 18, 2026

#include <iostream>

using namespace std;

using ulli_t = unsigned long long int;

ulli_t output(ulli_t n)
{
   cout << n << endl;
   return n;
}

[[nodiscard]] ulli_t plus1(ulli_t n)
{
   return n + 1ull;
}

[[nodiscard]] ulli_t factorial(ulli_t n)
{
   return n == 0ull ? 1ull : n * factorial(n - 1ull);
}

template <typename T>
class Functor
{
   private:
      const T m_value;
   public:
      Functor(T v):m_value { v }
      {}
      auto map(auto f) const
      {
         return Functor<decltype(f(m_value))> { f(m_value) };
      }
};

template <typename T>
auto operator|(const Functor<T>& v,auto f)
{
   return v.map(f);
}

int main()
{
   const Functor f5 { 5ull };
   output(5ull);
      /* --> */ f5.map(output);
      /* --> */ f5 | output;
   output(plus1(5ul));
      /* --> */ f5.map(plus1).map(output);
      /* --> */ f5 | plus1 | output;
   output(factorial(plus1(5ull)));
      /* --> */ f5.map(plus1).map(factorial).map(output);
      /* --> */ f5 | plus1 | factorial | output;
}

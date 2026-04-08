// NestedFunctor.cpp by Ulrich Eisenecker, February 18, 2026

#include <iostream>

using namespace std;

using ulli_t = unsigned long long int;

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
      T flatten() const
      {
         return m_value;
      };
      auto bind(auto f) const
      {
         return flatten().map(f);
      }
};

ulli_t output(ulli_t n)
{
   cout << n << endl;
   return n;
}

[[nodiscard]] ulli_t plus1(ulli_t n)
{
   return n + 1ull;
}

[[nodiscard]] auto check(ulli_t n)
{
   return Functor<ulli_t> { n > 20 ? 0 : n };
}

int main()
{
   const Functor f { 20ull };
   // f.map(output).map(plus1).map(check).map(output);
   //                                     ^ Error
   f.map(output).map(plus1).map(check).flatten().map(output);
   //                                            ^ now ok!
   f.map(output).map(plus1).map(check).bind(output);
   //                                  ^ also ok!
}

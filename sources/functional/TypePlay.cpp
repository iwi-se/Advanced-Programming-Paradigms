// TypePlay.cpp by Ulrich Eisenecker, February 19, 2026

#include <iostream>
#include <string>

using namespace std;

template <typename T>
[[nodiscard]] T output(T n);

template<>
[[nodiscard]] double output(double n)
{
   cout << n << endl;
   return n;
}

template<>
[[nodiscard]] string output(string n)
{
   cout << n << endl;
   return n;
}

[[nodiscard]] double grossTotal(double n)
{
   return n * 1.19;
}

[[nodiscard]] string withCurrency(double n)
{
   return to_string(n) + " EUR"s;
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

int main()
{
   const Functor amount { 11.0 };
   amount.map(output<double>).map(grossTotal)
         .map(withCurrency).map(output<string>);
}

// TypePlayCurrying.cpp by Ulrich Eisenecker, February 20, 2026

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

[[nodiscard]] auto grossTotal(double taxrate)
{
   return [taxrate](double n) { return n * (100.0 + taxrate) / 100.0; };
}


[[nodiscard]] auto withCurrency(string mnemonic)
{
   return [mnemonic](double n) { return to_string(n) + " "s + mnemonic; };
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
   amount.map(output<double>).map(grossTotal(19.0))
         .map(withCurrency("EUR")).map(output<string>);
}

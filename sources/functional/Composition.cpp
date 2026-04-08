// Composition.cpp by Ulrich Eisenecker, October 17, 2025

#include <iostream>
#include <optional>
#include <vector>

using ulli_t = unsigned long long int;

class Factorial
{
   public:
      Factorial():m_results {  1ull, 1ull, 2ull, 6ull }
      {
      }
     [[nodiscard]] ulli_t operator()(ulli_t n) const
      {
         for (auto i { size(m_results) }; i <= n; ++i)
         {
            m_results.push_back(m_results.back() * i);
         }
         return m_results[n];
      }
   private:
      mutable std::vector<ulli_t> m_results;
} const factorial5;

class Checking
{
   public:
      Checking(ulli_t limit):m_limit { limit }
      {}
      [[nodiscard]] std::optional<ulli_t> operator()(ulli_t n) const
      {
         if (n > m_limit)
         {
            return std::nullopt; // or alternatively: return { };
         }
         return m_function(n);
      }
   private:
      Factorial m_function;
      ulli_t m_limit;
} const factorial6 { 20 };

std::ostream& operator<<(std::ostream& os,const std::optional<ulli_t>& i)
{
   if (i)
   {
      os << i.value();
   }
   else
   {
      os << "overflow";
   }
   return os;
}

using namespace std;

int main()
{
   for (ulli_t i { 10 }; i <= 22; ++i)
   {
      cout << i << '\t' << factorial5(i) << '\t'
           << factorial6(i) << endl;
   }
   return 0;
}

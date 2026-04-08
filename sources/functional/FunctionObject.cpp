// FunctionObject.cpp by Ulrich Eisenecker, October 16, 2025

#include <iostream>
#include <vector>

using ulli_t = unsigned long long int;

class Factorial
{
   public:
      Factorial():m_results { 1ull, 1ull, 2ull, 6ull }
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

using namespace std;

int main()
{
   for (ulli_t i { 10 }; i <= 22; ++i)
   {
      cout << i << '\t' << factorial5(i) << endl;
   }
   return 0;
}

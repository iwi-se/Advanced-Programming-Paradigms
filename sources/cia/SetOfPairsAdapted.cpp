// SetOfPairsAdapted.cpp by Ulrich Eisenecker, June 6, 2025

#include <functional> // Because of less<>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <ranges>

#include "to_string.hpp"

using namespace std;

template <typename T1,typename T2>
struct less<pair<T1,T2>>
{
   bool operator()(const pair<T1,T2>& lhs,
                   const pair<T1,T2>& rhs) const
   {
      return lhs.first < rhs.first;
   }
};

int main()
{
   set<pair<string,string>>  s { { "X"s,"W"s }, { "X"s,"B"s },
                                 { "A"s,"Z"s }, { "A"s,"C"s },
                                 { "A"s,"C"s }, { "X"s,"B"s } };
   cout << cia::to_string(s | views::transform([](const auto& e)
                              { return e.first + e.second + '\n'; }))
        << endl;
}

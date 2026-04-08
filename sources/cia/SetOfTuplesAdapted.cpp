// SetOfTuplesAdapted.cpp by Ulrich Eisenecker, June 6, 2025

#include <functional> // Because of less<>
#include <iostream>
#include <set>
#include <string>
#include <ranges>
#include <tuple>

#include "to_string.hpp"

using namespace std;

template <typename ... TYPES>
struct less<std::tuple<TYPES ...>>
{
   bool operator()(const tuple<TYPES ...>& lhs,
                   const tuple<TYPES ...>& rhs) const
   {
      return get<0>(lhs) < get<0>(rhs);
   }
};

int main()
{
   set<tuple<char,unsigned,string>>
      s { { 'u',2,"X"s }, { 'u',0,"Y"s }, { 'u',1,"Z"s },
          { 'u',2,"W"s }, { 'A',42,"nn"s }, { 'A',42,"n"s },
          { 'A',42,"nn"s },  { 'u',0,"Y"s }, { 'u',2,"Z"s } };
   cout << cia::to_string(s | views::transform([](const auto& e)
                              { return get<0>(e) +
                                       to_string(get<1>(e)) +
                                       get<2>(e) + '\n';
                              }))
        << endl;
   cout << "The tuple size is "
        << tuple_size_v<decltype(s)::value_type>
        << '.'
        << endl;
}

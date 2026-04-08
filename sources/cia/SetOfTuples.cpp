// SetOfTuples.cpp by Ulrich Eisenecker, June 5, 2025

#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <ranges>
#include <tuple>

#include "to_string.hpp"

using namespace std;

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

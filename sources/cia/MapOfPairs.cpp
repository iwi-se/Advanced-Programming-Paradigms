// MapOfPairs.cpp by Ulrich Eisenecker, June 6, 2025

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <ranges>

#include "to_string.hpp"

using namespace std;

int main()
{
   map<string,string> s { { "X"s,"W"s }, { "X"s,"B"s },
                          { "A"s,"Z"s }, { "A"s,"C"s },
                          { "A"s,"C"s }, { "X"s,"B"s } };
   cout << cia::to_string(s | views::transform([](const auto& e)
                              { return e.first + e.second + '\n'; }))
        << endl;
}

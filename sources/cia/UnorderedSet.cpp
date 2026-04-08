// UnorderedSet.cpp by Ulrich Eisenecker, June 7, 2025

#include <iostream>
#include <unordered_set>
#include <string>
#include <ranges>

#include "to_string.hpp"

using namespace std;

int main()
{
   unordered_set s { 99, -42, 42, 16, 0, 20, -1, 99, 42 };
   cout << cia::to_string(s | views::transform([](const auto& e)
                              { return to_string(e) + ' '; }))
        << endl;
}

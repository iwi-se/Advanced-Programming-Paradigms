// FoldLeft.cpp by Ulrich Eisenecker, August 10, 2025
// Must be compiled with the option -std=c++23

#include <algorithm> // Because of fold_left<>()
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

std::string to_string(const std::ranges::forward_range auto& c)
{
   return std::ranges::fold_left(c,std::string { },
                       [] (auto result,auto element)
                          { return result + element; });
}

using namespace std;

int main()
{
   vector vs { "Eins"s,"Drei"s,"Acht"s };
   cout << to_string(vs) << endl;
   auto lambda { [](auto e){ return std::to_string(e); } };
   vector vi { 1,3,8 };
   cout << to_string(vi | std::views::transform(lambda)) << endl;
   // cout << std::to_string("Not possible."s) << endl;
   // The following line can be compiled and is executed correctly,
   // as the + operator also accepts a character as an operand.
   cout << to_string("This works!"s) << endl;
}

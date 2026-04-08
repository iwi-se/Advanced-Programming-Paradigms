// Join.cpp by Ulrich Eisenecker, March 17, 2026

#include <algorithm>
#include <ranges>
#include <print>
#include <string>
#include <vector>

std::string asString(const std::ranges::range auto& v)
{
   auto strings { std::views::transform(v,[](auto e)
                                          { return std::to_string(e); }) };
   auto joined { std::views::join_with(strings,' ') };
   std::string s { };
   std::ranges::for_each(joined,[&s](auto e) { s += e; });
   return s;
}

using namespace std;

int main()
{
   vector numbers { 1,2,3,4,5 };
   println("numbers: {}\nnumbers as string: \"{}\"",numbers,asString(numbers));

   vector<vector<int>> nested { { 1,2 },{ 3,4 }, { 5,6 } };
   println("nested vector: {}\nflattened string: \"{}\"",
            nested,
            asString(ranges::join_view(nested)));
}

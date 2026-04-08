// ViewMonad.cpp by Ulrich Eisenecker, March 17, 2026

#include <algorithm>
#include <ranges>
#include <print>
#include <string>
#include <vector>

std::string asString(const std::ranges::range auto& v)
{
   std::string s { };
   std::ranges::for_each(std::views::transform(v,[](auto e)
                                                 { return std::to_string(e); }),
                                              [&s](auto e) { s += e; } );
   return s;
}

using namespace std;

int main()
{
   vector many { 2,3,5 };
   println("many {}",asString(many));

   auto one { views::single(22.0 / 7) };
   println("one {}",asString(one));

   auto none { views::empty<bool> };
   println("none {}",asString(none));
}

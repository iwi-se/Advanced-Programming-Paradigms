// Transform.cpp by Ulrich Eisenecker, May 27, 2025

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
   std::vector ints { 5,3,8,1 };
   std::vector<std::string> strings;
   std::transform(begin(ints),end(ints),begin(ints),
                  [](int i) { return i - 1; });
   for (auto e : ints)
   {
      std::cout << e << ' ';
   }
   std::cout << std::endl;
   std::transform(begin(ints),end(ints),std::inserter(strings,end(strings)),
                  [](int i) { return std::to_string(i) + '-'; });
   for (auto e : strings)
   {
      std::cout << e;
   }
   std::cout << std::endl;

}

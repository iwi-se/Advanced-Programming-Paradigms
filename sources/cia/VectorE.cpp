// VectorE.cpp by Ulrich Eisenecker, Fabruary 17, 2026

#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
using namespace std;

int main()
{
   vector values { 9, 0, 7, 2, 8, 1, 6, 3, 4, 5 };
   cout << "Memory used by values: "
        << sizeof(values)
        << endl;
   // Output elements
   {
      cout << "Elements:";
      for (auto element : values)
      {
         cout << ' ' << element;
      }
      cout << endl;
   }
   // Output elements in reversed order
   {
      // Remember lambda in a variable.
      auto lambda { [](auto element)
                      { cout << ' ' << element; }
                  };
      // 1st version
      cout << "Elements:";
      ranges::for_each(ranges::reverse_view(values),lambda);
      cout << endl;
      // 2nd version
      cout << "Elements:";
      ranges::for_each(values | ranges::views::reverse,lambda);
      cout << endl;
   }
}

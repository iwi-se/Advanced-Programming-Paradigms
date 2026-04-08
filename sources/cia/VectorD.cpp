// VectorD.cpp by Ulrich Eisenecker, July 28, 2025

#include <algorithm>
#include <iostream>
#include <vector>

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
   // Reversing the order of elements
   ranges::reverse(values);
   // Output elements
   {
      cout << "Elements:";
      ranges::for_each(values,[](auto element)
                              { cout << ' ' << element; });
      cout << endl;
   }
}

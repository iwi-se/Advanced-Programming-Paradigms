// VectorB.cpp by Ulrich Eisenecker, July 28, 2025

#include <algorithm> // Because of swap<>() and for_each<>().
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
   {
      cout << "Reversing order of elements ..." << endl;
      auto start { size(values) };
      auto stop { start / 2 };
      while (start > stop)
      {
         swap(*(end(values) - start),*(begin(values) + start - 1));
         --start;
      }
   }
   // Output elements
   {
      cout << "Elements:";
      for_each(begin(values),end(values),[](auto element)
                                         { cout << ' ' << element; });
      cout << endl;
   }
}

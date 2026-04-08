// VectorC.cpp by Ulrich Eisenecker, July 28, 2025

#include <algorithm> // Because of reverse<>().
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
   // Reverse iteration over elements
   reverse(begin(values),end(values));
   // Output elements
   {
      cout << "Elements:";
      for_each(begin(values),end(values),[](auto element)
                                         { cout << ' ' << element; });
      cout << endl;
   }
}

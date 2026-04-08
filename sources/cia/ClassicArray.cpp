// ClassicArray.cpp by Ulrich Eisenecker, May 16, 2025

#include <iostream>
#include <iterator> // Because of begin() and end().

using namespace std;

const unsigned int maxSize { 10 };

int main()
{
   int values[maxSize] { 9, 0, 7, 2, 8, 1, 6, 3, 4, 5 };
   cout << "Memory used by values: "
        << sizeof(values)
        << endl;
   // Output elements
   {
      cout << "Elements:";
      for (unsigned int i { }; i < maxSize; ++i)
      {
         cout << ' ' << values[i];
      }
      cout << endl;
   }
   // Reversing order of elements
   {
      cout << "Reversing order of elements ..." << endl;
      auto start { 0u };
      auto stop { maxSize / 2 };
      while (start < stop)
      {
         auto temp { *(values + start) };
         *(values + start) = *(values + maxSize - start - 1);
         *(values + maxSize - start - 1) = temp;
         ++start;
      }
   }
   // Output elements
   {
      cout << "Elements:";
      auto iter { begin(values) };
      while (iter != end(values))
      {
         cout << ' ' << *iter++;
      }
      cout << endl;
   }
}

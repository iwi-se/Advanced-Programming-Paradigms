// VectorA.cpp by Ulrich Eisenecker, July 28, 2025

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
      for (decltype(values)::size_type i { }; i < values.size(); ++i)
      {
         cout << ' ' << values[i];
      }
      cout << endl;
   }
   // Reversing the order of elements
   {
      cout << "Reversing order of elements ..." << endl;
      decltype(values)::size_type start { 0 };
      auto stop { values.size() / 2 };
      while (start < stop)
      {
         auto temp { *(values.begin() + start) };
         *(values.begin() + start) = *(values.end() - start - 1);
         *(values.end() - start - 1) = temp;
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

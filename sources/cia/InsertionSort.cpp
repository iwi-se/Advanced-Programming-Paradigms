// InsertionSort.cpp by Ulrich Eisenecker, July 92, 2025

#include <iostream>
#include <ranges> // Because of views::transform<>().
#include <set>

#include "to_string.hpp" // Because of cia::to_string<>().

using namespace std;

using ElementType = double;
using ContainerType = multiset<ElementType>;

ContainerType readData()
{
   ContainerType data;
   ElementType value;
   while (cin)
   {
      cin >> value;
      if (cin)
      {
         data.insert(value); // The insertion sort takes place here.
      }
   }
   return data;
}

int main()
{
   cout << "Please enter floating point values.\n"
        << "When finished, enter EOF "
        << "(Ctrl-D on macOs and Linux, Ctrl-Z on MS Windows)."
        << endl;
   auto data { readData() };
   size_t counter { };
   cout << "You entered " << size(data) << " values.\n"
        << "Following, they are printed in ascending order.\n"
        << cia::to_string(data | views::transform([&counter](auto e)
                                 { return to_string(++counter) +
                                          ": " + to_string(e) + '\n'; }))
        << endl;
}

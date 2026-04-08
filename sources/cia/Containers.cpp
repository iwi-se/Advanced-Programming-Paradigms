// Containers.cpp by Ulrich Eisenecker, July 28, 2025

#include <algorithm>
#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <ranges> // Because of concept ranges::range.
#include <string>
#include <vector>

using namespace std;

void myMain(ranges::bidirectional_range auto& values)
{
   cout << "Memory used by values: "
        << sizeof(values)
        << endl;
   // Output elements
   cout << "Elements:";
   for (auto element : values)
   {
      cout << ' ' << element;
   }
   cout << endl;
   // Reversing the order of elements
   ranges::reverse(values);
   // Output elements
   cout << "Elements:";
   ranges::for_each(values,[](auto element)
                           { cout << ' ' << element; });
   cout << endl;
}

int main()
{
   array cArray { 9, 0, 7, 2, 8, 1, 6, 3, 4, 5 };
   myMain(cArray);
   vector stdVector { 9, 0, 7, 2, 8, 1, 6, 3, 4, 5 };
   myMain(stdVector);
   deque stdDeque { "9"s, "0"s, "7"s, "2"s, "8"s,
                    "1"s, "6"s, "3"s, "4"s, "5"s };
   myMain(stdDeque);
   list stdList { 9, 0, 7, 2, 8, 1, 6, 3, 4, 5 };
   myMain(stdList);

   forward_list stdFwdList { 9, 0, 7, 2, 8, 1, 6, 3, 4, 5 };
   // myMain(stdFwdList); // Does not compile

   string stdString { "9072816345"s };
   myMain(stdString);
}

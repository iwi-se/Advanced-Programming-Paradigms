// FinalDraw.cpp by Ulrich Eisenecker, August 8, 2025

#include <algorithm> // Because of next_permutation<>();
#include <array>
#include <iostream>
#include <iterator> // Because of begin() and end().
#include <ranges>   // Because of views::transform<>().
#include <string>
#include <vector>

#include "to_string.hpp"
#include "../objects/urn.hpp"

using namespace std;
using namespace urn;

int main()
{
   array<int,10> values { 9, 0, 7, 2, 8, 1, 6, 3, 4, 5 };
   do
   {
      cout << cia::to_string(values | std::views::transform([](auto e)
                                    { return std::to_string(e); })) << endl;
   } while (next_permutation(begin(values),end(values)));

   UrnO urn1 { 3,3 };
   vector urn2 { 0, 1, 2 };
   do
   {
      string draw1 { },
             draw2 { };
      for (uint i { };i < urn1.k(); ++i)
      {
         draw1 += to_string(urn1.at(i));
         draw2 += to_string(urn2.at(i));
      }
      if (draw1 != draw2)
      {
         cerr << "Error comparing urn results!" << endl;
         return 1;
      }
      next_permutation(begin(urn2),end(urn2));
   } while (urn1.next());
   cout << "The urns give identical results." << endl;
}

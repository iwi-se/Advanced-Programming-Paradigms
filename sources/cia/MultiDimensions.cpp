// MultiDimensions.cpp by Ulrich Eisenecker, July 14, 2025

#include <iostream>
#include <mdspan>
#include <numeric> // Because of iota<>().
#include <vector>

using namespace std;

int main()
{
   cout << "1..24 as one dimension with 24 elements\n";
   vector<unsigned int> oneDimensional(24);
   iota(begin(oneDimensional),end(oneDimensional),1);
   for (size_t i { 0 }; i < size(oneDimensional); ++i)
   {
      cout << " i" << i << ": " << oneDimensional[i];
   }

   cout << "\n\n1..24 as two dimensions with 4 rows and 6 columns\n";
   auto twoDimensional { mdspan(oneDimensional.data(),4,6) };
   for (size_t i { 0 }; i < size(oneDimensional) / 6; ++i)
   {
      for (size_t j { 0 }; j < size(oneDimensional) / 4; ++j)
      {
         cout << " i" << i << "|j" << j << ": "
              << twoDimensional[i,j];
      }
      cout << endl;
   }

   cout << "\n\n1..24 as three dimensions with width = 2, "
        << "height = 3 and depth = 4\n";
   auto threeDimensional { mdspan(oneDimensional.data(),2,3,4) };
   for (size_t i { 0 }; i < size(oneDimensional) / 3 / 4; ++i)
   {
      for (size_t j { 0 }; j < size(oneDimensional) / 2 / 4; ++j)
      {
         for (size_t k { 0 }; k < size(oneDimensional) / 2 / 3; ++k)
         {
            cout << " i" << i << "|j" << j << "|k" << k << ": "
                 << threeDimensional[i,j,k];
         }
         cout << endl;
      }
      cout << endl;
   }
   cout << endl;
}

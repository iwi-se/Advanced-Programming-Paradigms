// NamesAndMeans.cpp by Ulrich Eisenecker, July 22, 2025

#include <iostream>
#include <locale> // Because of locale.
#include <string>
using namespace std;

void discardLines(size_t number = 1)
{
   string s;
   while (number && cin)
   {
      getline(cin,s);
      --number;
   }
}

int main()
{
   locale currentLocale { "" }; // Retrieve the current locale.
   cout.imbue(currentLocale); // Set the current locale for cout.
   cout << "Name\tMean\tUnit" << endl;
   discardLines(7); // Remove Cacth2 front lines.
   while (cin)
   {
      discardLines(9); // Remove first lines of benchmark.
      string name;
      cin >> name;
      discardLines(); // Skip rest of line.
      double mean;
      cin >> mean;
      string unit;
      cin >> unit;
      discardLines(); // Skip rest of line.
      discardLines(3); // Skip trailing lines of benchmark.
      cout << name << '\t' << mean << '\t' << unit << endl;
      string line;
      getline(cin,line);
      if (size(line) && line.at(0) == '=') // Check, if the preceding output
      {                                    // was for the last benchmark.
         break; // Leave while loop (could have been done more elegantly).
      }
   }
}

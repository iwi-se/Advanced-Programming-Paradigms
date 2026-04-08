// Sorting.cpp by Ulrich Eisenecker, February 17, 2023

#include <string>
#include <vector>
#include <algorithm> // Because of sort<>
#include <iostream>
#include <cstdlib> // Because of atoll()

using namespace std;

bool ascending(const string& a,const string& b)
{
   return (a < b);
}

bool descending(const string& a,const string& b)
{
   return (a > b);
}

bool numericallyAscending(const string& a,const string& b)
{
   return (atoll(a.c_str()) < atoll(b.c_str()));
}

void sortAndPrint(vector<string> v,bool(*fp)(const string&,const string&))
{
   sort(v.begin(),v.end(),fp);
   for (const auto& e : v)
   {
      cout << e << ' ';
   }
   cout << endl;
}

int main()
{
   cout << boolalpha
        << ascending("B","A") << endl;
   vector someStrings  { "Dog"s,"Cat"s,"Mouse"s,"Zebra"s, "Alligator"s };

   sort(someStrings.begin(),someStrings.end(),ascending);
   for (const auto& s : someStrings)
   {
      cout << s << ' ';
   }
   cout << endl;

   sortAndPrint(someStrings,descending);
   sortAndPrint( { "2"s,"-9"s,"10000"s,"-17"s },numericallyAscending);

   using functionPointerType = bool (*)(const string&,const string&);
   functionPointerType f { numericallyAscending };
   sortAndPrint( { "3"s,"-2"s,"5"s },f);

   f = ascending;
   cout << f("a","b") << endl;
}

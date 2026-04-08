// Static.cpp by Ulrich Eisenecker, February 10, 2023

#include <iostream>
using namespace std;

unsigned int count()
{
   static unsigned c;
   return ++c;
}

int main()
{
   for (auto i { 0u }; i < 10u; ++i)
   {
      cout << count() << endl;
   }
}

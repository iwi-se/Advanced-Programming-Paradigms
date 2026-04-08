// HOFasParameter.cpp by Ulrich Eisenecker, August 27, 2025

#include <iostream>

auto sum(auto func,auto start,decltype(start) stop,decltype(start) increment)
{
   decltype (func(start)) result { }; // Zero initialization
   while (start < stop)
   {
      result += func(start);
      start += increment;
   }
   return result;
}

long long unsigned int identical(long long unsigned int n)
{
   return n;
};

long double reciprocal(int n)
{
   return 1.0L / n;
}

double squared(double n)
{
   return n * n;
}

using namespace std;

int main()
{
   cout << "Sum of numbers from 0 .. 10 step 1: "
        << sum(identical,0,10,1) << endl;
   cout << "Sum of reciprocals from 1 .. 10 step 1: "
        << sum(reciprocal,1,10,1) << endl;
   cout << "Sum of squares from -3 .. 0 step 1: "
        << sum(squared,-3,0,1) << endl;
}

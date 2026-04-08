// SwapMoreSpecialized.cpp by Ulrich Eisenecker, June 4, 2025

#include <iostream>
#include <limits> // Because of numeric_limits<>
#include <string>
using namespace std;

template <typename T>
void swapVariables(T& a,T& b)
{
   T temp { a };
   a = b;
   b = temp;
}

template <typename T>
T inputValue()
{
   T t;
   cin >> t;
   cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
   return t;
}

template <>
string inputValue<string>()
{
   string t;
   getline(cin,t);
   return t;
}

template <typename T>
void demonstrateSwap(char t)
{
   T v1,v2;
   cout << t << "1 = ";
   v1 = inputValue<T>();
   cout << t << "2 = ";
   v2 = inputValue<T>();
   swapVariables(v1,v2);
   cout << t << "1 = " << v1
        << "\n" << t << "2 = " << v2
        << endl;
}

int main()
{
   demonstrateSwap<int>('i');
   demonstrateSwap<double>('d');
   demonstrateSwap<string>('s');
}

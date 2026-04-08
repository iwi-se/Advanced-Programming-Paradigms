// SwapSpecialized.cpp by Ulrich Eisenecker, May 3, 2022

#include <iostream>
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
void demonstrateSwap(char t)
{
   T v1,v2;
   cout << t << "1 = ";
   cin >> v1;
   cout << t << "2 = ";
   cin >> v2;
   swapVariables(v1,v2);
   cout << t << "1 = " << v1
        << "\n" << t << "2 = " << v2
        << endl;
}

template <>
void demonstrateSwap<string>(char t)
{
   using T = string;
   T v1,v2;
   if(cin.peek() == '\n')
   {
      cin.get();
   }
   cout << t << "1 = ";
   getline(cin,v1);
   cout << t << "2 = ";
   getline(cin,v2);
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

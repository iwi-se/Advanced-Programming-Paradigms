// SwapMoreTemplates.cpp by Ulrich Eisenecker, May 3, 2022

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

int main()
{
   demonstrateSwap<int>('i');
   demonstrateSwap<double>('d');
   
   if(cin.peek() == '\n')
   {
      cin.get();
   }
   string s1,s2;
   cout << "s1 = ";
   getline(cin,s1);
   cout << "s2 = ";
   getline(cin,s2);
   swapVariables(s1,s2);
   cout << "s1 = " << s1
        << "\ns2 = " << s2
        << endl;
}

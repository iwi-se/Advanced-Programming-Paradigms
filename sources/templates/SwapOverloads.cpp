// SwapOverloads.cpp by Ulrich Eisenecker, April 29, 2022

#include <iostream>
#include <string>
using namespace std;

void swapVariables(int& a,int& b)
{
   int temp { a };
   a = b;
   b = temp;
}

void swapVariables(double& a,double& b)
{
   double temp { a };
   a = b;
   b = temp;
}

void swapVariables(string& a,string& b)
{
   string temp { a };
   a = b;
   b = temp;
}

int main()
{
   int i1,i2;
   cout << "i1 = ";
   cin >> i1;
   cout << "i2 = ";
   cin >> i2;
   swapVariables(i1,i2);
   cout << "i1 = " << i1
        << "\ni2 = " << i2
        << endl;

   double d1,d2;
   cout << "d1 = ";
   cin >> d1;
   cout << "d2 = ";
   cin >> d2;
   swapVariables(d1,d2);
   cout << "d1 = " << d1
        << "\nd2 = " << d2
        << endl;

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

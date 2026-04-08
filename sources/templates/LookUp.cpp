// LookUp.cpp by Ulrich Eisenecker, July 13, 2022

#include <iostream>
#include <string>
using namespace std;

string message()
{
   return "Uh oh!"s;
}

class Surprise
{
   public:
      string message()
      {
         return "Ah!"s;
      }
};

template <class T>
class SomeTemplate: public T
{
   public:
      SomeTemplate()
      {
         cout << message() << endl;
         cout << T::message() << endl;
         cout << (*this).message() << endl;
      }
/*
string message() 
      {
         return "Oh!"s;
      }
*/
};

int main()
{
   SomeTemplate<Surprise> sts;
}

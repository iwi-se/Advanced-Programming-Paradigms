// UsingPrivateBaseClass.cpp by Ulrich Eisenecker, February 23, 2023

#include <iostream>
using namespace std;

class Fish
{
   public:
      void swim() const
      {
         cout << "I can swim" << endl;
      }
};

class Whale: private Fish
{
   public:
      using Fish::swim;
};

int main()
{
   Fish { }.swim();
   Whale { }.swim();
}

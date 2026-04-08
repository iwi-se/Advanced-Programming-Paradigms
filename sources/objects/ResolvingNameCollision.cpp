// ResolvingNameCollision.cpp by Ulrich Eisenecker, March 7, 2023

#include <iostream>

using namespace std;

class FirstBase
{
   public:
      virtual ~FirstBase() = default;
      virtual void ambiguous() const
      {
         cout << "FirstBase::ambiguous()" << endl;
      }
};

class SecondBase
{
   public:
      virtual ~SecondBase() = default;
      virtual void ambiguous() const
      {
         cout << "SecondBase::ambiguous()" << endl;
      }
};

class Derived: public FirstBase, public SecondBase
{
   public:
      void resolved() const
      {
         // ambiguous(); // Ambiguous --> compilation error
         FirstBase::ambiguous(); // Not ambiguous
         SecondBase::ambiguous(); // Not ambiguous
      }
};

int main()
{
   Derived d;
   d.resolved();
   // d.ambiguous(); // Ambiguous --> compilation error
   d.FirstBase::ambiguous(); // Not ambiguous
   d.SecondBase::ambiguous(); // Not ambiguous
}

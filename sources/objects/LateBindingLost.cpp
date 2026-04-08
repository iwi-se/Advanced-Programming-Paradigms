// LateBindingLost.cpp by Ulrich Eisenecker, February 4, 2025

#include <iostream>
using namespace std;

class GrandParent
{
   public:
      GrandParent()
      {
         cout << "GrandParent::GrandParent(): ";
         virtualFunction();
      }
      void nonVirtualFunction() const
      {
         cout << "nonVirtualFunction(): ";
         virtualFunction();
      }
      virtual ~GrandParent()
      {
         cout << "GrandParent~GrandParent(): ";
         virtualFunction();
      };
      virtual void virtualFunction() const
      {
         cout << "GrandParent::virtualFunction()" << endl;
      }
};

class Parent: public GrandParent
{
   public:
      Parent()
      {
         cout << "Parent::Parent(): ";
         virtualFunction();
      }
      void virtualFunction() const override
      {
         cout << "Parent::virtualFunction()" << endl;
      }
};

class Child: public Parent
{
   public:
      Child()
      {
         cout << "Child::Child(): ";
         virtualFunction();
      }
      void virtualFunction() const override
      {
         cout << "Child::virtualFunction()" << endl;
      }
};


int main()
{
   Child c;
   c.nonVirtualFunction();
}

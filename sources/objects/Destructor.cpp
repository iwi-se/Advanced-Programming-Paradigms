// Destructor.cpp by Ulrich Eisenecker, February 17, 2023

#include <iostream>
#include <array>
using namespace std;

class Base
{
   public:
      Base()
      {
         cout << "Base::Base()" << endl;
      }
      ~Base()
      {
         cout << "Base::~Base()" << endl;
      }
   private:
     unsigned char m_base_data;
};

class Derived: public Base
{
   public:
      Derived()
      {
         cout << "Derived::Derived()" << endl;
      }
      ~Derived()
      {
         cout << "Derived::~Derived()" << endl;
      }
   private:
      array<unsigned char,1024 * 1024> m_derived_data;
};

int main()
{
   cout << "Assigning new Base to Base * and delete it afterwards." 
        << endl;
   Base * basePointer { new Base };
   delete basePointer;

   cout << "\nAssigning new Derived to Derived * and delete it afterwards." 
        << endl;
   Derived * derivedPointer { new Derived };
   delete derivedPointer;

   cout << "\nAssigning new Derived to Base * and delete it afterwards." 
        << endl;
   Base * actuallyDerivedPointer { new Derived };
   delete actuallyDerivedPointer; // Ouch!
}

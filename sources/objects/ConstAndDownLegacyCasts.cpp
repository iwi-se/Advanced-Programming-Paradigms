// ConstAndDownLegacyCasts.cpp by Ulrich Eisenecker, March 21, 2023

#include <iostream>
#include <string>

using namespace std;

class Base
{
   public:
      [[nodiscard]] string staticTypename()
      {
         return "Base";
      }
      [[nodiscard]] virtual string dynamicTypename()
      {
         return "Base";
      }
      virtual ~Base() = default;
};

class Derived: public Base
{
   public:
      [[nodiscard]] string staticTypename()
      {
         return "Derived";
      }
      [[nodiscard]] string dynamicTypename() override
      {
         return "Derived";
      }
};

const Base& test(Base& b)
{
   cout << "Static type: " << b.staticTypename() 
        << '\t'
        << "dynamic type: " << b.dynamicTypename()
        << endl;
   return b;
}

int main()
{
   Base b;
   Derived d;

   test(b);
   test(d);
   
   cout << endl;

   Derived& d1 { (Derived&) test(d) };

   cout << d1.staticTypename()
        << endl;

   using DerivedRef = Derived&;

   Derived& d2 { DerivedRef(test(d)) };

   cout << d2.staticTypename()
        << endl;
}

// DynamicCast.cpp by Ulrich Eisenecker, May 8, 2024

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

   const Derived& d1 { dynamic_cast<const Derived&>(test(d)) };

   cout << const_cast<Derived&>(d1).staticTypename()
        << endl;

   const Derived* d2 { dynamic_cast<const Derived*>(&(test(d))) };

   if (d2 != nullptr)
   {
      cout << const_cast<Derived*>(d2)->staticTypename()
           << endl;
   }

   // The following static_cast<>() is invalid,
   // but not reported as an error.
   const Derived& d3 { static_cast<const Derived&>(test(b)) };
   // The following line leads to nonsensical results.
   cout << const_cast<Derived&>(d3).staticTypename() << endl;
   // The following line produces a correct result.
   cout << const_cast<Derived&>(d3).dynamicTypename() << endl;

   // The following dynamic_cast is invalid
   // and causes a runtime error.
   const Derived& d4 { dynamic_cast<const Derived&>(test(b)) };
}

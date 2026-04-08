// ConstCast.cpp by Ulrich Eisenecker, March 23, 2023

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

   cout << const_cast<Base&>(test(b)).dynamicTypename() << endl;
   cout << const_cast<Base&>(test(d)).dynamicTypename() << endl;
}

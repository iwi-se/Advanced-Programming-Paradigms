// DynamicType.cpp by Ulrich Eisenecker, March 30, 2023

#include <iostream>
#include <typeinfo> // Because of typeid.

using namespace std;

class A
{
   public:
      virtual ~A() = default;
};

class B: public A
{ };

class C: public B
{ };

int main()
{
   C c;
   A& casa { c };
   cout << boolalpha
        << "Is casa an A? "
        << (typeid(casa) == typeid(A))
        << endl
        << "Is casa a B? "
        << (typeid(casa) == typeid(B))
        << endl
        << "Is casa a C? "
        << (typeid(casa) == typeid(C))
        << endl;
}

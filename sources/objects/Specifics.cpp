// Specifics.cpp by Ulrich Eisenecker, May 20, 2025

#include <iostream>
#include <type_traits> // Because of is_same_v<>,
#include <typeinfo> // Because of typeid.

using namespace std;

class A
{
   public:
      virtual ~A() = default;
};

class B: public A
{ };

B notEvaluated()
{
   cout << "Not evaluated ";
   return B { };
}

A& evaluated(A& a)
{
   cout << "Evaluated ";
   return a;
}

A* alsoEvaluated(A& a)
{
   cout << "alsoEvaluated ";
   return &a;
}

int main()
{
   B aB;
   int a { 42 };
   const int& b { a };
   
   cout << boolalpha
        << "const is relevant for is_same_v<>: "
        << is_same_v<int,const int>
        << endl
        << "reference is relevant for is_same_v<>: "
        << is_same_v<int,int&>
        << endl
        << "Use remove_cvref_t<> to remove const, volatile or reference: "
        << is_same_v<int,remove_cvref_t<decltype(b)>>
        << endl
        << "const is NOT relevant for typeid: "
        << (typeid(int) == typeid(const int))
        << endl
        << "type_info.name() returns implementation specific value: "
        << typeid(std::type_info).name()
        << endl
        << "type_info.hash_code() returns implementation specific value: "
        << typeid(std::type_info).hash_code()
        << endl
        << "Operand of typeid is NOT evaluated "
           "if the type can be determined statically: "
        << typeid(notEvaluated()).name()
        << endl
        << "Operand of typeid IS evaluated "
           "if the type cannot be determined statically: "
        << typeid(evaluated(aB)).name()
        << endl
        << "Operand of typeid IS evaluated "
           "if the type cannot be determined statically: "
        << typeid(*alsoEvaluated(aB)).name()
        << endl;
}

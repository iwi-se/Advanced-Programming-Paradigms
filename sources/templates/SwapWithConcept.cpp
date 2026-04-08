// SwapWithConcept.cpp by Ulrich Eisenecker, June 29, 2023
// Warning: Program does not compile!

#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
concept CanBeSwapped =  
   is_destructible_v<T> &&
   is_copy_constructible_v<T> && 
   is_assignable_v<T&,T>;

template <CanBeSwapped T>
void swapVariables(T& a,T& b)
{
   T temp { a };
   a = b;
   b = temp;
}

class NoCopyConstructor
{
   public:
      NoCopyConstructor()
      {}
      NoCopyConstructor(const NoCopyConstructor&) = delete;
};

class NoAssignmentOperator
{
   public:
      NoAssignmentOperator& operator=(const NoAssignmentOperator&) = delete;
};

class NoDestructor
{
   public:
      ~NoDestructor() = delete;
};

int main()
{
   {
      NoCopyConstructor a,b;
      swapVariables(a,b);
   }

   {
      NoAssignmentOperator a,b;
      swapVariables(a,b);
   }

   {
      NoDestructor* a = new NoDestructor();
      NoDestructor* b = new NoDestructor();
      swapVariables(*a,*b);
   }
   {
      int a { 99 }, b { 42 };
      swapVariables(a,b);
   }
}


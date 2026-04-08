// SwapChecked.cpp by Ulrich Eisenecker, May 27, 2022
// Warning: Program does not compile!

#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
void swapVariables(T& a,T& b)
{
   static_assert(is_destructible<T>::value == true,
                 "No destructor available for T");
   static_assert(is_copy_constructible<T>::value == true,
                 "No copy constructor available for T");
   static_assert(is_assignable<T&,T>::value == true,
                 "No assignment operator available for T");
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
}


// UnmetRequirements.cpp by Ulrich Eisenecker, April 29, 2022
// Warning: Program does not compile!

#include <iostream>
using namespace std;

template <typename T>
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
}


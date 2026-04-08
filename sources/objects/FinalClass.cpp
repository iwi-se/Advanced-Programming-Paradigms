// FinalAndClass.cpp by Ulrich Eisenecker, February 20, 2023
// Warning: This program will not compile on purpose!

#include <type_traits>

class DontUseAsBaseClass
{
   // This class does not have
   // a virtual destructor. Thus, 
   // it does not qualify as a base
   // class, but it can still be
   // used as such, although
   // this should not be done.
   
   // Decomment the next line for 
   // providing a virtual destructor.
   // public: virtual ~DontUseAsBaseClass() {};
};

class ChildWithBadParent: public DontUseAsBaseClass
{
   // This class is poorly designed
   // and implemented because it 
   // inherits from a base class
   // which does not have a virtual
   // destructor.

   // Nevertheless, meta-programming can
   // be used to check for the presence
   // of a virtual destructor in the
   // base class.
   static_assert(std::has_virtual_destructor_v<DontUseAsBaseClass>,
                 "Base class has no virtual destructor!");
};

class NotABaseClass final
{
};

class ImpossibleChild: public NotABaseClass
{
};

int main()
{
}

// booleanvariant.hpp by Ulrich Eisenecker, February 25, 2026

#ifndef BOOLEANVARIANT_HPP
#define BOOLEANVARIANT_HPP

#include <iostream>
#include <variant>

namespace booleanvariant
{
   class False
   {};

   class True
   {};

   using Boolean = std::variant<False,True>;

   std::ostream& operator<<(std::ostream& os,False)
   {
      os << "False";
      return os;
   }

   std::ostream& operator<<(std::ostream& os,True)
   {
      os << "True";
      return os;
   }

   constexpr True operator!(False)
   {
      return True { };
   }

   constexpr False operator!(True)
   {
      return False { };
   }

   constexpr True operator==(False,False)
   {
      return True { };
   }

   constexpr False operator==(False,True)
   {
      return False { };
   }

   constexpr False operator==(True,False)
   {
      return False { };
   }

   constexpr True operator==(True,True)
   {
      return True { };
   }

   constexpr False operator&&(False,False)
   {
      return False { };
   }

   constexpr False operator&&(False,True)
   {
      return False { };
   }

   constexpr False operator&&(True,False)
   {
      return False { };
   }

   constexpr True operator&&(True,True)
   {
      return True { };
   }

   constexpr False operator||(False,False)
   {
      return False { };
   }


   constexpr True operator||(False,True)
   {
      return True { };
   }

   constexpr True operator||(True,False)
   {
      return True { };
   }

   constexpr True operator||(True,True)
   {
      return True { };
   }

} // namespace booleanvariant

#endif // BOOLEANVARIANT_HPP

// booleanenum.hpp by Ulrich Eisenecker, February 25, 2026

#ifndef BOOLEANENUM_HPP
#define BOOLEANENUM_HPP

#include <iostream>

namespace booleanenum
{
   enum class Boolean
   {
      False,
      True
   };

   std::ostream& operator<<(std::ostream& os,const Boolean& b)
   {
      os << (b == Boolean::False ? "False" : "True");
      return os;
   }

   constexpr Boolean operator!(const Boolean& b)
   {
      if (b == Boolean::False)
      {
         return Boolean::True;
      }
      return Boolean::False;
   }

   constexpr Boolean operator&&(const Boolean& p1,const Boolean& p2)
   {
      return (p1 == Boolean::True) && (p2 == Boolean::True) ?
             Boolean::True : Boolean::False;
   }

   constexpr Boolean operator||(const Boolean& p1,const Boolean& p2)
   {
      return (p1 == Boolean::True) || (p2 == Boolean::True) ?
             Boolean::True : Boolean::False;
   }

} // namespace booleanenum

#endif // BOOLEANENUM_HPP

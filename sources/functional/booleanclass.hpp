// booleanclass.hpp by Ulrich Eisenecker, March 4, 2026

#ifndef BOOLEANCLASS_HPP
#define BOOLEANCLASS_HPP

#include <concepts> // Because of std::is_derived_from<>
#include <iostream>
#include <typeinfo> // Because of typeid()
#include <type_traits> // Because of std::is_same_v<>

namespace booleanclass
{
   class Boolean
   {
      public:
         virtual ~Boolean() = default;
         virtual void output(std::ostream& os) const = 0;
   };

   class False final : public Boolean
   {
      public:
         void output(std::ostream& os) const override
         {
            os << "False";
         }
   };

   class True final : public Boolean
   {
      public:
         void output(std::ostream& os) const override
         {
            os << "True";
         }
   };
   std::ostream& operator<<(std::ostream& os,const False& f)
   {
      f.output(os);
      return os;
   }


   std::ostream& operator<<(std::ostream& os,const True& t)
   {
      t.output(os);
      return os;
   }

   std::ostream& operator<<(std::ostream& os,const Boolean& b)
   {
      b.output(os);
      return os;
   }

   constexpr const True operator!(const False&)
   {
      return True { };
   }

   constexpr const False operator!(const True&)
   {
      return False { };
   }

   const Boolean& operator!(const Boolean& b)
   {
      static const True t { };
      static const False f { };
      if (typeid(b) == typeid(True))
      {
         return f;
      }
      return t;
   }

   template <class T1,class T2>
   constexpr const False operator==(const T1&,const T2&)
         requires std::derived_from<T1,Boolean> &&
                  std::derived_from<T2,Boolean> &&
                  (!std::is_same_v<T1,Boolean>) &&
                  (!std::is_same_v<T2,Boolean>)
   {
      return False { };
   }

   template <class T>
   constexpr const True operator==(const T&,const T&)
         requires std::derived_from<T,Boolean>
   {
      return True { };
   }

   const Boolean& operator==(const Boolean& p1,const Boolean& p2)
   {
      static const True t { };
      static const False f { };
      if (typeid(p1) == typeid(p2))
      {
         return t;
      }
      return f;
   }

   constexpr const False operator&&(const False&,const Boolean&)
   {
      return False { };
   }

   constexpr const False operator&&(const True&,const False&)
   {
      return False { };
   }

   constexpr const True operator&&(const True&,const True&)
   {
      return True { };
   }

   const Boolean& operator&&(const Boolean& p1,const Boolean& p2)
   {
      static const True t { };
      static const False f { };
      if (typeid(p1) == typeid(True) && typeid(p2) == typeid(True))
      {
         return t;
      }
      return f;
   }

   constexpr const False operator||(const False&,const False&)
   {
      return False { };
   }

   constexpr const True operator||(const False&,const True&)
   {
      return True { };
   }

   constexpr const True operator||(const True&,const False&)
   {
      return True { };
   }

   constexpr const True operator||(const True&,const True&)
   {
      return True { };
   }

   const Boolean& operator||(const Boolean& p1,const Boolean& p2)
   {
      static const True t { };
      static const False f { };
      if (typeid(p1) == typeid(True) || typeid(p2) == typeid(True))
      {
         return t;
      }
      return f;
   }

} // namespace booleanclass

#endif // BOOLEANCLASS_HPP

// oid_manager.hpp by Ulrich Eisenecker, March 28, 2023

#ifndef OID_MANAGER_HPP
#define OID_MANAGER_HPP

#include <map>

namespace oid_manager
{

   class Object
   {
      public:
         virtual ~Object()
         {}
   };

   class OIDManager
   {
      public:
         [[nodiscard]] static bool isKnown(const Object& o)
         {
            return m_ids.find(&o) != m_ids.end();
         }
         [[nodiscard]] static std::size_t getId(const Object& o)
         {
            if (!isKnown(o))
            {
               m_ids[&o] = ++m_id;
            }
            return m_ids[&o];
         }
         static bool deregister(const Object& o)
         {
            if (isKnown(o))
            {
               m_ids.erase(m_ids.find(&o));
               return true;
            }
            return false;
         }
      private:
         inline static std::size_t m_id { 0 };
         static inline std::map<const Object*,std::size_t> m_ids;
   };
}
#endif // OID_MANAGER_HPP

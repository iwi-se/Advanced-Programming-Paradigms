// persistence.hpp by Ulrich Eisenecker, May 19, 2025

#ifndef PERSISTENCE_HPP
#define PERSISTENCE_HPP

#include <map>
#include <iostream>
#include <limits> // Because of numeric_limits<std::streamsize>::max()

namespace persistence
{
   using IdType = std::size_t; // Provide a single point for changing the type
                               // of object IDs.

   class Persistable
   {
      public:
         virtual void serialize(std::ostream& os,
                                const bool endline = true) const = 0;
         virtual void deserialize(std::istream& is,
                                  const bool endline = true) = 0;
         virtual void updateAssociations()
         {
           // Nothing to update for Persistable.
         }
         virtual ~Persistable() = default;
         inline static constexpr char separator { '\t' };
         static void nextLine(std::istream& is)
         {
            is.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); 
         }
         static void nextToken(std::istream& is)
         {
            is.ignore(1,separator);
         }
   };

   static_assert(sizeof(IdType) == sizeof(Persistable*),
                 "Incompatible sizes");

   class OIDManager
   {
      public:
         [[nodiscard]] static bool isKnown(const Persistable& o)
         {
            return m_ids.find(&o) != m_ids.end();
         }
         [[nodiscard]] static bool isKnown(IdType id)
         {
            return m_addresses.find(id) != m_addresses.end();
         }
         [[nodiscard]] static IdType getId(const Persistable& o)
         {
            if (!isKnown(o))
            {
               m_ids[&o] = ++m_id;
            }
            return m_ids[&o];
         }
         [[nodiscard]] static 
            persistence::Persistable* getAddress(IdType id)
         {
            if (!isKnown(id))
            {
               return nullptr;
            }
            return m_addresses[id];
         }
         static bool deregister(const Persistable& o)
         {
            if (isKnown(o))
            {
               auto id { getId(o) }; // Find id and remember it.
               m_ids.erase(m_ids.find(&o));
               if (isKnown(id)) // If id is still known, the corresponding
               {                // entry in m_addresses is deleted.
                  m_addresses.erase(m_addresses.find(id));
               }
               return true;
            }
            return false;
         }
         static bool doregister(IdType id,Persistable* p)
         {
            if (isKnown(id))
            {
               return false;
            }
            m_addresses[id] = p;
            m_ids[p] = id; 
            if (id > m_id) // Just continuosly updating m_id!
            {
               m_id = id;
            }
            return true;
         }
         static void reset()
         {
            m_id = 0;
            m_ids.clear();
            m_addresses.clear();
         }
         static void updateAssociations()
         {
            for (auto& idAddress : m_addresses)
            {
               idAddress.second->updateAssociations();
            }
         }
      private:
         inline static IdType m_id { 0 };
         static inline std::map<const Persistable*,IdType> m_ids;
         static inline std::map<IdType,Persistable*> m_addresses;
   };

   void Persistable::serialize(std::ostream& os,const bool endline) const
   {
      // Since Persistable is an abstract class, it must not
      // be called with endline = true.
      auto id { OIDManager::getId(*this) };
      os << id;
   }

   std::ostream& operator<<(std::ostream& os,const Persistable& p)
   {
      p.serialize(os);
      return os;
   }

   void Persistable::deserialize(std::istream& is,const bool endline)
   {
      // Since Persistable is an abstract class, it must not
      // be called with endline = true.
      IdType id;
      is >> id;
      OIDManager::doregister(id,this);
   }

   std::istream& operator>>(std::istream& is,Persistable& p)
   {
      p.deserialize(is);
      return is;
   }
}

#endif // PERSISTENCE_HPP

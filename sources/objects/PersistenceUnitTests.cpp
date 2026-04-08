// PersistenceUnitTests.cpp by Ulrich Eisenecker, March 18, 2025

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
// This code is based on Catch2 v3,
// therefore only the minimal header
// file for test macros is included.
// The C++ library path must be set
// accordingly for compilation and
// linking, and the Catch2Main and
// Catch2 libraries must be linked
// explicitly in exactly this order!

#include "persistence.hpp"
#include <string>
#include <iostream>
#include <set>
#include <sstream>
#include <cstdlib> // Because of exit()

class Object: public persistence::Persistable
{
   public:
      void serialize(std::ostream& os,
                     const bool endline = true) const override
      {
         persistence::Persistable::serialize(os,false);
         if (endline == true)
         {
            os << std::endl;
         }
      }
      void deserialize(std::istream& is,const bool endline = true) override
      {
         persistence::Persistable::deserialize(is,false);
         if (endline == true)
         {
            nextLine(is);
         }
      }
};

class Person: public persistence::Persistable
{
   public:
      Person(const std::string& name): m_name { name }
      {}
      void introduce(const Person& p)
      {
         m_acquaintances.insert(&p);
      }
      void print() const
      {
         std::cout << "I\'m " << m_name;
         if (m_acquaintances.size() > 0)
         {
            std::cout << " and I know ";
         }
         for (std::size_t i { 1 };const auto& a : m_acquaintances)
         {
            std::cout << a->m_name;
            if (i < m_acquaintances.size() - 1)
            {
               std::cout << ", ";
            }
            if (i == m_acquaintances.size() - 1)
            {
               std::cout << " and ";
            }
            ++i;
         }
         std::cout << '.' << std::endl;
      }
      void serialize(std::ostream& os,
                             const bool endline = true) const override
      {
         Persistable::serialize(os,false);
         os << separator
            << m_name << separator
            << m_acquaintances.size();
         for (auto& a : m_acquaintances)
         {
            os << separator << persistence::OIDManager::getId(*a);
         }
         if (endline == true)
         {
            os << std::endl;
         }
      }
      void deserialize(std::istream& is,const bool endline = true) override
      {
         persistence::Persistable::deserialize(is,false);
         nextToken(is);
         std::getline(is,m_name,separator);
         std::size_t numberOfPeople,
                     id;
         is >> numberOfPeople;
         while (numberOfPeople > 0)
         {
            nextToken(is);
            is >> id;
            m_acquaintances.insert(reinterpret_cast<Person*&>(id));
            --numberOfPeople;
         }
         if (endline == true)
         {
            nextLine(is);
         }
      }
      void updateAssociations() override
      {
         std::set<const Person*> acquaintances;
         for (auto& id : m_acquaintances)
         {
            auto address { persistence::OIDManager::
                           getAddress(reinterpret_cast<const std::size_t&>
                           (id))
                         };
            if (address == nullptr)
            {
               std::cerr << "Cannot convert id to address." << std::endl;
               exit(1);
            }
            else
            {
              auto person { static_cast<Person*>(address) };
              acquaintances.insert(person);
            }
         }
         m_acquaintances.swap(acquaintances);
      }
   private:
      std::string m_name;
      std::set<const Person*> m_acquaintances;
};

TEST_CASE("OIDMANAGER")
{
   using namespace persistence;
   OIDManager::reset();
   Object o1,o2;
   REQUIRE(OIDManager::isKnown(o1) == false);
   REQUIRE(OIDManager::getId(o1) == 1ll);
   REQUIRE(OIDManager::isKnown(o1) == true);
   REQUIRE(OIDManager::isKnown(o2) == false);
   REQUIRE(OIDManager::getId(o2) == 2ll);
   REQUIRE(OIDManager::isKnown(o2) == true);
   REQUIRE(OIDManager::deregister(o1) == true);
   REQUIRE(OIDManager::deregister(o2) == true);
   REQUIRE(OIDManager::deregister(o1) == false);
   REQUIRE(OIDManager::deregister(o2) == false);
   OIDManager::reset();
   REQUIRE(OIDManager::isKnown(o1) == false);
   REQUIRE(OIDManager::isKnown(o2) == false);
   REQUIRE(OIDManager::doregister(1,&o1) == true);
   REQUIRE(OIDManager::doregister(1,&o1) == false);
   REQUIRE(OIDManager::doregister(1,&o2) == false);
   REQUIRE(OIDManager::isKnown(o1) == true);
   REQUIRE(OIDManager::getId(o1) == 1ll);
   REQUIRE(OIDManager::doregister(2,&o2) == true);
   REQUIRE(OIDManager::doregister(2,&o2) == false);
   REQUIRE(OIDManager::doregister(2,&o1) == false);
   REQUIRE(OIDManager::isKnown(o2) == true);
   REQUIRE(OIDManager::getId(o2) == 2ll);
}

TEST_CASE("OBJECT")
{
   using namespace persistence;
   using namespace std;
   OIDManager::reset();
   Object o1,o2;

   ostringstream os1;
   o1.serialize(os1);
   o2.serialize(os1);

   OIDManager::reset();
   istringstream is1 { os1.str() };
   o1.deserialize(is1);
   o2.deserialize(is1);

   ostringstream os2;
   o1.serialize(os2);
   o2.serialize(os2);
   REQUIRE(os1.str() == os2.str());

   OIDManager::reset();
   ostringstream os3;
   os3 << o1 << o2 << flush;
   OIDManager::reset();
   istringstream is2 { os3.str() };
   is2 >> o1 >> o2;
   ostringstream os4;
   os4 << o1 << o2 << flush;
   REQUIRE(os3.str() == os4.str());
}

TEST_CASE("PERSONS_SERIALIZE")
{
   using namespace persistence;
   using namespace std;
   OIDManager::reset();
   Person p1 { "Arnet" },
          p2 { "Marn" },
          p3 { "Fry" },
          p4 { "Kat" },
          p5 { "Tat" },
          p6 { "Pash" },
          p7 { "Pesh" };

   p1.introduce(p2);
   p1.introduce(p3);
   p1.introduce(p4);
   p2.introduce(p1);
   p2.introduce(p5);
   p3.introduce(p6);
   p4.introduce(p2);
   p4.introduce(p3);
   p5.introduce(p6);
   p7.introduce(p7);

   p1.print();
   p2.print();
   p3.print();
   p4.print();
   p5.print();
   p6.print();
   p7.print();

   ostringstream persons;
   persons << p1 << p2 << p3 << p4 << p5 << p6 << p7 << std::flush;
   constexpr auto& s { Persistable::separator };
   string content { "1"s + s + "Arnet"s + s
                         + "3"s + s + "2"s + s + "3"s + s + "4\n"
                    "4"s + s + "Marn"s + s + "2"s + s + "5"s + s + "1\n"
                    "3"s + s + "Fry"s + s + "1"s + s + "6\n"
                    "2"s + s + "Kat"s + s + "2"s + s + "3"s + s + "4\n"
                    "5"s + s + "Tat"s + s + "1"s + s + "6\n"
                    "6"s + s + "Pash"s + s + "0\n"
                    "7"s + s + "Pesh"s + s + "1"s + s + "7\n"
                  };
   REQUIRE(persons.str() == content);
}

TEST_CASE("PERSONS_DESERIALIZE")
{
   using namespace persistence;
   using namespace std;

   Person p1 { "" },
          p2 { "" },
          p3 { "" },
          p4 { "" },
          p5 { "" },
          p6 { "" },
          p7 { "" };

   constexpr auto& s { Persistable::separator };
   string content { "1"s + s + "Arnet"s + s
                         + "3"s + s + "2"s + s + "3"s + s + "4\n"
                    "4"s + s + "Marn"s + s + "2"s + s + "5"s + s + "1\n"
                    "3"s + s + "Fry"s + s + "1"s + s + "6\n"
                    "2"s + s + "Kat"s + s + "2"s + s + "3"s + s + "4\n"
                    "5"s + s + "Tat"s + s + "1"s + s + "6\n"
                    "6"s + s + "Pash"s + s + "0\n"
                    "7"s + s + "Pesh"s + s + "1"s + s + "7\n"
                 };

   OIDManager::reset();
   istringstream input { content };
   input >> p1 >> p2 >> p3 >> p4 >> p5 >> p6 >> p7;
   OIDManager::updateAssociations();

   p1.print();
   p2.print();
   p3.print();
   p4.print();
   p5.print();
   p6.print();
   p7.print();

   ostringstream output;
   OIDManager::reset();
   output << p1 << p2 << p3 << p4 << p5 << p6 << p7 << std::flush;

   REQUIRE(output.str() == content);
}

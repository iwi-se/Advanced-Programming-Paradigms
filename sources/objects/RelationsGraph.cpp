// RelationsGraph.cpp by Ulrich Eisenecker, February 12, 2025

#include "oid_manager.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;
using namespace oid_manager;

class RelationsGraph final
{
   public:
      RelationsGraph(ostream& os):m_os { os }
      {
         m_os << "digraph relations\n"
              << "{\n"
              << "   rankdir = LR\n";
      }
      ~RelationsGraph()
      {
         m_os << "}" << flush;
      }
      operator ostream& ()
      {
         return m_os;
      }
   private:
      ostream& m_os;
};

class Person: public Object
{
   public:
      Person(const string& name): m_name { name }
      {}
      void introduce(const Person& p)
      {
         m_acquaintances.insert(&p);
      }
      void print() const
      {
         cout << "I\'m " << m_name;
         if (m_acquaintances.size() > 0)
         {
            cout << " and I know ";
         }
         for (size_t i { 1 };const auto& a : m_acquaintances)
         {
            cout << a->m_name;
            if (i < m_acquaintances.size() - 1)
            {
               cout << ", ";
            }
            if (i == m_acquaintances.size() - 1)
            {
               cout << " and ";
            }
            ++i;
         }
         cout << '.' << endl;
      }
      void serialize(ostream& os) const
      {
         auto id { OIDManager::getId(*this) };
         os << id << '\t'
            << m_name << '\t'
            << m_acquaintances.size();
         for (const auto& a : m_acquaintances)
         {
            os << '\t' << OIDManager::getId(*a);
         }
         os << endl;
      }
      void serialize(RelationsGraph& graph) const
      {
#ifndef __clang__
         ostream& os { graph }; // When not compiling with clang++.
#else
         ostream& os = graph;  // When compiling with clang++.
#endif
         auto id { OIDManager::getId(*this) };
         os << "   " << id
            << " [ label = \"" << m_name << "\" ]\n   "
            << id << " -> {";
         for (const auto& a : m_acquaintances)
         {
            os << ' ' << OIDManager::getId(*a);
         }
         os << " }\n";
      }
   private:
      string m_name;
      set<const Person*> m_acquaintances;
};

ostream& operator<<(ostream& os,const Person& p)
{
   p.serialize(os);
   return os;
}

RelationsGraph& operator<<(RelationsGraph& os,const Person& p)
{
   p.serialize(os);
   return os;
}

int main()
{
   {
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

         {
            ofstream persons { "persons.csv" };
            persons << p1 << p2 << p3 << p4 << p5 << p6 << p7 << flush;
         }
         {
            ofstream graph { "persons.viz" };
            RelationsGraph persons { graph };
            persons << p1 << p2 << p3 << p4 << p5 << p6 << p7;
         }
   }
}

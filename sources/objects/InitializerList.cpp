// InitializerList.cpp by Ulrich Eisenecker, February 15, 2023

#include <iostream>
#include <initializer_list>
#include <string>
#include <vector>

using namespace std;

class Person
{
   public:
      Person(string surname,initializer_list<string> firstnames = { })
         : m_surname { surname },
           m_firstnames { firstnames }
      {}
      string fullname() const
      {
         string result { };
         for (const auto& name : m_firstnames)
         {
            result += name;
            if (m_firstnames.size() > 0)
            {
               result += ' ';
            }
         }
         result += m_surname;
         return result;
      }
   private:
     string m_surname;
     vector<string> m_firstnames;
};

int main()
{
   Person somePerson { "Johnson",{ "Jaden","Asa","Evan" } };
   cout << somePerson.fullname() << endl;
   Person anotherPerson { "Miller"};
   cout << anotherPerson.fullname() << endl;
}

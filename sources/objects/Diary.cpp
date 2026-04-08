// Diary.cpp by Ulrich Eisenecker, March 1, 2023

// Caution: To successfully compile this program,
// the lines "Person kane { josh };" and
// "josh = josh;" must be turned into comments.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Person
{
   public:
      Person(const string& name)
         : m_diary { name + "s_diary.txt" },
           m_name { name }
      {
         m_diary << name 
                 << " was created." 
                 << endl;
      }
      const string& name() const
      {
         m_diary << m_name
                 << " was asked for the name."
                 << endl;
         return m_name;
      }
      void name(const string& newName)
      {
         m_diary << m_name
                 << " changed the name to "
                 << newName
                 << '.'
                 << endl;
         m_name = newName;
      }
      virtual ~Person()
      {
         m_diary << m_name 
                 << " passed away."
                 << endl;
      }
   private:
      mutable ofstream m_diary;
      string m_name;
};

int main()
{
   Person josh { "Josh" };
   cout << josh.name() << endl;
   josh.name("Jaden");
   cout << josh.name() << endl;
   Person kane { josh };
   josh = josh;
}

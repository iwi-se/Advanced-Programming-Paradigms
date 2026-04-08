// IncompleteObject.cpp by Ulrich Eisenecker, August 23, 2023

#include <iostream>
#include <stdexcept>
#include <string>
#include <source_location>
using namespace std;

class Object
{
   public:
      Object(string name = "anonymous"s,
             unsigned long line = source_location::current().line(),
             unsigned long column = source_location::current().column()):
                m_name { name }
      {
         cout << m_name << " created in line " << line
              << " column " << column << '.' << endl;
      }
      virtual ~Object()
      {
         cout << m_name << " deleted." << endl;
      }
   private:
      string m_name;
};

class IncompleteObject: public Object
{
   public:
      IncompleteObject(): m_pointer { nullptr }
      {
         m_pointer = new Object { "DynamicObject"s };
         throw exception { };
         cout << "We will not see this." << endl;
      }
      IncompleteObject(const IncompleteObject& ) = delete;
      IncompleteObject& operator=(const IncompleteObject& ) = delete;
      ~IncompleteObject() override
      {
         delete m_pointer;
      }
   private:
      Object *m_pointer;
};

int main()
{
   try
   {
      IncompleteObject io;
   }
   catch (...)
   {
      cout << "Unspecified exception caught" << endl;
   }
}

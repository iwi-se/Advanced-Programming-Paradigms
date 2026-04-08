// StackUnwinding.cpp by Ulrich Eisenecker, August 22, 2023

#include <iostream>
#include <stdexcept>
#include <string>
#include <source_location>
using namespace std;

class Logger final
{
   public:
      Logger(string fu = source_location::current().function_name(),
             string fi = source_location::current().file_name()):
                m_functionname { fu },
                m_filename { fi }
      {
         cout << "Entering " << m_functionname
              << " (" << m_filename << ")."
              << endl;
      }
      ~Logger()
      {
         cout << "Leaving " << m_functionname
              << " (" << m_filename <<  ")."
              << endl;
      }
   private:
      string m_functionname,
             m_filename;
};

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

void top()
{
   Logger l;
   Object A { "A"s };
   throw exception { };
   Object B { "B"s };
}

void middle()
{
   Logger l;
   Object C { "C"s };
   top();
   Object D { "D"s };
}

int main()
{
   Logger l;
   try
   {
      Object E { "E"s };
      middle();
      Object F { "F"s };
   }
   catch (...)
   {
      cout << "Unspecified exception caught" << endl;
   }
}

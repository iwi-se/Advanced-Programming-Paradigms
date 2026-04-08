// Order.cpp by Ulrich Eisenecker, February 17, 2023

#include <iostream>
#include <string>
using namespace std;

class Class {

   public:
      Class(const string& description):m_description { description }
      {
         cout << "Class::Class(" << m_description << ')' << endl;
      }
      virtual ~Class()
      {
         cout << "Class::~Class() " << m_description << endl;
      }
   private:
      string m_description;
};

class Derived: public Class
{
   public:
      Derived(const string& description): Class { description }
      {
         cout << "Derived::Derived()" << endl;
      }
      ~Derived()
      {
         cout << "Derived::~Derived()" << endl;
      }
   private:
     Class m_1 { "This is Derived::m_1" },
           m_2 { "This is Derived::m_2" };
};

int main()
{
   Derived d("This is d");
}

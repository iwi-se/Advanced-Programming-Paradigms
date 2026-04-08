// BreakingTheCircle.cpp by Ulrich Eisenecker, May 31, 2025

#include <string>
#include <iostream>
#include <memory>
using namespace std;

class Object final
{
   public:
      explicit Object(const string& name): m_name { name }
      {
         cout << m_name << " created." << endl;
      }
      Object(const Object&) = delete;
      Object& operator=(const Object&) = delete;
      ~Object()
      {
         cout << m_name << " deleted." << endl;
      }
      void connect(shared_ptr<Object>& p)
      {
         m_object = weak_ptr<Object> { p };
      }
      void disconnect()
      {
         m_object.reset();
      }
   private:
      string m_name;
      weak_ptr<Object> m_object;
};

int main()
{
   {
      cout << "Shared pointers are released." << endl;
      auto o1 { make_shared<Object>("Jaden"s) };
      auto o2 { make_shared<Object>("Josh"s) };
      o1->connect(o2);
      o1.reset();
      o2.reset();
   }

   {
      cout << "\nShared pointers are released." << endl;
      auto o1 { make_shared<Object>("Kyle"s) };
      auto o2 { make_shared<Object>("Rowan"s) };
      auto o3 { make_shared<Object>("Jordan"s) };
      o1->connect(o2);
      o2->connect(o3);
      o1.reset();
      o2.reset();
   }

   {
      cout << "\nShared pointers with circular references are also released."
           << endl;
      auto o1 { make_shared<Object>("Quinn"s) };
      auto o2 { make_shared<Object>("Logan"s) };
      o1->connect(o2);
      o2->connect(o1);
      o1.reset();
      o2.reset();
   }

   {
      cout << "\nShared pointers with circular references are also released." 
           << endl;
      auto o1 { make_shared<Object>("River"s) };
      auto o2 { make_shared<Object>("Riley"s) };
      auto o3 { make_shared<Object>("Avery"s) };
      o1->connect(o2);
      o2->connect(o3);
      o3->connect(o1);
      o1.reset();
      o2.reset();
      o3.reset();
   }
}

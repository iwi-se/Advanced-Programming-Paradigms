// TransferOwnership.cpp by Ulrich Eisenecker, June 3, 2026

#include <iostream>
#include <memory>
#include <utility>
using namespace std;

class Object
{
   public:
      Object()
      {
         cout << "Object " << ++m_id << " created" << endl;
      }
      ~Object()
      {
         cout << "Object " << m_id << " deleted" << endl;
      }
   private:
      inline static size_t m_id { 0 };
};

void transferOwnership(unique_ptr<Object>&& o)
{
   unique_ptr<Object> local { std::move(o) }; // <-- Some compilers
   // issue a warning if a call to move() is not fully qualified.
}

int main()
{
   transferOwnership(unique_ptr<Object> { new Object });
   unique_ptr<Object> o { new Object };
   cout << boolalpha << (o.get() == nullptr) << endl;
   transferOwnership(std::move(o)); // <--Some compilers
   // issue a warning if a call to move() is not fully qualified.
   cout << boolalpha << (o.get() == nullptr) << endl;
}

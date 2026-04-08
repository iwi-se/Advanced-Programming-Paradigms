// Delete.cpp by Ulrich Eisenecker, January 17, 2024

#include <string>

using namespace std;

class Person
{
   public:
      Person(string name):m_name(name)
      {}
      Person() = default;
      Person(const Person&) = delete;
      Person& operator=(const Person&) = delete;
      void* operator new(std::size_t) = delete;
      void* operator new[](std::size_t) = delete;
      void operator delete(void*,std::size_t) = delete;
      void operator delete[](void*,std::size_t) = delete;
      Person* operator&() const = delete;
   private:
      string m_name;
};

int main()
{
   Person p1 { "Jude" };
   Person persons[2]; // Possible
   // Person p2 { p1 }; // Not possible
   Person p3 { "Jaden" };
   // p1 = p3; // Not possible
   // Person* p4 = { new Person { "Jill" } }; // Not possible
   // Person* p5 { new Person[2] }; // Not possible 
   // delete p4; // Not possible
   // delete[] p5; // Not possible
   Person* p6 { nullptr };
   // delete p6;
   // delete[] p6;
   // Person* p7 { &p1 }; // Not possible
}

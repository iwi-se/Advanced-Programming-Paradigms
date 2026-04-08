// Default.cpp by Ulrich Eisenecker, February 24, 2023

#include <string>

using namespace std;

class Person
{
   public:
      Person(string name):m_name(name)
      {}
      Person() = default;
   private:
      string m_name;
};

int main()
{
   Person p1 { "Jude" };
   Person p2;
}

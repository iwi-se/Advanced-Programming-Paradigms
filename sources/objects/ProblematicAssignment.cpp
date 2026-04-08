// ProblematicAssignment.cpp by Ulrich Eisenecker, March 24, 2023

#include <iostream>
#include <string>
using namespace std;

class A 
{
   public:
      A(string a = "A::a"): m_a { a }
      {}
      virtual void print() const
      {
         cout << m_a << endl;
      }
      virtual ~A() = default;
   private:
      string m_a;
};

class B: public A 
{
   public:
      B(string a = "B::a",string b = "B::b"): A { a }, m_b { b }
      {}
      void print() const override
      {
         A::print();
         cout << m_b << endl;
      }
   private:
      string m_b;
};

int main()
{
   cout << "Assignment with static == dynamic type\n"
           "a" << endl;
   A a;
   a.print();
   cout << "b" << endl;
   B b;
   b.print();
   cout << "a = b" << endl;
   a = b;
   a.print();
   
   cout << "\nAssignment with static != dynamic type"
        << endl;
   B b1 { "b1::a","b1::b" };;
   B b2 { "b2::a","b2::b" };
   A& b1asa { b1 };
   A& b2asa { b2 };
   b1asa.print();
   b2asa.print();
   cout << "b1asa = b2asa" << endl;
   cout << "b1asa" << endl;
   b1asa = b2asa;
   b1asa.print();
}

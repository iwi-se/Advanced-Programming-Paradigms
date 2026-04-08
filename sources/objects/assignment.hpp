// assignment.hpp by Ulrich Eisenecker, May 17, 2023

#ifndef ASSIGNMENT_HPP
#define ASSIGNMENT_HPP

#include <iostream>
#include <string>

namespace assignment
{
   class A 
   {
      public:
         A(std::string a = "A::a"): m_a { a }
         {}
         virtual void print() const
         {
            std::cout << m_a << std::endl;
         }
         virtual void assign(const A& a)
         {
            if (this != &a)
            {
               m_a = a.m_a;
            }
         }
         A& operator=(const A& a)
         {
            assign(a);
            return *this;
         }
         virtual ~A() = default;
   #ifndef COMPILE_FOR_TESTING
         private:
   #endif // COMPILE_FOR_TESTING
         std::string m_a;
   };

   class B: public A 
   {
      public:
         B(std::string a = "B::a",std::string b = "B::b"): A { a }, m_b { b }
         {}
         void print() const override
         {
            A::print();
            std::cout << m_b << std::endl;
         }
         void assign(const A& a) override
         {
            if (this != &a)
            {
               const B& b { dynamic_cast<const B&>(a) };
               A::assign(b);
               m_b = b.m_b;
            }
         }
         B& operator=(const B& b)
         {
            assign(b);
            return *this;
         }
   #ifndef COMPILE_FOR_TESTING
      private:
   #endif // COMPILE_FOR_TESTING
         std::string m_b;
   };
}

#endif // ASSIGNMENT_HPP

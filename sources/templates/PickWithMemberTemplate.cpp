// PickWithMemberTemplate.cpp by Ulrich Eisenecker, June 17, 2026

#include <iostream>
#include <string>

using namespace std;

template <typename T,class Criterion>
class Pick
{
   public:
      Pick(const T& t1,const T& t2):m_t { Criterion::select(t1,t2) }
      {}
      T& value()
      {
         return m_t;
      }
   private:
      T m_t;
};

class Larger
{
   public:
      template <class T>
      static const T& select(const T& t1,const T& t2)
      {
         if (t1 > t2)
         {
            return t1;
         }
         return t2;
      }
};

class Smaller
{
   public:
      template <class T>
      static const T& select(const T& t1,const T& t2)
      {
         if (t1 < t2)
         {
            return t1;
         }
         return t2;
      }
};

int main()
{
   Pick<int,Larger> p1 { 1, 2 };
   Pick<double,Smaller> p2 { 1.5, 1.4 };
   Pick<string,Larger> p3 { "Hi", "there" };
   cout << p1.value() << endl;
   cout << p2.value() << endl;
   cout << p3.value() << endl;
}

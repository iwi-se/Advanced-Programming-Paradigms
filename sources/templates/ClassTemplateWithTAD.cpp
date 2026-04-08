// ClassTemplateWithTAD.cpp by Ulrich Eisenecker, February 27, 2025

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class RingBuffer
{
   public:
      RingBuffer()
      {}
      RingBuffer(T t)
      {
         put(t);
      }
      RingBuffer(T t1,T t2)
      {
         put(t1);
         put(t2);
      }
      RingBuffer(T t1,T t2,T t3)
      {
         put(t1);
         put(t2);
         put(t3);
      }
      void put(T element)
      {
         if (m_noOfElements < 5)
         { 
            ++m_noOfElements;
         }
         m_elements[m_writeIndex++] = element;
         m_writeIndex %= 5;
      }
      T get()
      {
         if (m_noOfElements == 0)
         {
            throw out_of_range { "RingBuffer<>::get() - empty buffer" };
         }
         int readIndex { (5 - m_noOfElements + m_writeIndex) % 5 };
         --m_noOfElements;
         return m_elements[readIndex];
      }
   private:
      int m_writeIndex { 0 },
          m_noOfElements { 0 };
      T m_elements[5];
};

int main()
{
   RingBuffer rb1 { 'X' };
   RingBuffer rb2 { 5.0, 1.5 };
   RingBuffer rb3 { "Ring"s, "Buffer"s, "std::string"s };
   cout << rb1.get() << endl;
   cout << rb2.get() << endl;
   cout << rb3.get() << endl;
}

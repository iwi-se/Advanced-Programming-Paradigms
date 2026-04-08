// BufferTemplateT.cpp by Ulrich Eisenecker, February 27, 2025

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class RingBuffer
{
   public:
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
   RingBuffer<char> rb;
   rb.put('A');
   rb.put('B');
   rb.put('C');
   rb.put('D');
   rb.put('E');
   rb.put('F');
   cout << rb.get() << endl;
   cout << rb.get() << endl;
   cout << rb.get() << endl;
   cout << rb.get() << endl;
   cout << rb.get() << endl;
   // The next statement throws an exception.
   cout << rb.get() << endl;
}

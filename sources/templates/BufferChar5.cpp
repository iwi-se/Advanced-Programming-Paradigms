// BufferChar5.cpp by Ulrich Eisenecker, November 7, 2023

#include <iostream>
#include <stdexcept>
using namespace std;

class RingBuffer
{
   public:
      void put(char element)
      {
         cout << "P" << m_writeIndex << " N" << m_noOfElements << endl;
         if (m_noOfElements < 5)
         { 
            ++m_noOfElements;
         }
         m_elements[m_writeIndex++] = element;
         m_writeIndex %= 5;
      }
      char get()
      {
         if (m_noOfElements == 0)
         {
            throw out_of_range { "RingBuffer::get() - empty buffer" };
         }
         int readIndex { (5 - m_noOfElements + m_writeIndex) % 5 };
         --m_noOfElements;
         return m_elements[readIndex];
      }
   private:
      int m_writeIndex { 0 },
          m_noOfElements { 0 };
      char m_elements[5];
};

int main()
{
   RingBuffer rb;
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

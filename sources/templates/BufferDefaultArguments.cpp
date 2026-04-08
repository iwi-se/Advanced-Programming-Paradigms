// BufferDefaultArguments.cpp by Ulrich Eisenecker, February 27, 2025

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T = char,int CAPACITY = 5>
class RingBuffer
{
   public:
      void put(T element)
      {
         if (m_noOfElements < CAPACITY)
         {
            ++m_noOfElements;
         }
         m_elements[m_writeIndex++] = element;
         m_writeIndex %= CAPACITY;
      }
      T get()
      {
         if (m_noOfElements == 0)
         {
            throw out_of_range { "RingBuffer<>::get() - empty buffer" };
         }
         int readIndex { (CAPACITY - m_noOfElements 
                          + m_writeIndex) % CAPACITY };
         --m_noOfElements;
         return m_elements[readIndex];
      }
   private:
      int m_writeIndex { 0 },
          m_noOfElements { 0 };
      T m_elements[CAPACITY];
};

int main()
{
   RingBuffer<char,5> rb1;
   RingBuffer<char> rb2;
   RingBuffer<> rb3;
   RingBuffer rb4;
}

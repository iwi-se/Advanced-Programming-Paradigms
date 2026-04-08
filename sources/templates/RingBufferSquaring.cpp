// RingBufferSquaring.cpp by Ulrich Eisenecker, February 27, 2025

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T,int CAPACITY>
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
      void squareElements()
      {
         for (auto& e : m_elements)
         {
            e *= e;
         }
      }
   private:
      int m_writeIndex { 0 },
          m_noOfElements { 0 };
      T m_elements[CAPACITY];
};

int main()
{
   RingBuffer<char,5> rb1;
   rb1.squareElements();
   RingBuffer<string,5> rb2;
   rb2.put("How");
   rb2.put("are");
   rb2.put("you?");
   cout << rb2.get() << endl;
   cout << rb2.get() << endl;
   cout << rb2.get() << endl;
   rb2.squareElements(); // This line does not compile!
}


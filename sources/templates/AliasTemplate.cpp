// AliasTemplate.cpp by Ulrich Eisenecker, March 4, 2025

#include <iostream>
#include <type_traits>
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
         // The function must not be called if m_noOfElements == 0!
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

template <typename TYPE,int SIZE>
using CircularBuffer = RingBuffer<TYPE,SIZE>;

int main()
{
   using CB = CircularBuffer<char,5>;
   using RB = RingBuffer<char,5>;
   static_assert(is_same<CB,RB>::value,"That should not happen!");
}

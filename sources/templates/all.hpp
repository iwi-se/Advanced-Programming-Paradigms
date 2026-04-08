// all.hpp by Ulrich Eisenecker, March 2, 2025

/* This header file contains a function template and
   a class template.
   The function template and the member functions of the
   of the class template are declared only and defined
   separately after their declaration.
*/

#ifndef ALL_HPP
#define ALL_HPP

template <typename T>
void swapVariables(T& a,T& b)
{
   T temp { a };
   a = b;
   b = temp;
}

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

#endif // ALL_HPP

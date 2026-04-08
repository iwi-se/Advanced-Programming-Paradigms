// definitions.t by Ulrich Eisenecker, March 2, 2025

/* This header file is included from header.cpp.
   It contains all definitions of the function template
   and the member functions of the class template.
*/

template <typename T>
void swapVariables(T& a,T& b)
{
   T temp { a };
   a = b;
   b = temp;
}

template <typename T,int CAPACITY>
void RingBuffer<T,CAPACITY>::put(T element)
{
   if (m_noOfElements < CAPACITY)
   { 
      ++m_noOfElements;
   }
   m_elements[m_writeIndex++] = element;
   m_writeIndex %= CAPACITY;
}

template <typename T,int CAPACITY>
T RingBuffer<T,CAPACITY>::get()
{
   // The function must not be called if m_noOfElements == 0!
   int readIndex { (CAPACITY - m_noOfElements 
                    + m_writeIndex) % CAPACITY };
   --m_noOfElements;
   return m_elements[readIndex];
}

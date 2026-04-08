// separated.hpp by Ulrich Eisenecker, March 2, 2025

/* This header files contains a function template and
   a class template.
   The function template as well as the member functions
   of the class template are declared only and defined
   separately after their declaration.
*/

#ifndef SEPARATED_HPP
#define SEPARATED_HPP

// Declaration only

template <typename T>
void swapVariables(T& a,T& b);

// Definition of class template only
// without definitions of member functions

template <typename T,int CAPACITY>
class RingBuffer
{
   public:
      void put(T element);
      T get();
   private:
      int m_writeIndex { 0 },
          m_noOfElements { 0 };
      T m_elements[CAPACITY];
};

// Definition

template <typename T>
void swapVariables(T& a,T& b)
{
   T temp { a };
   a = b;
   b = temp;
}

// Definitions of member functions of class template

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

#endif // SEPARATED_HPP

// header.hpp by Ulrich Eisenecker, March 2, 2025

/* This header file contains a function template and
   a class template.
   The function template and the member functions of the
   of the class template are declared.
   Their definitions are contained in definitions.t
   which is included at the end of the file.
*/

#ifndef HEADER_HPP
#define HEADER_HPP

template <typename T>
void swapVariables(T& a,T& b);

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

#if __has_include("definitions.t")
#include "definitions.t"
#endif // __has_include

#endif // HEADER_HPP

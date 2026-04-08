/*! \file rational_number_operators.hpp
 *
 *  Operators related to rational numbers as free functions.
 *
 *  \author Ulrich Eisenecker
 *  \date June 21, 2021
 */

/*!
 * Include gard for rational_number_operators.hpp
 */
#ifndef RATIONAL_NUMBER_OPERATORS_HPP
#define RATIONAL_NUMBER_OPERATORS_HPP

#include "rational_number.hpp"

/*! Namespace for types and functions related to rational numbers.
 */
namespace rational_number
{
   /*! Adds rational numbers a and b
    *  and returns result as value.
    */    
   [[nodiscard]] RationalNumber operator+(const RationalNumber& a,const RationalNumber& b);
   /*! Subtracts rational number a from b
    *  and returns result as value.
    */ 
   [[nodiscard]] RationalNumber operator-(const RationalNumber& a,const RationalNumber& b);
   /*! Multiplies rational numbers a and b
    *  and returns result as value.
    */ 
   [[nodiscard]] RationalNumber operator*(const RationalNumber& a,const RationalNumber& b);
   /*! Divides rational number b by a
    *  and returns result as value.
    */ 
   [[nodiscard]] RationalNumber operator/(const RationalNumber& a,const RationalNumber& b);

   /*! Stream-insertion operator which outputs RationalNumber to output stream.
    */
   std::ostream& operator<<(std::ostream& os,const RationalNumber& r);
   /*! Stream-extraction operator which inputs RationalNumber from input stream.
    */
   std::istream& operator>>(std::istream& is,RationalNumber& r);
}
#endif // RATIONAL_NUMBER_OPERATORS_HPP

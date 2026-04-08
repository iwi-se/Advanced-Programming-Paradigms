/*! \file rational_number.hpp
 *
 *  Types and functions related to rational numbers.
 *
 *  \author Ulrich Eisenecker
 *  \date June 25, 2021
 */

/*!
 * Include gard for rational_number.hpp
 */
#ifndef RATIONAL_NUMBER_HPP
#define RATIONAL_NUMBER_HPP

#include <cstdint> // Because of intmax_t

/*! Namespace for types and functions related to rational numbers.
 */
namespace rational_number
{
   /*! Represents rational number as class.
    */
   class RationalNumber
   {
      public:
         /*! Constructs a normalized RationalNumber exemplar 
          *  with n for m_numerator and d for d_denominator;
          *  default value for n is 0, 
          *  default value for d is 1.
          */
         RationalNumber(const std::intmax_t& n = 0, const std::intmax_t& d = 1);
         /*! Returns m_numerator as reference to const.
          */
         [[nodiscard]] const std::intmax_t& numerator() const
         {
            return m_numerator;
         }
         /*! Returns m_denominator as reference to const.
          */
         [[nodiscard]] const std::intmax_t& denominator() const
         {
            return m_denominator;
         }
         /*! Adds rational numbers *this and r,
          *  and returns result as value.
          */         
         [[nodiscard]] RationalNumber add(const RationalNumber& r) const;
         /*! Subtracts rational number r from *this,
          *  and returns result as value.
          */
         [[nodiscard]] RationalNumber subtract(const RationalNumber& r) const;
         /*! Multiplies rational numbers *this and r,
          *  and returns result as value.
          */
         [[nodiscard]] RationalNumber multiply(const RationalNumber& r) const;
         /*! Divides rational numbers *this by r,
          *  and returns result as value.      
          */
         [[nodiscard]] RationalNumber divide(const RationalNumber& r) const;
         /*! Serializes rational number to ostream.
          */
         void output(std::ostream& os) const;
         /*! Deserializes rational number from istream.
             No error checking is performed!
          */
         void input(std::istream& is);
         /*! Returns long double value approximating
             the decimal value of the RationalNumber
             *this. 
          */ 
         [[nodiscard]] long double toLongDouble() const;
         /*! Interactively inputs rational number from cin
          *  and returns it as value.
          */
         [[nodiscard]] static RationalNumber input();
      private:
         /*! Normalizes rational number, 
          *   i.e., canonical form and m_denominator > 0.
          */
         void normalize();
         /*! Holds numerator of rational number.
          *  By default, numerator is initialized to 0.
          */
         std::intmax_t  m_numerator { 0 },
         /*! Holds denominator of rational number.
          *  By default, denominator is initialized to 1.
          */
                        m_denominator { 1 };
   };
}
#endif // RATIONAL_NUMBER_HPP

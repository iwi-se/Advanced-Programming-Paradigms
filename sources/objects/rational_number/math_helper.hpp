/*! \file math_helper.hpp
 *
 *  Basic math helper functions.
 *
 *  \author Ulrich Eisenecker
 *  \date February 8, 2022
 */

/*!
 * Include gard for math_helper.hpp
 */
#ifndef MATH_HELPER_HPP
#define MATH_HELPER_HPP

#include <cstdint> // Because of intmax_t

/*! Namespace for math helper functions.
 */
namespace math_helper
{
   /*! Returns -1 if n < 0, 0 if n == 0, +1 if n > 0.
    *  Return value must not be discarded.
    */
   [[nodiscard]] std::intmax_t sign(const std::intmax_t& n);
}
#endif // MATH_HELPER_HPP

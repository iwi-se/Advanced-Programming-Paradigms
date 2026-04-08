#include <cmath>

#include "math_helper.hpp"

namespace math_helper
{
   using namespace std;

   intmax_t sign(const intmax_t& n)
   {
      if (n < 0)
      {
         return -1;
      }
      if (n > 0)
      {
         return +1;
      }
      return 0;
   }
}

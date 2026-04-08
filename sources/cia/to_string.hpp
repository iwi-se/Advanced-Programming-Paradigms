// to_string.hpp by Ulrich Eisenecker, June 2, 2025

#ifndef TO_STRING_HPP
#define TO_STRING_HPP

#include <numeric>  // Because of accumulate<>().
#include <string>

namespace cia
{
   std::string to_string(const std::ranges::forward_range auto& c)
   {
      return std::accumulate(begin(c),end(c),std::string { },
                              [](auto result,auto element)
                               { return result + element; });
   }
} // cia
#endif // TO_STRING_HPP

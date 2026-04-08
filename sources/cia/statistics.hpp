// statistics.hpp by Ulrich Eisenecker, August 27, 2025
#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <algorithm>   // Because of min_element<>() and max_element<>().
#include <cmath>       // Because of sqrt().
#include <iostream>
#include <numeric>     // Because of accuulate<>().
#include <ostream>     // Because of ostream.
#include <ranges>      // Because of generate<>() and forward_range<>().
#include <random>      // Because of mt19937_64 and normal_distribution.
#include <set>         // Because of set<>.
#include <tuple>       // Because of make_tuple<>(), tuple<> and apply<>().
#include <utility>     // Because of pair<> and make_pair<>().
#include <vector>

namespace statistics
{
   template <typename ELEMENTTYPE = double,
             template <class T,class Allocator = std::allocator<T>>
             class CONTAINER = std::vector,
             class DISTRIBUTION,
             class GENERATOR
            >
   [[nodiscard]] auto generateRandomData(DISTRIBUTION&& distribution,
                                         GENERATOR&& generator,
                                         std::size_t n)
   {
      CONTAINER<ELEMENTTYPE> result(n);
      std::ranges::generate(result,[&] () { return distribution(generator); });
      return result;
   }

   auto modes(std::ranges::forward_range auto&& data)
   /* This function assumes that the elements of
    * data are sorted in ascending order. This is
    * not checked by the function itself!
    */
   {
      auto n { size(data) };
      auto recentValue { data[0] };
      std::size_t frequency { },
                  modeFrequency { };
      std::set<decltype(recentValue)> modeValues;
      for (std::size_t counter { };auto& v : data)
      {
         ++counter;
         if (v == recentValue)
         {
            ++frequency;
            if (frequency > modeFrequency)
            {
               modeFrequency = frequency;
               modeValues.clear();
               modeValues.insert(recentValue);
            }
            else if (frequency == modeFrequency)
                 {
                    if (modeValues.contains(recentValue) == false)
                    {
                       modeValues.insert(recentValue);
                    }
                 }
         }
         else if (counter < n)
              {
                 recentValue = v;
                 frequency = 1;
              }
      }
      return std::make_pair(modeFrequency,modeValues);
   }

   template <typename PRECISION = double>
   [[nodiscard]] auto calculateParameters(std::ranges::forward_range auto&& data)
   {
      auto n { size(data) };
      PRECISION sum { std::accumulate(data.begin(),data.end(),PRECISION { 0.0 },
                      [](auto sum,auto val){ return sum + val;}) };
      PRECISION mean { sum / n };
      PRECISION stdDev
         { std::sqrt(std::accumulate(data.begin(),data.end(),PRECISION { 0.0 },
           [=](auto sum,auto val)
              { return sum + (val - mean) * (val - mean);} ) / n)
         };
      std::ranges::sort(data);
      auto median { n % 2 ? data[n / 2] :
                      (data[n / 2 - 1] + data[n / 2]) /
                      PRECISION { 2.0 } };
      auto [modeFrequency,modeValues] = modes(data);
      using namespace std::string_literals;
      return std::make_tuple(std::make_pair("n"s,n),
                             std::make_pair("mean value"s,mean),
                             std::make_pair("standard deviation"s,stdDev),
                             std::make_pair("median"s,median),
                             std::make_pair("mode frequency"s,modeFrequency),
                             std::make_pair("mode value(s)"s,modeValues),
                             std::make_pair("minimal value"s,*(data.begin())),
                             std::make_pair("maximal value"s,*(data.rbegin())));
   }

   void outputData(std::ostream& os,std::ranges::forward_range auto&& data)
   {
      constexpr std::size_t valuesPerLine { 8 };
      std::size_t n { 0 };
      for (auto value : data)
      {
         os << value;
         if ( ++n < valuesPerLine)
         {
            os << '\t';
         }
         else
         {
            os << std::endl;
            n = 0;
         }
      }
      os << std::endl;
   }

   namespace internal // Indicates, that the following definitions should not
   {                  // be accessed from the outside, i.e. client code.
      template <class T1,class T2>
      std::ostream& output(std::ostream& os,const std::pair<T1,T2>& p)
      {
         os << p.first << '\t' << p.second;
         return os;
      };

      template <class T1,class T2>
      std::ostream& output(std::ostream& os,const std::pair<T1,std::set<T2>>& p)
      {
         os << p.first;
         for (auto e : p.second)
         {
            os << '\t' << e;
         }
         return os;
      };
   }

   template <typename ...Pair>
   void outputParameters(std::ostream& os,const std::tuple<Pair...>& params)
   {
      std::apply([&os](const Pair& ...param)
                 { ((internal::output(os,param) << std::endl), ...); },params);
   }
} // end namespace statistics
#endif // STATISTICS_HPP

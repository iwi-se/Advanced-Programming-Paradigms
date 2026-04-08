// extended_statistics.hpp by Ulrich Eisenecker, July 22, 2025
//
#ifndef EXTENDED_STATISTICS_HPP
#define EXTENDED_STATISTICS_HPP

#include <algorithm>
#include <map>

#include "statistics.hpp"

namespace statistics
{
   template <typename T = double,
             class DISTRIBUTION,
             class GENERATOR
            >
   [[nodiscard]] auto generateRndDtaAsMap(DISTRIBUTION&& distribution,
                                          GENERATOR&& generator,
                                          std::size_t n)
   {
      std::map<T,std::size_t> result;
      while (n)
      {
         result[distribution(generator)] += 1;
         --n;
      };
      return result;
   }

   template <typename T = double>
   auto modes(std::map<T,std::size_t>& data)
   {
      std::size_t frequency { },
                  modeFrequency { };
      std::set<T> modeValues;
      for (auto& p : data)
      {
         if (p.second > modeFrequency)
         {
            modeFrequency = p.second;
            if (!modeValues.contains(p.first))
            {
               modeValues.clear();
               modeValues.insert(p.first);
            }
         }
         else if (p.second == modeFrequency)
         {
            modeValues.insert(p.first);
         }
      }
      return std::make_pair(modeFrequency,modeValues);
   }

   template <typename PRECISION,typename T = double>
   PRECISION median(std::map<T,std::size_t>& data,std::size_t n)
   {
      std::pair<T,std::size_t> belowHalf { },
                               aboveOrEqualHalf { };
      auto nHalf { n / PRECISION { 2.0 } };
      for (auto& p : data)
      {
         if (belowHalf.second + p.second <= nHalf)
         {
            belowHalf.first = p.first;
            belowHalf.second += p.second;
         };
         aboveOrEqualHalf.first = p.first;
         aboveOrEqualHalf.second += p.second;
         if (aboveOrEqualHalf.second > nHalf)
         {
            break; // Exit range-based for loop.
         }
      }
      PRECISION median { };
      if (nHalf + 1 == aboveOrEqualHalf.second)
      {
         median = (belowHalf.first + aboveOrEqualHalf.first) / PRECISION { 2.0 };
      }
      else
      {
         median = aboveOrEqualHalf.first;
      }
      return median;
   }

   template <typename PRECISION = double,typename T = double>
   [[nodiscard]] auto calculateParameters(std::map<T,std::size_t>& data)
   {
      std::size_t n { };
      PRECISION sum { },
                sumOfSquares { };
      std::ranges::for_each(data,[&n,&sum,&sumOfSquares](auto p)
                                 {
                                    n += p.second;
                                    sum += p.first * p.second;
                                    sumOfSquares += p.first * p.first * p.second;
                                 });
      PRECISION mean { PRECISION { sum } / n };
      PRECISION stdDev { std::sqrt(sumOfSquares / static_cast<PRECISION>(n) -
                                   mean * mean) };
      auto medianValue { median<PRECISION>(data,n) };
      auto [modeFrequency,modeValues] = modes(data);
      using namespace std::string_literals;
      return std::make_tuple(std::make_pair("n"s,n),
                             std::make_pair("mean value"s,mean),
                             std::make_pair("standard deviation"s,stdDev),
                             std::make_pair("median"s,medianValue),
                             std::make_pair("mode frequency"s,modeFrequency),
                             std::make_pair("mode value(s)"s,modeValues),
                             std::make_pair("minimal value"s,data.begin()->first),
                             std::make_pair("maximal value"s,data.rbegin()->first));
   }

   template <typename T = double>
   void outputData(std::ostream& os,std::map<T,std::size_t>& data)
   {
      os << "Value\tFrequency" << std::endl;
      for (auto& p : data)
      {
         os << p.first << '\t' << p.second << std::endl;
      }
   }

   template <typename PRECISION = double>
   [[nodiscard]] auto calcParamsFaster(std::ranges::forward_range auto&& data)
   {
      auto n { size(data) };
      PRECISION sum { },
                sumOfSquares { };
      std::ranges::for_each(data,[&sum,&sumOfSquares](auto v)
                                             {
                                                sum += v;
                                                sumOfSquares += v * v;
                                             });
      PRECISION mean { sum / n };
      PRECISION stdDev { std::sqrt(sumOfSquares / n - mean * mean) };
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
}

#endif // EXTENDED_STATISTICS_HPP

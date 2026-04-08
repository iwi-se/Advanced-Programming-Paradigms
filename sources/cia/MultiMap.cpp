// MultiMap.cpp by Ulrich Eisenecker, Agust 27, 2025
// Compiles with clang version 20.1.5 .
// Does not compile with GCC 15.1.0 .

#include <catch2/catch_test_macros.hpp>
#include <algorithm>// Because of is_sorted<>() abd equal<>().
#include <iostream>
#include <iterator> // Because of begin<>(), end<>() and inserter<>().
#include <map>      // Because of multimap<>.
#include <ranges>   // Because of set operations in the ranges library,
                    // forward_range concept and is_sorted<>().
#include <string>   // Because of string.
                    //
#include "to_string.hpp" // Because of cia::to_string<>().

auto allSubstrings(std::string s)
{
   using StringType = decltype(s);
   using SizeType = StringType::size_type;
   std::multimap<StringType,SizeType> result;
   for (SizeType i { }; i < size(s); ++i)
   {
      for (SizeType l { 1 }; l <= size(s) - i; ++l)
      {
         result.insert({ s.substr(i,l),i });
      }
   }
   return result;
}

TEST_CASE("MultiMap")
{
   using namespace std;
   using namespace cia;

   auto abacab { allSubstrings("ABACAB"s) };
   auto aba { allSubstrings("ABA"s) };
   auto abc { allSubstrings("abc"s) };

   SECTION("to_string, transform, keys & values")
   {
      auto pairs { abc | views::transform([](const auto& p)
                                             { return " "s + p.first +
                                               "->" + to_string(p.second);
                                             }
                                         )
                 };
      REQUIRE(to_string(pairs) == " a->0 ab->0 abc->0 b->1 bc->1 c->2"s);
      REQUIRE(to_string(abc | views::keys) == "aababcbbcc"s);
      auto values { abc | views::values
                        | views::transform([](const auto& v)
                                           { return std::to_string(v);}
                                          )
                  };
      REQUIRE(to_string(values) == "000112"s);
   }
   SECTION("size")
   {
      REQUIRE(size(abacab) == 21);
      REQUIRE(size(aba) == 6);
   }
   SECTION("Internally sorted")
   {
      REQUIRE(ranges::is_sorted(abacab));
      REQUIRE(ranges::is_sorted((aba)));
   }
   SECTION ("Merge, keys & equal")
   {
      auto abacabCopy { abacab },
           abaCopy { aba };
      abacab.merge(aba);
      REQUIRE(size(abacab) == size(abacabCopy) + size(abaCopy));
      REQUIRE(size(aba) == 0);
      abaCopy.merge(abacabCopy);
      REQUIRE(size(abacabCopy) == 0);
      auto v1 { views::keys(abacab) };
      auto v2 { views::keys(abaCopy) };
      REQUIRE(ranges::equal(v1,v2));
   }
}

// Set.cpp by Ulrich Eisenecker, August 28, 2025
// Compiles with clang version 20.1.5 .
// Does not compile with GCC 15.1.0 .

#include <catch2/catch_test_macros.hpp>
#include <algorithm>// Because of set operations.
#include <iterator> // Because of begin<>(), end<>() and inserter<>().
#include <numeric>  // Because of accumulate<>().
#include <ranges>   // Because of set operations in the ranges library
                    // and forward_range concept.
#include <set>      // Because of set<>.
#include <string>   // Because of string.

// The following function template creates a string representation
// for all elements of a set.
std::string to_string(const std::ranges::forward_range auto& c)
{
   // accumulate<>() is not yet available in the ranges library.
   return std::accumulate(begin(c),end(c),std::string { });
}

TEST_CASE("Set")
{
   using namespace std;

   set set1 { "two"s,"one"s,"zero"s,"four"s },
       set2 { "four"s,"six"s,"eight"s,"one"s,"nine"s,"six"s }; // "six" occurs
                                                               // twice!
   set<string> result { }; // Empty set of strings.
   SECTION("size")
   {
      REQUIRE(size(set1) == 4);
      REQUIRE(size(set2) == 5); // Not 6 elements, as "six" occurs twice above.
   }
   SECTION("Internally sorted")
   {
       REQUIRE(to_string(set1) == "fouronetwozero"s);
       REQUIRE(to_string(set2) == "eightfournineonesix"s);
       // Or with the same effect
       REQUIRE(ranges::is_sorted(set1));
       REQUIRE(ranges::is_sorted(set2));
   }
   SECTION("Inserting, erasing & containing")
   {
      REQUIRE(set1.contains("five"s) == false);
      set1.insert("five"s);
      REQUIRE(size(set1) == 5);
      REQUIRE(set1.contains("five"s) == true);
      set1.erase("five"s);
      REQUIRE(set1.size() == 4);
      REQUIRE(set1.contains("five"s) == false);
   }
   SECTION("Union")
   {
      // An inserter is required to insert elements into the
      // result set. The container and an iterator (either begin()
      // or end()) must be passed to the inserter as arguments.
      ranges::set_union(set1,set2,
                        inserter(result,begin(result)));
      REQUIRE(to_string(result) == "eightfournineonesixtwozero"s);
   }
   SECTION("Intersection")
   {
      ranges::set_intersection(set1,set2,
                               inserter(result,begin(result)));
      REQUIRE(to_string(result) == "fourone"s);
   }
   SECTION("Difference")
   {
      ranges::set_difference(set1,set2,
                             inserter(result,begin(result)));
      REQUIRE(to_string(result) == "twozero"s);
   }
   SECTION("Symmetric difference")
   {
      ranges::set_symmetric_difference(set1,set2,
                                       inserter(result,begin(result)));
      REQUIRE(to_string(result) == "eightninesixtwozero"s);
   }
}

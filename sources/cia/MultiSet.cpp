// MultiSet.cpp by Ulrich Eisenecker, June 2, 2025
// Compiles with clang version 20.1.5,
// Does not compile with GCC 15.1.0

#include <catch2/catch_test_macros.hpp>
#include <algorithm>// Because of set operations.
#include <iterator> // Because of begin<>(), end<>() and inserter<>()
#include <ranges>   // Because of set operations in the ranges library
                    // and forward_range concept
#include <set>      // Because of multiset<>
#include <string>   // Because of string
#include "to_string.hpp" // Because of cia::to_string<>()

TEST_CASE("Set")
{
   using namespace std;
   using namespace cia;

   multiset set1 { "two"s,"one"s,"zero"s,"four"s },
            set2 { "four"s,"six"s,"eight"s,"one"s,"nine"s,"six"s };
   multiset<string> result { }; // Empty set of strings.
   SECTION("size")
   {
      REQUIRE(size(set1) == 4);
      REQUIRE(size(set2) == 6); // In a multiset, "six" can occur twice.
   }
   SECTION("Internally sorted")
   {
       REQUIRE(to_string(set1) == "fouronetwozero"s);
       REQUIRE(to_string(set2) == "eightfournineonesixsix"s);
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
      REQUIRE(to_string(result) == "eightfournineonesixsixtwozero"s);
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
      REQUIRE(to_string(result) == "eightninesixsixtwozero"s);
   }
}

// AssignmentUnitTests.cpp by Ulrich Eisenecker, March 18, 2025

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
// This code is based on Catch2 v3,
// therefore only the minimal header
// file for test macros is included.
// The C++ library path must be set
// accordingly for compilation and
// linking, and the Catch2Main and
// Catch2 libraries must be linked
// explicitly in exactly this order!

#define COMPILE_FOR_TESTING

#include "assignment.hpp"
#include <string>
#include <exception>

using namespace std;
using namespace assignment;

TEST_CASE("ASSIGN")
{
   A a1 { "a1::a" };
   A a2 { "a2::a" };
   B b1 { "b1::a","b1::b" };
   B b2 { "b2::a","b2::b" };
   A& b1asa { b1 };
   A& b2asa { b2 };

   SECTION("a1_assign_a2")
   {
      REQUIRE(a1.m_a == "a1::a");
      REQUIRE(a2.m_a == "a2::a");
      a1.assign(a2);
      REQUIRE(a1.m_a == a2.m_a);
   }
   SECTION("b1_assign_b2")
   {
      REQUIRE(b1.m_a == "b1::a");
      REQUIRE(b1.m_b == "b1::b");
      REQUIRE(b2.m_a == "b2::a");
      REQUIRE(b2.m_b == "b2::b");
      b1.assign(b2);
      REQUIRE(b1.m_a == b2.m_a);
      REQUIRE(b1.m_b == b2.m_b);
   }
   SECTION("a1_assign_b1")
   {
      REQUIRE(a1.m_a == "a1::a");
      REQUIRE(b1.m_a == "b1::a");
      REQUIRE(b1.m_b == "b1::b");
      a1.assign(b1);
      REQUIRE(a1.m_a == b1.m_a);
   }
   SECTION("b1asa_assign_b2asa")
   {
      REQUIRE(b1.m_a == "b1::a");
      REQUIRE(b1.m_b == "b1::b");
      REQUIRE(b2.m_a == "b2::a");
      REQUIRE(b2.m_b == "b2::b");
      b1asa.assign(b2asa);
      REQUIRE(b1.m_a == b2.m_a);
      REQUIRE(b1.m_b == b2.m_b);
   }
   SECTION("a1_assign_b1asa")
   {
      REQUIRE(a1.m_a == "a1::a");
      REQUIRE(b1.m_a == "b1::a");
      REQUIRE(b1.m_b == "b1::b");
      a1.assign(b1asa);
      REQUIRE(a1.m_a == b1.m_a);
   }
   SECTION("b1asa_assign_a1")
   {
      REQUIRE(b1.m_a == "b1::a");
      REQUIRE(b1.m_b == "b1::b");
      REQUIRE(a1.m_a == "a1::a");
      REQUIRE_THROWS_AS(b1asa.assign(a1),bad_cast);
   }
}

TEST_CASE("OPERATOR=")
{
   A a1 { "a1::a" };
   A a2 { "a2::a" };
   B b1 { "b1::a","b1::b" };
   B b2 { "b2::a","b2::b" };
   A& b1asa { b1 };
   A& b2asa { b2 };

   SECTION("a1=a2")
   {
      REQUIRE(a1.m_a == "a1::a");
      REQUIRE(a2.m_a == "a2::a");
      a1 = a2;
      REQUIRE(a1.m_a == a2.m_a);
   }
   SECTION("b1=b2")
   {
      REQUIRE(b1.m_a == "b1::a");
      REQUIRE(b1.m_b == "b1::b");
      REQUIRE(b2.m_a == "b2::a");
      REQUIRE(b2.m_b == "b2::b");
      b1 = b2;
      REQUIRE(b1.m_a == b2.m_a);
      REQUIRE(b1.m_b == b2.m_b);
   }
   SECTION("a1=b1")
   {
      REQUIRE(a1.m_a == "a1::a");
      REQUIRE(b1.m_a == "b1::a");
      REQUIRE(b1.m_b == "b1::b");
      a1 = b1;
      REQUIRE(a1.m_a == b1.m_a);
   }
   SECTION("b1asa=b2asa")
   {
      REQUIRE(b1.m_a == "b1::a");
      REQUIRE(b1.m_b == "b1::b");
      REQUIRE(b2.m_a == "b2::a");
      REQUIRE(b2.m_b == "b2::b");
      b1asa = b2asa;
      REQUIRE(b1.m_a == b2.m_a);
      REQUIRE(b1.m_b == b2.m_b);
   }
   SECTION("a1=b1asa")
   {
      REQUIRE(a1.m_a == "a1::a");
      REQUIRE(b1.m_a == "b1::a");
      REQUIRE(b1.m_b == "b1::b");
      a1 = b1asa;
      REQUIRE(a1.m_a == b1.m_a);
   }
   SECTION("b1asa=a1")
   {
      REQUIRE(b1.m_a == "b1::a");
      REQUIRE(b1.m_b == "b1::b");
      REQUIRE(a1.m_a == "a1::a");
      REQUIRE_THROWS_AS(b1asa = a1,bad_cast);
   }
}

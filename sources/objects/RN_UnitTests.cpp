// RN_UnitTests.cpp by Ulrich Eisenecker, March 18, 2025

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

#include <sstream>
#include <string>

#include "RN.hpp"

TEST_CASE("1ST_CONSTRUCTOR")
{
   using namespace std;
   RationalNumber a { 2, 4 };
   ostringstream os;
   a.output(os);
   REQUIRE(os.str() == "(1/2)"s);
}

TEST_CASE("2ND_CONSTRUCTOR")
{
   using namespace std;
   RationalNumber a { "2", "4" };
   ostringstream os;
   a.output(os);
   REQUIRE(os.str() == "(1/2)"s);
}

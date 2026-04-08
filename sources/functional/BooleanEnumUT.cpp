// BooleanEnumUT.cpp by Ulrich Eisenecker, February 23, 2026

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

#include "booleanenum.hpp"

#include <string>
#include <sstream>

using namespace std;

using namespace booleanenum;

TEST_CASE("STATIC")
{
   ostringstream os;

   SECTION("<<")
   {
      SECTION("FALSE")
      {
         os << Boolean::False;
         REQUIRE(os.str() == "False");
      }
      SECTION("TRUE")
      {
         os << Boolean::True;
         REQUIRE(os.str() == "True");
      }
   }
   SECTION("!")
   {
      SECTION("FALSE")
      {
         os << !(Boolean::False);
         REQUIRE(os.str() == "True");
      }
      SECTION("TRUE")
      {
         os << !(Boolean::True);
         REQUIRE(os.str() == "False");
      }
   }
   SECTION("AND")
   {
      SECTION("FALSEFALSE")
      {
         os << (Boolean::False && Boolean::False);
         REQUIRE(os.str() == "False");
      }
      SECTION("FALSETRUE")
      {
         os << (Boolean::False && Boolean::True);
         REQUIRE(os.str() == "False");
      }
      SECTION("TRUEFALSE")
      {
         os << (Boolean::True && Boolean::False);
         REQUIRE(os.str() == "False");
      }
      SECTION("TRUETRUE")
      {
         os << (Boolean::True && Boolean::True);
         REQUIRE(os.str() == "True");
      }
   }
   SECTION("OR")
   {
      SECTION("FALSEFALSE")
      {
         os << (Boolean::False || Boolean::False);
         REQUIRE(os.str() == "False");
      }
      SECTION("FALSETRUE")
      {
         os << (Boolean::False ||Boolean::True);
         REQUIRE(os.str() == "True");
      }
      SECTION("TRUEFALSE")
      {
         os << (Boolean::True || Boolean::False);
         REQUIRE(os.str() == "True");
      }
      SECTION("TRUETRUE")
      {
         os << (Boolean::True ||Boolean::True);
         REQUIRE(os.str() == "True");
      }
   }
}

TEST_CASE("DYNAMIC")
{
   ostringstream os;
   Boolean fls { Boolean::False };
   Boolean tr { Boolean::True };
   Boolean& f { fls };
   Boolean& t { tr };

   SECTION("<<")
   {
      SECTION("FALSE")
      {
         os << f;
         REQUIRE(os.str() == "False");
      }
      SECTION("TRUE")
      {
         os << t;
         REQUIRE(os.str() == "True");
      }
   }
   SECTION("!")
   {
      SECTION("FALSE")
      {
         os << !f;
         REQUIRE(os.str() == "True");
      }
      SECTION("TRUE")
      {
         os << !t;
         REQUIRE(os.str() == "False");
      }
   }
   SECTION("AND")
   {
      SECTION("FALSEFALSE")
      {
         os << (f && f);
         REQUIRE(os.str() == "False");
      }
      SECTION("FALSETRUE")
      {
         os << (f && t);
         REQUIRE(os.str() == "False");
      }
      SECTION("TRUEFALSE")
      {
         os << (t && f);
         REQUIRE(os.str() == "False");
      }
      SECTION("TRUETRUE")
      {
         os << (t && t);
         REQUIRE(os.str() == "True");
      }
   }
   SECTION("OR")
   {
      SECTION("FALSEFALSE")
      {
         os << (f ||f);
         REQUIRE(os.str() == "False");
      }
      SECTION("FALSETRUE")
      {
         os << (f || t);
         REQUIRE(os.str() == "True");
      }
      SECTION("TRUEFALSE")
      {
         os << (t || t);
         REQUIRE(os.str() == "True");
      }
      SECTION("TRUETRUE")
      {
         os << (t || t);
         REQUIRE(os.str() == "True");
      }
   }
}

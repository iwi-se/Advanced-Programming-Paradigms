// BooleanVariantUT.cpp by Ulrich Eisenecker, February 23, 2026

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

#include "booleanvariant.hpp"

#include <string>
#include <sstream>
#include <type_traits>

using namespace std;

using namespace booleanvariant;

TEST_CASE("FALSETRUE")
{
   ostringstream os;

   SECTION("<<")
   {
      SECTION("FALSE")
      {
         os << False { };
         REQUIRE(os.str() == "False");
      }
      SECTION("TRUE")
      {
         os << True { };
         REQUIRE(os.str() == "True");
      }
   }
   SECTION("!")
   {
      SECTION("FALSE")
      {
         os << !(False { });
         REQUIRE(os.str() == "True");
      }
      SECTION("TRUE")
      {
         os << !(True { });
         REQUIRE(os.str() == "False");
      }
   }
   SECTION("==")
   {
      SECTION("FALSEFALSE")
      {
         os << (False { } == False { });
         REQUIRE(os.str() == "True");
      }
      SECTION("FALSETRUE")
      {
         os << (False { } == True { });
         REQUIRE(os.str() == "False");
      }
      SECTION("TRUEFALSE")
      {
         os << (True { } == False { });
         REQUIRE(os.str() == "False");
      }
      SECTION("TRUETRUE")
      {
         os << (True { } == True { });
         REQUIRE(os.str() == "True");
      }
   }
   SECTION("AND")
   {
      SECTION("FALSEFALSE")
      {
         os << (False { } && False { });
         REQUIRE(os.str() == "False");
      }
      SECTION("FALSETRUE")
      {
         os << (False { } && True { });
         REQUIRE(os.str() == "False");
      }
      SECTION("TRUEFALSE")
      {
         os << (True { } && False { });
         REQUIRE(os.str() == "False");
      }
      SECTION("TRUETRUE")
      {
         os << (True { } && True { });
         REQUIRE(os.str() == "True");
      }
   }
   SECTION("OR")
   {
      SECTION("FALSEFALSE")
      {
         os << (False { } || False { });
         REQUIRE(os.str() == "False");
      }
      SECTION("FALSETRUE")
      {
         os << (False { } || True { });
         REQUIRE(os.str() == "True");
      }
      SECTION("TRUEFALSE")
      {
         os << (True { } || False { });
         REQUIRE(os.str() == "True");
      }
      SECTION("TRUETRUE")
      {
         os << (True { } || True { });
         REQUIRE(os.str() == "True");
      }
   }
}

Boolean isOdd(unsigned long long int i)
{
   if (i % 2)
   {
      return True { };
   }
   return False { };
}

TEST_CASE("BOOLEAN")
{
   ostringstream os;
   auto visitor { [&os](auto v) { os << v; } };

   SECTION("FALSE")
   {
      auto result { isOdd(2) };
      REQUIRE(get_if<False>(&result));
      REQUIRE(is_same_v<False,variant_alternative_t<0,decltype(result)>>);
      REQUIRE(result.index() == 0);
      result.visit(visitor);
      REQUIRE(os.str() == "False");
   }
   SECTION("TRUE")
   {
      auto result { isOdd(3) };
      REQUIRE(get_if<True>(&result));
      REQUIRE(is_same_v<True,variant_alternative_t<1,decltype(result)>>);
      REQUIRE(result.index() == 1);
      result.visit(visitor);
      REQUIRE(os.str() == "True");
   }
}

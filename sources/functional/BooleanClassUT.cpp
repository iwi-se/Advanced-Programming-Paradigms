// BooleanClassUT.cpp by Ulrich Eisenecker, February 23, 2026

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

#include "booleanclass.hpp"

#include <string>
#include <sstream>

using namespace std;

using namespace booleanclass;

TEST_CASE("STATIC")
{
   ostringstream os;

   SECTION("OUTPUT")
   {
      SECTION("FALSE")
      {
         False { }.output(os);
         REQUIRE(os.str() == "False");
      }
   }
      SECTION("TRUE")
      {
         True { }.output(os);
         REQUIRE(os.str() == "True");
      }
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

TEST_CASE("DYNAMIC")
{
   ostringstream os;
   False fls;
   True tr;
   Boolean& f { fls };
   Boolean& t { tr };

   SECTION("OUTPUT")
   {
      SECTION("FALSE")
      {
         f.output(os);
         REQUIRE(os.str() == "False");
      }
   }
      SECTION("TRUE")
      {
         t.output(os);
         REQUIRE(os.str() == "True");
      }
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
   SECTION("==")
   {
      SECTION("FALSEFALSE")
      {
         os << (f == f);
         REQUIRE(os.str() == "True");
      }
      SECTION("FALSETRUE")
      {
         os << (f == t);
         REQUIRE(os.str() == "False");
      }
      SECTION("TRUEFALSE")
      {
         os << (t == f);
         REQUIRE(os.str() == "False");
      }
      SECTION("TRUETRUE")
      {
         os << (t == t);
         REQUIRE(os.str() == "True");
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


TEST_CASE("MIXED")
{
   ostringstream os;
   False fls;
   True tr;
   Boolean& f { fls };
   Boolean& t { tr };
   SECTION("==SD")
   {
      os << (False { } == f);
      REQUIRE(os.str() == "True");
   }
   SECTION("==DS")
   {
      os << (f == True { });
      REQUIRE(os.str() == "False");
   }
   SECTION("&&SD")
   {
      os << (False { } && t);
      REQUIRE(os.str() == "False");
   }
   SECTION("&&SD")
   {
      os << (t && True { });
      REQUIRE(os.str() == "True");
   }
   SECTION("||SD")
   {
      os << (True { } || f);
      REQUIRE(os.str() == "True");
   }
   SECTION("||DS")
   {
      os << (f || True { });
      REQUIRE(os.str() == "True");
   }
}

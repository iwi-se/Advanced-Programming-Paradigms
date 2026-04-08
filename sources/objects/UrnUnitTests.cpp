// UrnUnitTests.cpp by Ulrich Eisenecker, March 18, 2025

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

#include "urn.hpp"
#include <iostream>
#include <string>

std::string to_string(const urn::UrnOR& urn)
{
   std::string result;
   for (urn::uint i { 0 }; i < urn.k(); ++i)
   {
      if (i > 0)
      {
         result += " ";
      }
      result += std::to_string(urn[i]);
   }
   return result;
}

TEST_CASE("UrnOR")
{
   using namespace urn;
   SECTION("1")
   {
      UrnOR u { 0,0 };
      REQUIRE(u.n() == 0);
      REQUIRE(u.k() == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("2")
   {
      //UrnOR u { 0,1 };
      std::cout << "[UrnOR][2] is not implemented yet" 
                << std::endl;
   }
   SECTION("3")
   {
      UrnOR u { 1,0 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("4")
   {
      UrnOR u { 1,1 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("5")
   {
      UrnOR u { 2,1 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == true);
      REQUIRE(u.at(0) == 1);
      REQUIRE(u[0] == 1);
      REQUIRE(u.next() == false);
   }
   SECTION("6")
   {
      UrnOR u { 2,2 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 2);
      REQUIRE(to_string(u) == "0 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 1");
      REQUIRE(u.next() == false);
   }
}

TEST_CASE("UrnO")
{
   using namespace urn;
   SECTION("7")
   {
      UrnO u { 0,0 };
      REQUIRE(u.n() == 0);
      REQUIRE(u.k() == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("8")
   {
      //UrnO u { 0,1 };
      std::cout << "[UrnO][8] is not implemented yet" 
                << std::endl;
   }
   SECTION("9")
   {
      UrnO u { 1,0 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("10")
   {
      UrnO u { 1,1 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("11")
   {
      UrnO u { 2,1 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == true);
      REQUIRE(u.at(0) == 1);
      REQUIRE(u[0] == 1);
      REQUIRE(u.next() == false);
   }
   SECTION("12")
   {
      UrnO u { 2,2 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 2);
      REQUIRE(to_string(u) == "0 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 0");
      REQUIRE(u.next() == false);
   }
   SECTION("13")
   {
      UrnO u { 3,3 };
      REQUIRE(u.n() == 3);
      REQUIRE(u.k() == 3);
      REQUIRE(to_string(u) == "0 1 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 2 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 0 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 2 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "2 0 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "2 1 0");
      REQUIRE(u.next() == false);
   }
}

TEST_CASE("UrnR")
{
   using namespace urn;
   SECTION("14")
   {
      //UrnR u { 0,1 };
      std::cout << "[UrnR][15] is not implemented yet" 
                << std::endl;
   }
   SECTION("15")
   {
      UrnR u { 1,0 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("16")
   {
      UrnR u { 1,1 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("17")
   {
      UrnR u { 2,1 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == true);
      REQUIRE(u.at(0) == 1);
      REQUIRE(u[0] == 1);
      REQUIRE(u.next() == false);
   }
   SECTION("18")
   {
      UrnR u { 2,2 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 2);
      REQUIRE(to_string(u) == "0 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 1");
      REQUIRE(u.next() == false);
   }
   SECTION("19")
   {
      UrnR u { 3,3 };
      REQUIRE(u.n() == 3);
      REQUIRE(u.k() == 3);
      REQUIRE(to_string(u) == "0 0 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 0 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 0 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 2 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 1 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 1 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 2 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "2 2 2");
      REQUIRE(u.next() == false);
   }
}

TEST_CASE("Urn")
{
   using namespace urn;
   SECTION("20")
   {
      Urn u { 0,0 };
      REQUIRE(u.n() == 0);
      REQUIRE(u.k() == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("21")
   {
      //Urn u { 0,1 };
      std::cout << "[Urn][21] is not implemented yet" 
                << std::endl;
   }
   SECTION("22")
   {
      Urn u { 1,1 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("23")
   {
      Urn u { 2,1 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == true);
      REQUIRE(u.at(0) == 1);
      REQUIRE(u[0] == 1);
      REQUIRE(u.next() == false);
   }
   SECTION("24")
   {
      Urn u { 2,2 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 2);
      REQUIRE(to_string(u) == "0 1");
      REQUIRE(u.next() == false);
   }
   SECTION("25")
   {
      Urn u { 3,3 };
      REQUIRE(u.n() == 3);
      REQUIRE(u.k() == 3);
      REQUIRE(to_string(u) == "0 1 2");
      REQUIRE(u.next() == false);
   }
   SECTION("26")
   {
      Urn u { 4,3 };
      REQUIRE(u.n() == 4);
      REQUIRE(u.k() == 3);
      REQUIRE(to_string(u) == "0 1 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1 3");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 2 3");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 2 3");
      REQUIRE(u.next() == false);
   }
}

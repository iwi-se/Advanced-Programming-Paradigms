// OIDManagerUnitTests.cpp by Ulrich Eisenecker, March 18, 2025

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

#include "oid_manager.hpp"

TEST_CASE("CLASS")
{
   using namespace oid_manager;
   Object o1,o2;
   REQUIRE(OIDManager::isKnown(o1) == false);
   REQUIRE(OIDManager::getId(o1) == 1ll);
   REQUIRE(OIDManager::isKnown(o1) == true);
   REQUIRE(OIDManager::isKnown(o2) == false);
   REQUIRE(OIDManager::getId(o2) == 2ll);
   REQUIRE(OIDManager::isKnown(o2) == true);
   REQUIRE(OIDManager::deregister(o1) == true);
   REQUIRE(OIDManager::deregister(o2) == true);
   REQUIRE(OIDManager::deregister(o1) == false);
   REQUIRE(OIDManager::deregister(o2) == false);
}

// CAUTION: The following test case
// requires the prior execution of
// TEST_CASE("StaticCall").
// This violates inherent Catch2
// assumptions!
TEST_CASE("OBJECT")
{
   using namespace oid_manager;
   OIDManager om;
   Object o1,o2;
   REQUIRE(om.isKnown(o1) == false);
   REQUIRE(om.getId(o1) == 3ll);
   REQUIRE(om.isKnown(o1) == true);
   REQUIRE(om.isKnown(o2) == false);
   REQUIRE(om.getId(o2) == 4ll);
   REQUIRE(om.isKnown(o2) == true);
   REQUIRE(om.deregister(o1) == true);
   REQUIRE(om.deregister(o2) == true);
   REQUIRE(om.deregister(o1) == false);
   REQUIRE(om.deregister(o2) == false);
}

// OBCH_UnitTests.cpp by Ulrich Eisenecker, March 18, 2025

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

#include "OBCH.hpp"

TEST_CASE("OBCC")
{
   OBCC o { 6.0 }; // l or gallons per 100 km or miles
   REQUIRE(o.mileage() == 0.0);
   REQUIRE(o.fuel() == 0.0);
   o.addFuel(35.25);
   REQUIRE(o.fuel() == 35.25);
   o.addFuel(0.75);
   REQUIRE(o.fuel() == 36.0);
   REQUIRE(o.remainingRange() == 600.0);
   REQUIRE(o.drive(100.0) == 100.0);
   REQUIRE(o.remainingRange() == 500.0);
   REQUIRE(o.drive(550.0) == 500.0);
   REQUIRE(o.remainingRange() == 0.0);
   REQUIRE(o.mileage() == 600.0);
}

TEST_CASE("OBCE")
{
   OBCE o { 20.0 }; // kWh 100 km or miles
   REQUIRE(o.mileage() == 0.0);
   REQUIRE(o.capacity() == 0.0);
   o.charge(45.0);
   REQUIRE(o.capacity() == 45.0);
   o.charge(15.0);
   REQUIRE(o.capacity() == 60.0);
   REQUIRE(o.remainingRange() == 300.0);
   REQUIRE(o.drive(100.0) == 100.0);
   REQUIRE(o.remainingRange() == 200.0);
   REQUIRE(o.drive(250.0) == 200.0);
   REQUIRE(o.remainingRange() == 0.0);
   REQUIRE(o.mileage() == 300.0);
}

TEST_CASE("OBC/OBCC_REF")
{
   OBCC o { 5.5 };
   OBC& obc { o };
   REQUIRE(obc.mileage() == 0.0);
   o.addFuel(27.5);
   REQUIRE(obc.remainingRange() == 500.0);
   REQUIRE(obc.drive(250.0) == 250.0);
   REQUIRE(obc.remainingRange() == 250.0);
   REQUIRE(obc.mileage() == 250.0);
}

TEST_CASE("OBC/OBCE_REF")
{
   OBCE o { 20.0 };
   OBC& obc { o };
   REQUIRE(obc.mileage() == 0.0);
   o.charge(60.0);
   REQUIRE(obc.remainingRange() == 300.0);
   REQUIRE(obc.drive(200.0) == 200.0);
   REQUIRE(obc.remainingRange() == 100.0);
   REQUIRE(obc.mileage() == 200.0);
}


TEST_CASE("OBC/OBCC_PTR")
{
   OBCC o { 5.5 };
   OBC* obc { &o };
   REQUIRE(obc->mileage() == 0.0);
   o.addFuel(27.5);
   REQUIRE(obc->remainingRange() == 500.0);
   REQUIRE(obc->drive(250.0) == 250.0);
   REQUIRE(obc->remainingRange() == 250.0);
   REQUIRE(obc->mileage() == 250.0);
}

TEST_CASE("OBC/OBCE_PTR")
{
   OBCE o { 20.0 };
   OBC* obc { &o };
   REQUIRE(obc->mileage() == 0.0);
   o.charge(60.0);
   REQUIRE(obc->remainingRange() == 300.0);
   REQUIRE(obc->drive(200.0) == 200.0);
   REQUIRE(obc->remainingRange() == 100.0);
   REQUIRE(obc->mileage() == 200.0);
}

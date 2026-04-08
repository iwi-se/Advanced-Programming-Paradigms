// Cone.cpp by Ulrich Eisenecker, February 17, 2026

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <functional> // Because of bind<>()
#include <iostream>
#include <numbers> // Because of pi<>

[[nodiscard ]] auto coneVolume(double r,double h)
{
   return 1.0 / 3.0 * r * r * std::numbers::pi * h;
}

[[nodiscard ]] double conicalSegmentVolume(double r,double h,double s)
{
   double t { h - s };
   return (r == 0.0 || h == 0.0) ?
             0.0 :
             r * r * std::numbers::pi * h / 3.0 - ((s < h) ?
                conicalSegmentVolume(r * t / h,t,t) :
                0.0);
}

TEST_CASE("CONE_VOLUME")
{
   REQUIRE(coneVolume(1.0,1.0) == std::numbers::pi / 3.0);
   REQUIRE(coneVolume(0.0,1.0) == 0.0);
   REQUIRE(coneVolume(1.0,0.0) == 0.0);
   REQUIRE(coneVolume(0.0,0.0) == 0.0);
   REQUIRE_THAT(coneVolume(2.0,4.0),
                Catch::Matchers::WithinAbs(16.75516082,0.000000005));
}

TEST_CASE("CONIC_SEGMENT_VOLUME")
{
   REQUIRE(conicalSegmentVolume(1.0,1.0,1.0) == coneVolume(1.0,1.0));
   REQUIRE_THAT(conicalSegmentVolume(2.0,4.0,4.0),
                Catch::Matchers::WithinAbs(16.75516082,0.000000005));
   REQUIRE_THAT(conicalSegmentVolume(4.0,8.0,4.0),
                Catch::Matchers::WithinAbs(117.28612573,0.000000005));
}

TEST_CASE("BIND1")
{
   using namespace std::placeholders;
   auto coneVolume2 { std::bind(conicalSegmentVolume,_1,_2,_2) };
   std::cout << coneVolume2(6.0,5.0) << std::endl;
   REQUIRE(conicalSegmentVolume(6.0,5.0,5.0) == coneVolume2(6,5));
   REQUIRE_THAT(conicalSegmentVolume(6.0,5.0,5.0) -
                coneVolume(6.0,5.0),
                Catch::Matchers::WithinAbs(0.0,0.000000005));
}

TEST_CASE("BIND2")
{
   using namespace std::placeholders;
   auto times2 { [](double n) { return 2.0 * n; } };
   auto equilateralConeVolume { std::bind(conicalSegmentVolume,_1,
                                std::bind(times2,_1),
                                std::bind(times2,_1)) };
   std::cout << equilateralConeVolume(6.0) << std::endl;
   REQUIRE_THAT(equilateralConeVolume(6.0),
                Catch::Matchers::WithinAbs(coneVolume(6.0,12.0),0.000000005));
}

TEST_CASE("BIND3")
{
   using namespace std::placeholders;
   auto coneVolume2 { std::bind(conicalSegmentVolume,_1,_2,_2) };
   auto equilateralConeVolume { std::bind(coneVolume2,_1,
                                std::bind([](double n) 
                                          { return 2.0 * n; },_1)) };
   std::cout << equilateralConeVolume(6.0) << std::endl;
   REQUIRE_THAT(equilateralConeVolume(6.0),
                Catch::Matchers::WithinAbs(coneVolume(6.0,12.0),0.000000005));
}

TEST_CASE("BIND4")
{
   using namespace std::placeholders;
   auto equilateralConeVolume { std::bind(coneVolume,_1,
                                std::bind([](double n) 
                                          { return 2.0 * n; },_1)) };
   std::cout << equilateralConeVolume(6.0) << std::endl;
   REQUIRE_THAT(equilateralConeVolume(6.0),
                Catch::Matchers::WithinAbs(coneVolume(6.0,12.0),0.000000005));
}

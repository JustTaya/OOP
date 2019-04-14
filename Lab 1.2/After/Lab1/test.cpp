//
// Created by Taya on 14.04.2019.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "IPParser.h"


TEST_CASE("Parser", "[parser]") {
    auto parser = IPParser();
    SECTION("IPv4") {
        auto parsed = parser.parse("192.0.2.235");
        REQUIRE(parsed.size() == 4);
        REQUIRE(parsed[0] == 192);
        REQUIRE(parsed[1] == 0);
        REQUIRE(parsed[2] == 2);
        REQUIRE(parsed[3] == 235);
    }

    SECTION("IPv6") {
        auto parsed = parser.parse("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
        REQUIRE(parsed.size() == 8);
        REQUIRE(parsed[0] == 0x2001);
        REQUIRE(parsed[1] == 0x0db8);
        REQUIRE(parsed[2] == 0x11a3);
        REQUIRE(parsed[3] == 0x09d7);
        REQUIRE(parsed[4] == 0x1f34);
        REQUIRE(parsed[5] == 0x8a2e);
        REQUIRE(parsed[6] == 0x07a0);
        REQUIRE(parsed[7] == 0x765d);
    }

    SECTION("abbreviated IPv6") {
        auto parsed = parser.parse("2001::1f34:8a2e:07a0:765d");
        REQUIRE(parsed.size() == 8);
        REQUIRE(parsed[0] == 0x2001);
        REQUIRE(parsed[1] == 0);
        REQUIRE(parsed[2] == 0);
        REQUIRE(parsed[3] == 0);
        REQUIRE(parsed[4] == 0x1f34);
        REQUIRE(parsed[5] == 0x8a2e);
        REQUIRE(parsed[6] == 0x07a0);
        REQUIRE(parsed[7] == 0x765d);
    }

    SECTION("zero IPv6") {
        auto parsed = parser.parse("::");
        REQUIRE(parsed.size() == 8);
        REQUIRE(parsed[0] == 0);
        REQUIRE(parsed[1] == 0);
        REQUIRE(parsed[2] == 0);
        REQUIRE(parsed[3] == 0);
        REQUIRE(parsed[4] == 0);
        REQUIRE(parsed[5] == 0);
        REQUIRE(parsed[6] == 0);
        REQUIRE(parsed[7] == 0);
    }

    SECTION("wrong abbreviated IPv6") {
        auto parsed = parser.parse("2001::1f34:8a2e::765d");
        REQUIRE(parsed.empty());
    }


    SECTION("not ip") {
        auto parsed = parser.parse("abc.abc");
        REQUIRE(parsed.empty());
    }
    //REQUIRE( Factorial(1) == 1 );
}
//
// Created by Taya on 14.04.2019.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "IPParser.h"
#include "IPAddress.h"

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

    SECTION("wrong IPv4") {
        auto parsed = parser.parse("300.0.2.235");
        REQUIRE(parsed.empty());
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
}

TEST_CASE("Fabric", "[fabric]") {
    SECTION("IPv4") {
        auto ip = IPFabric::newIP("192.0.2.235");
        REQUIRE(ip != nullptr);
    }
    SECTION("wrong IPv4") {
        auto ip = IPFabric::newIP("300.0.2.235");
        REQUIRE(ip == nullptr);
    }
    SECTION("IPv6") {
        auto ip = IPFabric::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
        REQUIRE(ip != nullptr);
    }
    SECTION("abbreviated IPv6") {
        auto ip = IPFabric::newIP("2001::1f34:8a2e:07a0:765d");
        REQUIRE(ip != nullptr);
    }
    SECTION("zero IPv6") {
        auto ip = IPFabric::newIP("::");
        REQUIRE(ip != nullptr);
    }
    SECTION("wrong abbreviated IPv6") {
        auto ip = IPFabric::newIP("2001::1f34:8a2e::765d");
        REQUIRE(ip == nullptr);
    }
    SECTION("not ip") {
        auto ip = IPFabric::newIP("abc.abc");
        REQUIRE(ip == nullptr);
    }
}

TEST_CASE("IPv4", "[ipv4]") {
    auto ip = IPFabric::newIP("192.0.2.235");
    REQUIRE(ip->getBinary() == "11000000000000000000001011101011");
}

TEST_CASE("IPv6", "[ipv6]") {
    auto ip = IPFabric::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
    REQUIRE(ip->getBinary() ==
            "00100000000000010000110110111000000100011010001100001001110101110001111100110100100010100010111000000111101000000111011001011101");
}
//
// Created by Taya on 14.04.2019.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "IP.h"
#include "SubNetwork.h"

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

TEST_CASE("Factory", "[factory]") {
    SECTION("IPv4") {
        auto ip = IPFactory::newIP("192.0.2.235");
        REQUIRE(ip != nullptr);
    }
    SECTION("wrong IPv4") {
        auto ip = IPFactory::newIP("300.0.2.235");
        REQUIRE(ip == nullptr);
    }
    SECTION("IPv6") {
        auto ip = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
        REQUIRE(ip != nullptr);
    }
    SECTION("abbreviated IPv6") {
        auto ip = IPFactory::newIP("2001::1f34:8a2e:07a0:765d");
        REQUIRE(ip != nullptr);
    }
    SECTION("zero IPv6") {
        auto ip = IPFactory::newIP("::");
        REQUIRE(ip != nullptr);
    }
    SECTION("wrong abbreviated IPv6") {
        auto ip = IPFactory::newIP("2001::1f34:8a2e::765d");
        REQUIRE(ip == nullptr);
    }
    SECTION("not ip") {
        auto ip = IPFactory::newIP("abc.abc");
        REQUIRE(ip == nullptr);
    }
}

TEST_CASE("IPv4", "[ipv4]") {
    auto ip = IPFactory::newIP("192.0.2.235");
    REQUIRE(ip->getBinary() == "11000000000000000000001011101011");
    auto octets = ip->getIP();
    REQUIRE(octets.size() == 4);
    REQUIRE(octets[0] == 192);
    REQUIRE(octets[1] == 0);
    REQUIRE(octets[2] == 2);
    REQUIRE(octets[3] == 235);

    std::ostringstream oss;
    ip->print(oss);
    REQUIRE(oss.str() == "192.0.2.235");
    //std::cout << ip << std::endl;
}

TEST_CASE("IPv6", "[ipv6]") {
    auto ip = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
    REQUIRE(ip->getBinary() ==
            "00100000000000010000110110111000000100011010001100001001110101110001111100110100100010100010111000000111101000000111011001011101");
    auto octets = ip->getIP();
    REQUIRE(octets.size() == 8);
    REQUIRE(octets[0] == 0x2001);
    REQUIRE(octets[1] == 0x0db8);
    REQUIRE(octets[2] == 0x11a3);
    REQUIRE(octets[3] == 0x09d7);
    REQUIRE(octets[4] == 0x1f34);
    REQUIRE(octets[5] == 0x8a2e);
    REQUIRE(octets[6] == 0x07a0);
    REQUIRE(octets[7] == 0x765d);

    std::ostringstream oss;
    ip->print(oss);
    REQUIRE(oss.str() == "2001:db8:11a3:9d7:1f34:8a2e:7a0:765d");
    //std::cout << ip << std::endl;
}

TEST_CASE("IPConvertor", "[ipconvertor]") {
    auto ip1 = IPFactory::newIP("192.168.99.1");
    auto ip2 = IPtoIPv6::convert(ip1);
    auto octets = ip2->getIP();
    REQUIRE(octets.size() == 8);
    REQUIRE(octets[0] == 0);
    REQUIRE(octets[1] == 0);
    REQUIRE(octets[2] == 0);
    REQUIRE(octets[3] == 0);
    REQUIRE(octets[4] == 0);
    REQUIRE(octets[5] == 0xffff);
    REQUIRE(octets[6] == 0xc0a8);
    REQUIRE(octets[7] == 0x631);
}


TEST_CASE("IPComparator", "[ipcomparator]") {
    SECTION("Compare ipv4 with same ipv4") {
        auto ip1 = IPFactory::newIP("209.1.53.165");
        auto ip2 = IPFactory::newIP("209.1.53.165");
        REQUIRE(!IPComparator::cmp(ip1, ip2));
        REQUIRE(!IPComparator::cmp(ip2, ip1));
    }
    SECTION("Compare ipv4 with ipv4") {
        auto ip1 = IPFactory::newIP("209.1.53.165");
        auto ip2 = IPFactory::newIP("209.10.52.165");
        REQUIRE(IPComparator::cmp(ip1, ip2));
        REQUIRE(!IPComparator::cmp(ip2, ip1));
    }
    SECTION("Compare ipv6 with same ipv6") {
        auto ip1 = IPFactory::newIP("2001:db8:11a3:9d7:1f34:8a2e:7a0:765d");
        auto ip2 = IPFactory::newIP("2001:db8:11a3:9d7:1f34:8a2e:7a0:765d");
        REQUIRE(!IPComparator::cmp(ip1, ip2));
        REQUIRE(!IPComparator::cmp(ip2, ip1));
    }
    SECTION("Compare ipv6 with ipv6") {
        auto ip1 = IPFactory::newIP("2001:db8:11a3:9d7:1f34:8a2e:7a0:765d");
        auto ip2 = IPFactory::newIP("2001:db9:10a3:9d7:1f34:8a2e:7a0:765d");
        REQUIRE(IPComparator::cmp(ip1, ip2));
        REQUIRE(!IPComparator::cmp(ip2, ip1));
    }
    SECTION("Compare ipv4 with same ipv6") {
        auto ip1 = IPFactory::newIP("192.168.99.1");
        auto ip2 = IPFactory::newIP("::ffff:c0a8:631");
        REQUIRE(!IPComparator::cmp(ip1, ip2));
        REQUIRE(!IPComparator::cmp(ip2, ip1));
    }
    SECTION("Compare ipv4 with ipv6") {
        auto ip1 = IPFactory::newIP("192.168.99.1");
        auto ip2 = IPFactory::newIP("::ffff:c1a8:631");
        REQUIRE(IPComparator::cmp(ip1, ip2));
        REQUIRE(!IPComparator::cmp(ip2, ip1));
    }
}

TEST_CASE("SubNetwork", "[SubNetwork]") {
    SECTION("ipv4") {
        auto ip = IPFactory::newIP("192.0.2.235");
        auto subnet = SubNetworkFactory::newSubNetwork(ip, 31);
        auto octets = subnet->getIP();
        auto ipOctets = ip->getIP();
        REQUIRE(octets.size() == 4);
        REQUIRE(octets[0] == 192);
        REQUIRE(octets[1] == 0);
        REQUIRE(octets[2] == 2);
        REQUIRE(octets[3] == 235);
        REQUIRE(octets == ipOctets);
        REQUIRE(subnet->getMask() == 31);
        REQUIRE(subnet->getBinary()=="11000000000000000000001011101010");
        std::ostringstream oss;
        subnet->print(oss);
        REQUIRE(oss.str() == "192.0.2.235/31");
    }
    SECTION("ipv6") {
        auto ip = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
        auto subnet = SubNetworkFactory::newSubNetwork(ip, 127);
        auto octets = subnet->getIP();
        auto ipOctets = ip->getIP();
        REQUIRE(octets.size() == 8);
        REQUIRE(octets[0] == 0x2001);
        REQUIRE(octets[1] == 0x0db8);
        REQUIRE(octets[2] == 0x11a3);
        REQUIRE(octets[3] == 0x09d7);
        REQUIRE(octets[4] == 0x1f34);
        REQUIRE(octets[5] == 0x8a2e);
        REQUIRE(octets[6] == 0x07a0);
        REQUIRE(octets[7] == 0x765d);;
        REQUIRE(octets == ipOctets);
        REQUIRE(subnet->getMask() == 127);
        REQUIRE(subnet->getBinary()=="00100000000000010000110110111000000100011010001100001001110101110001111100110100100010100010111000000111101000000111011001011100");
        std::ostringstream oss;
        subnet->print(oss);
        REQUIRE(oss.str() == "2001:db8:11a3:9d7:1f34:8a2e:7a0:765d/127");
    }
}

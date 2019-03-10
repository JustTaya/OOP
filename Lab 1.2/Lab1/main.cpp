#define CATCH_CONFIG_MAIN
//#include "Samples.h"
#include "IPAddress.h"
#include "Tree.h"
#include "catch.hpp"

TEST_CASE("Test IPv6", "[IPv6]") {
    std::string *ip6 = new std::string[8];
    ip6[0] = "2001";
    ip6[1] = "0db8";
    ip6[2] = "11a3";
    ip6[3] = "09d7";
    ip6[4] = "1f34";
    ip6[5] = "8a2e";
    ip6[6] = "07a0";
    ip6[7] = "765d";
    IPv6 ip(ip6);
    REQUIRE(ip.getBinary() == std::bitset<128>(
            "00100000000000010000110110111000000100011010001100001001110101110001111100110100100010100010111000000111101000000111011001011101"));
}

TEST_CASE("Test IPv4", "[IPv4]") {
    unsigned ip4[4];
    ip4[0] = 209;
    ip4[1] = 1;
    ip4[2] = 53;
    ip4[3] = 165;
    IPv4 ip(ip4);
    REQUIRE(ip.getBinary() == std::bitset<32>("11010001000000010011010110100101"));
    std::string *ip6 = new std::string[8];
    ip6[0] = "0";
    ip6[1] = "0";
    ip6[2] = "0";
    ip6[3] = "0";
    ip6[4] = "0";
    ip6[5] = "ffff";
    ip6[6] = "d101";
    ip6[7] = "35a5";
    IPv6 tmp = IPv6(ip6);
    REQUIRE((*ip.converttoIPv6()).getBinary() == tmp.getBinary());
}

TEST_CASE("Test IP", "[IP]") {

    std::string *ip6 = new std::string[8];
    ip6[0] = "0";
    ip6[1] = "0";
    ip6[2] = "0";
    ip6[3] = "0";
    ip6[4] = "0";
    ip6[5] = "ffff";
    ip6[6] = "d101";
    ip6[7] = "35a9";
    SECTION("IPv4") {
        unsigned ip4_1[4];
        ip4_1[0] = 209;
        ip4_1[1] = 1;
        ip4_1[2] = 53;
        ip4_1[3] = 165;
        SECTION("test1") {
            unsigned ip4_2[4];
            ip4_2[0] = 209;
            ip4_2[1] = 1;
            ip4_2[2] = 53;
            ip4_2[3] = 165;

            IP *ipv4 = new IP(ip4_1),
                    *ipv6 = new IP(ip4_2);
            REQUIRE(!ipv4->compare(ipv6));
            REQUIRE(!ipv6->compare(ipv4));
        }
        SECTION("test2") {
            unsigned ip4_2[4];
            ip4_2[0] = 210;
            ip4_2[1] = 1;
            ip4_2[2] = 53;
            ip4_2[3] = 168;

            IP *ipv4 = new IP(ip4_1),
                    *ipv6 = new IP(ip4_2);
            REQUIRE(ipv4->compare(ipv6));
           // REQUIRE(!ipv6->compare(ipv4));
        }
    }
    SECTION("IPv6") {
        //  IP ipv6 = IP(ip6),
        //        ipv4 = IP(ip4);

    }
}

/*
int main() {
    srand(time(NULL));
    int_sample();
    double_sample();
    string_sample();

    std::vector<std::vector<int> *> tmp(4);
    tmp[0]=new std::vector<int>({38,1235,3});
    tmp[1]=new std::vector<int>({88,21,21,0});
    tmp[2]=new std::vector<int>({443,1000,1000,2});
    tmp[3]=new std::vector<int>({1,1,0,1});

    vector_sample(tmp);
    ip_sample();
    subnet_sample();
    return 0;
}
*/

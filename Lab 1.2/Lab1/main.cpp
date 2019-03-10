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

    unsigned ip4[4];
    ip4[0] = 209;
    ip4[1] = 1;
    ip4[2] = 53;
    ip4[3] = 165;

    std::string *ip6 = new std::string[8];
    ip6[0] = "0";
    ip6[1] = "0";
    ip6[2] = "0";
    ip6[3] = "0";
    ip6[4] = "0";
    ip6[5] = "ffff";
    ip6[6] = "d101";
    ip6[7] = "35a9";

    SECTION("test1") {
        unsigned ip4_1[4];
        ip4_1[0] = 209;
        ip4_1[1] = 1;
        ip4_1[2] = 53;
        ip4_1[3] = 165;

        IP *ipv4 = new IP(ip4),
                *ipv6 = new IP(ip4_1);
        REQUIRE(!ipv4->compare(ipv6));
        REQUIRE(!ipv6->compare(ipv4));
    }
    SECTION("test2") {
        std::string *ip6 = new std::string[8];
        ip6[0] = "0";
        ip6[1] = "0";
        ip6[2] = "0";
        ip6[3] = "0";
        ip6[4] = "0";
        ip6[5] = "ffff";
        ip6[6] = "d101";
        ip6[7] = "35a9";

        IP *ipv4_1 = new IP(ip4),
                *ipv6 = new IP(ip6);
        REQUIRE(ipv4_1->compare(ipv6));
        REQUIRE(!ipv6->compare(ipv4_1));
    }
    SECTION("test3") {
        std::string *ip6_1 = new std::string[8];
        ip6_1[0] = "0";
        ip6_1[1] = "0";
        ip6_1[2] = "0";
        ip6_1[3] = "0";
        ip6_1[4] = "0";
        ip6_1[5] = "ffff";
        ip6_1[6] = "d110";
        ip6_1[7] = "35a9";
        IP *ipv6 = new IP(ip6),
                *ipv6_1 = new IP(ip6_1);
        REQUIRE(ipv6->compare(ipv6_1));
        REQUIRE(!ipv6_1->compare(ipv6));
    }
}
/* Subnet(IP *ip, unsigned mask) : ip(ip), mask(mask) {};

    bool check(IP *checkIP);

    bool compare(Subnet *right);    //compare the number of hosts*/
TEST_CASE("Subnetwork test","[subnetwork]"){
    //check
    


    //compare
    SECTION("Compre method test"){

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

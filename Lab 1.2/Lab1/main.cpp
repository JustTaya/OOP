#define CATCH_CONFIG_MAIN
//#include "Samples.h"
#include "IPAddress.h"
#include "Tree.h"
#include "catch.hpp"

TEST_CASE("Test IDv6", "[IDv6]") {
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

TEST_CASE("Test IDv4", "[IDv4]") {
    unsigned ip4[4];
    ip4[0] = 209;
    ip4[1] = 173;
    ip4[2] = 53;
    ip4[3] = 167;
    IPv4 ip(ip4);
    //REQUIRE(ip.getBinary()==std::bitset<32>("11000000000000000000001011101011"));
    std::string *ip6 = new std::string[8];
    ip6[0] = "0";
    ip6[1] = "0";
    ip6[2] = "0";
    ip6[3] = "0";
    ip6[4] = "0";
    ip6[5] = "0";
    ip6[6] = "d1ab";
    ip6[7] = "35a7";
    IPv6* tmp=new IPv6(ip6);
    std::cout<<tmp->getBinary()<<"   ";
    std::cout<<ip.converttoIPv6()->getBinary();
    REQUIRE(ip.converttoIPv6()->getBinary() == tmp->getBinary());
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

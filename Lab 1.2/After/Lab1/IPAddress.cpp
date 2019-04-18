//
// Created by Taya on 13.04.2019.
//

#include "IPAddress.h"


IPv4::IPv4(std::vector<unsigned> ip) : ip(std::move(ip)) {
    setBinary();
}

std::string IPv4::getBinary() const {
    return binary;
}

void IPv4::setBinary() {
    std::string bin;
    for (auto i:ip) {
        std::bitset<8> toBin(i);
        bin += toBin.to_string();
    }
    binary = bin;
}

IPv6::IPv6(std::vector<unsigned> ip) : ip(std::move(ip)) {
    setBinary();
}

std::string IPv6::getBinary() const {
    return binary;
}

void IPv6::setBinary() {
    std::string bin;
    for (auto i:ip) {
        std::bitset<16> toBin(i);
        bin += toBin.to_string();
    }
    binary = bin;
}

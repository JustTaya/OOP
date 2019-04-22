//
// Created by Taya on 13.04.2019.
//

#include "IPAddress.h"

IPv4::IPv4(std::vector<unsigned int> _ip) : ip(std::move(_ip)) {
    setBinary(ip);
}

std::string IPv4::getBinary() {
    return binary;
}

void IPv4::setBinary(const std::vector<unsigned> &_ip) {
    std::string newBinary;
    for (auto i:_ip) {
        newBinary += std::bitset<8>(i).to_string();
    }
    binary = newBinary;
}

void IPv4::print(std::ostringstream &oss) {
    for (std::size_t i = 0; i < ip.size() - 1; ++i) {
        oss << ip[i] << '.';
    }
    oss << ip.back();
}

std::size_t IPv6::findPos() {
    std::size_t pos = 0;
    int count = 0,
            newCount = 0,
            j = -1;
    for (std::size_t i = 0; i < ip.size(); ++i) {
        if (ip[i] == 0) {
            ++newCount;
            if (j == -1) {
                j = i;
            }
        }
        if (ip[i] != 0 || i == ip.size() - 1) {
            if (newCount > count) {
                count = newCount;
                pos = j;
            }
            newCount = 0;
            j = -1;
        }
    }
    return pos;
}

IPv6::IPv6(std::vector<unsigned int> _ip) : ip(std::move(_ip)) {
    setBinary(ip);
}

std::string IPv6::getBinary() {
    return binary;
}

void IPv6::setBinary(const std::vector<unsigned> &_ip) {
    std::string newBinary;
    for (auto i:_ip) {
        newBinary += std::bitset<16>(i).to_string();
    }
    binary = newBinary;
}

void IPv6::print(std::ostringstream &oss) {
    std::size_t pos = findPos();
    for (std::size_t i = 0; i < ip.size(); ++i) {
        if (i == pos && ip[i] == 0) {
            while (ip[i] == 0)
                ++i;
            oss << "::";
        } else {
            oss << std::hex << ip[i];
            if (i != ip.size() - 1 && pos != i + 1)
                oss << ':';
        }
    }
}



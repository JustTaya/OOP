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

std::unique_ptr<IP> IPFabric::newIP(const std::string &ip) {
    static auto parser = IPParser();
    std::vector<unsigned> parsed = parser.parse(ip);
    if (parsed.empty())
        return nullptr;
    switch (parsed.size()) {
        case 4:
            return std::make_unique<IPv4>(IPv4(parsed));
        case 8:
            return std::make_unique<IPv6>(IPv6(parsed));
    }
    return nullptr;
}

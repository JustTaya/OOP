//
// Created by Taya on 22.04.2019.
//

#include "SubNetwork.h"

std::vector<unsigned> SubNetwork::getIP() const {
    return ip->getIP();
}

unsigned SubNetwork::getMask() const {
    return mask;
}

std::string SubNetwork::getBinary() const {
    return applyMask[v](ip->getBinary(),mask);
}

void SubNetwork::print(std::ostringstream &oss) const {
    ip->print(oss);
    oss << "/";
    oss << std::dec << mask;
}

//TODO: check ip
bool SubNetwork::check(IP *_ip) const {
    auto ip1 = IPtoIPv6::convert(ip);
    auto ip2 = IPtoIPv6::convert(_ip);
    if (mask)
        return false;
    return false;
}

std::string SubNetwork::getIPv4Binary(const std::string &binary, unsigned _mask) {
    std::bitset<maxMask[ipv4]> IPv4mask;
    std::bitset<maxMask[ipv4]> result;
    for (int i = maxMask[ipv4] - 1; i >= maxMask[ipv4] - _mask; i--)
        IPv4mask[i] = true;
    result = (std::bitset<maxMask[ipv4]>(binary) & IPv4mask);
    return result.to_string();
}

std::string SubNetwork::getIPv6Binary(const std::string &binary, unsigned _mask) {
    std::bitset<maxMask[ipv6]> IPv6mask;
    std::bitset<maxMask[ipv6]> result;
    for (int i = maxMask[ipv6]; i >= maxMask[ipv6] - _mask; i--)
        IPv6mask[i] = true;
    result = (std::bitset<maxMask[ipv6]>(binary) & IPv6mask);
    return result.to_string();
}

std::string SubNetwork::getBinaryMask(unsigned _mask, SubNetwork::Version _v) const {
    switch (_v) {
        case ipv4: {
            std::bitset<maxMask[ipv4]> IPv4mask;
            for (int i = maxMask[ipv4]; i >= maxMask[ipv4] - _mask; i--)
                IPv4mask[i] = true;
            return IPv4mask.to_string();
        }
        case ipv6: {
            std::bitset<maxMask[ipv6]> IPv6mask;
            for (int i = maxMask[ipv6]; i >= maxMask[ipv6] - _mask; i--)
                IPv6mask[i] = true;
            return IPv6mask.to_string();
        }
    }
}

std::ostream &operator<<(std::ostream &os, const SubNetwork &subnet) {
    std::ostringstream oss;
    subnet.print(oss);
    os << oss.str();
    return os;
}

bool SubNetworkComparator::cmp(const SubNetwork &subnet1, const SubNetwork &subnet2) {
    if (subnet1.getMask() == subnet2.getMask()) {
        return IPComparator::cmp(subnet1.ip, subnet2.ip);
    }
    return (subnet1.getMask() < subnet2.getMask());
}

SubNetwork *SubNetworkFactory::newSubNetwork(IP *ip, unsigned mask) {
    if (auto ipv4 = dynamic_cast<IPv4 *>(ip)) {
        if (mask <= SubNetwork::maxMask[SubNetwork::Version::ipv4]) {
            return new SubNetwork(ip, mask, SubNetwork::Version::ipv4);
        }
    } else if (auto ipv6 = dynamic_cast<IPv6 *>(ip)) {
        if (mask <= SubNetwork::maxMask[SubNetwork::Version::ipv6])
            return new SubNetwork(ip, mask, SubNetwork::Version::ipv6);
    }
    return nullptr;
}

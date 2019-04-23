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
    auto binary = ip->getBinary();
    switch (binary.size()) {
        case maxIPv4Mask: {
            std::bitset<maxIPv4Mask> IPv4mask;
            std::bitset<maxIPv4Mask> result;
            for (int i = maxIPv4Mask - 1; i >= maxIPv4Mask - mask; i--)
                IPv4mask[i] = true;
            result = (std::bitset<maxIPv4Mask>(binary) & IPv4mask);
            return result.to_string();
        }
        case maxIPv6Mask: {
            std::bitset<maxIPv6Mask> IPv6mask;
            std::bitset<maxIPv6Mask> result;
            for (int i = maxIPv6Mask; i >= maxIPv6Mask - mask; i--)
                IPv6mask[i] = true;
            result = (std::bitset<maxIPv6Mask>(binary) & IPv6mask);
            return result.to_string();
        }
    }
    return ip->getBinary();
}

void SubNetwork::print(std::ostringstream &oss) const {
    ip->print(oss);
    oss << "/";
    oss<<std::dec<<mask;
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
        if (mask <= maxIPv4Mask)
            return new SubNetwork(ip, mask);
    } else if (auto ipv6 = dynamic_cast<IPv6 *>(ip)) {
        if (mask <= maxIPv6Mask)
            return new SubNetwork(ip, mask);
    }
    return nullptr;
}

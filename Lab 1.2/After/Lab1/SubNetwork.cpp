//
// Created by Taya on 22.04.2019.
//

#include "SubNetwork.h"

SubNetwork::~SubNetwork() {
    delete ip;
}

IPv4SubNetwork::~IPv4SubNetwork() {
    delete ip;
}

std::vector<unsigned> IPv4SubNetwork::getIP() const {
    return ip->getIP();
}

unsigned IPv4SubNetwork::getMask() const {
    return mask;
}

std::string IPv4SubNetwork::getBinary() const {
    std::bitset<maxMask> IPv4mask;
    std::bitset<maxMask> result;
    for (int i = maxMask - 1; i >= maxMask - mask; i--)
        IPv4mask[i] = true;
    result = (std::bitset<maxMask>(ip->getBinary()) & IPv4mask);
    return result.to_string();
}

void IPv4SubNetwork::print(std::ostringstream &oss) const {
    ip->print(oss);
    oss << "/";
    oss << std::dec << mask;
}

bool IPv4SubNetwork::check(IP *_ip) const {
    if (auto ipv6 = dynamic_cast<IPv6 *>(_ip)) {
        return false;
    }
    std::bitset<maxMask> ipBinary(_ip->getBinary());
    std::bitset<maxMask> subnetBinary(ip->getBinary());
    std::bitset<maxMask> IPv4mask;
    for (int i = maxMask - 1; i >= maxMask - mask; i--)
        IPv4mask[i] = true;
    return ((ipBinary & IPv4mask) == (subnetBinary & IPv4mask));
}

IPv6SubNetwork::~IPv6SubNetwork() {
    delete ip;
}

std::vector<unsigned> IPv6SubNetwork::getIP() const {
    return ip->getIP();
}

unsigned IPv6SubNetwork::getMask() const {
    return mask;
}

std::string IPv6SubNetwork::getBinary() const {
    std::bitset<maxMask> IPv6mask;
    std::bitset<maxMask> result;
    for (int i = maxMask - 1; i >= maxMask - mask; i--)
        IPv6mask[i] = true;
    result = (std::bitset<maxMask>(ip->getBinary()) & IPv6mask);
    return result.to_string();
}

void IPv6SubNetwork::print(std::ostringstream &oss) const {
    ip->print(oss);
    oss << "/";
    oss << std::dec << mask;
}

bool IPv6SubNetwork::check(IP *_ip) const {
    auto tmp = IPtoIPv6::convert(_ip)->getBinary();
    std::bitset<maxMask> ipBinary(tmp);
    std::bitset<maxMask> subnetBinary(ip->getBinary());
    std::bitset<maxMask> IPv6mask;
    for (int i = maxMask - 1; i >= maxMask - mask; i--)
        IPv6mask[i] = true;
    return ((ipBinary & IPv6mask) == (subnetBinary & IPv6mask));
}

bool SubNetworkComparator::operator()(const SubNetwork *subnet1, const SubNetwork *subnet2){
    if (subnet1->getMask() == subnet2->getMask()) {
        IPComparator cmp;
        return cmp(subnet1->ip, subnet2->ip);
    }
    return (subnet1->getMask() < subnet2->getMask());
}

SubNetwork *SubNetworkFactory::newSubNetwork(IP *ip, unsigned mask) {
    if (auto ipv4 = dynamic_cast<IPv4 *>(ip)) {
        if (mask <= IPv4SubNetwork::maxMask) {
            return new IPv4SubNetwork(ip, mask);
        }
    } else if (auto ipv6 = dynamic_cast<IPv6 *>(ip)) {
        if (mask <= IPv6SubNetwork::maxMask)
            return new IPv6SubNetwork(ip, mask);
    }
    return nullptr;
}

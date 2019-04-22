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
    return ip->getBinary();
}

void SubNetwork::print(std::ostringstream &oss) const {
    ip->print(oss);
    oss << "/" << mask;
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

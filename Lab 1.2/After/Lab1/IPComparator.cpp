//
// Created by Taya on 22.04.2019.
//

#include "IPComparator.h"

bool IPComparator::operator()(IP *ip1, IP *ip2) {
    if (ip1 == nullptr || ip2 == nullptr)
        return false;
    auto octets1 = IPtoIPv6::convert(ip1)->getIP();
    auto octets2 = IPtoIPv6::convert(ip2)->getIP();
    for (std::size_t i = 0; i < octets1.size(); ++i) {
        if (octets1[i] < octets2[i])
            return true;
        else if (octets1[i] > octets2[i])
            return false;
    }
    return false;
}

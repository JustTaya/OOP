//
// Created by Taya on 22.04.2019.
//

#include "IPComparator.h"

bool IPComparator::cmp(IP *ip1, IP *ip2) {
    auto octets1 = IPtoIPv6::convert(ip1)->getIP();
    auto octets2 = IPtoIPv6::convert(ip2)->getIP();
    for (std::size_t i = 0; i < octets1.size(); ++i) {
        if(octets1[i]>=octets2[i])
            return false;
    }
    return true;
}

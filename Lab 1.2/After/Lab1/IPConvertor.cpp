//
// Created by Taya on 22.04.2019.
//

#include "IPConvertor.h"

IP *IPtoIPv6::convert(IP *ip) {
    if (auto ipv4 = dynamic_cast<IPv4 *>(ip)) {
        return convertIPv4(ipv4);
    } else if (auto ipv6 = dynamic_cast<IPv6 *>(ip)) {
        return convertIPv6(ipv6);
    }
    return nullptr;
}

IP *IPtoIPv6::convertIPv4(IPv4 *ip) {
    std::vector<unsigned> octets = ip->getIP();
    std::string str = "::ffff:";
    std::ostringstream oss;
    oss << std::hex << octets[0];
    oss << std::hex << octets[1];
    oss << ":";
    oss << std::hex << octets[2];
    oss << std::hex << octets[3];
    str += oss.str();
    return IPFactory::newIP(str);
}

IP *IPtoIPv6::convertIPv6(IPv6 *ip) {
    return ip;
}

//
// Created by Taya on 22.04.2019.
//

#include "IPFactory.h"

IP* IPFactory::newIP(const std::string &ip) {
    static auto parser = IPParser();
    std::vector<unsigned> parsed = parser.parse(ip);
    if (parsed.empty())
        return nullptr;
    switch (parsed.size()) {
        case 4:
            return new IPv4(parsed);
        case 8:
            return new IPv6(parsed);
    }
    return nullptr;
}
//
// Created by Taya on 13.04.2019.
//

#ifndef LAB1_IPFACTORY_H
#define LAB1_IPFACTORY_H

#include "IPAddress.h"
#include "IPParser.h"

#include <memory>

template<typename T>
struct IPFactoty {
    static std::unique_ptr<T> newIP(const std::string &ip);
private:
    static IPParser parser;
};

template<typename T>
std::unique_ptr<T> IPFactoty<T>::newIP(const std::string &ip) {
    auto parsed = parser.parse(ip);
    if (parsed.empty())
        return nullptr;
    return std::make_unique<T>(T(parsed));
}


#endif //LAB1_IPFACTORY_H

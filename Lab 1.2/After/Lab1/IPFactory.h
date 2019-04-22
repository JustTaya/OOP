//
// Created by Taya on 22.04.2019.
//

#ifndef LAB1_IPFACTORY_H
#define LAB1_IPFACTORY_H

#include "IPAddress.h"

class IPFactory {
public:
    static IP *newIP(const std::string &ip);
};


#endif //LAB1_IPFACTORY_H

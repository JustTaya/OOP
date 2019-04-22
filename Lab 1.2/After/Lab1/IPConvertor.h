//
// Created by Taya on 22.04.2019.
//

#ifndef LAB1_IPCONVERTOR_H
#define LAB1_IPCONVERTOR_H

#include "IPFactory.h"

class IPtoIPv6 {
public:
    static IP *convert(IP *ip);

private:
    static IP *convertIPv4(IPv4 *ip);

    static IP *convertIPv6(IPv6 *ip);
};


#endif //LAB1_IPCONVERTOR_H

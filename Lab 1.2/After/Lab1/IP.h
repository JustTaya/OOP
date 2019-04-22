//
// Created by Taya on 13.04.2019.
//

#ifndef LAB1_IP_H
#define LAB1_IP_H

#include "IPFactory.h"

std::ostream &operator<<(std::ostream &os, IP *ip) {
    std::ostringstream oss;
    ip->print(oss);
    os<<oss.str();
    return os;
}

#endif //LAB1_IP_H

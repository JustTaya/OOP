//
// Created by Taya on 22.04.2019.
//

#include "IP.h"

std::ostream &operator<<(std::ostream &os, IP *ip) {
    std::ostringstream oss;
    ip->print(oss);
    os << oss.str();
    return os;
}
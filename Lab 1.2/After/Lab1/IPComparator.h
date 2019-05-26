//
// Created by Taya on 22.04.2019.
//

#ifndef LAB1_IPCOMPARATOR_H
#define LAB1_IPCOMPARATOR_H

#include "IPAddress.h"
#include "IPConvertor.h"

class IPComparator {
public:
    bool operator()( IP *ip1, IP *ip2); //return ip1<ip2
};


#endif //LAB1_IPCOMPARATOR_H

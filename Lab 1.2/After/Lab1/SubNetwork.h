//
// Created by Taya on 22.04.2019.
//

#ifndef LAB1_SUBNETWORK_H
#define LAB1_SUBNETWORK_H

#include "IP.h"

class SubNetwork {
public:
    SubNetwork(IP *ip, unsigned mask) : ip(ip), mask(mask) {};

    std::vector<unsigned> getIP() const;

    unsigned getMask() const;

    std::string getBinary() const;

    void print(std::ostringstream &oss) const;

    friend class SubNetworkComparator;

private:
    IP *ip;
    unsigned mask;
};

std::ostream &operator<<(std::ostream &os, const SubNetwork &subnet);

class SubNetworkComparator {
public:
    static bool cmp(const SubNetwork &subnet1, const SubNetwork &subnet2); //return subnet1<subnet2
};

#endif //LAB1_SUBNETWORK_H

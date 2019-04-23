//
// Created by Taya on 22.04.2019.
//

#ifndef LAB1_SUBNETWORK_H
#define LAB1_SUBNETWORK_H

#include "IP.h"

class SubNetwork {

    SubNetwork(IP *ip, unsigned mask) : ip(ip), mask(mask) {};

    friend class SubNetworkComparator;

    friend class SubNetworkFactory;

public:

    std::vector<unsigned> getIP() const;

    unsigned getMask() const;

    std::string getBinary() const;

    void print(std::ostringstream &oss) const;

private:
    IP *ip;
    unsigned mask;
};

std::ostream &operator<<(std::ostream &os, const SubNetwork &subnet);

class SubNetworkComparator {
public:
    static bool cmp(const SubNetwork &subnet1, const SubNetwork &subnet2); //return subnet1<subnet2
};

class SubNetworkFactory {
public:
    static SubNetwork *newSubNetwork(IP *ip, unsigned mask);

private:
    static const unsigned maxIPv4Mask = 32;
    static const unsigned maxIPv6Mask = 128;
};

#endif //LAB1_SUBNETWORK_H

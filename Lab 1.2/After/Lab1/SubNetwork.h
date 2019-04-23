//
// Created by Taya on 22.04.2019.
//

#ifndef LAB1_SUBNETWORK_H
#define LAB1_SUBNETWORK_H

#include "IP.h"

class SubNetwork {

public:

    std::vector<unsigned> getIP() const;

    unsigned getMask() const;

    std::string getBinary() const;

    void print(std::ostringstream &oss) const;

    bool check(IP *_ip) const;

private:

    friend class SubNetworkComparator;

    friend class SubNetworkFactory;

    enum Version {
        ipv4, ipv6, count
    };

    IP *ip;
    unsigned mask;
    Version v;

    typedef std::string (*Mask)(const std::string &binary, unsigned _mask);


    static std::string getIPv4Binary(const std::string &binary, unsigned _mask);

    static std::string getIPv6Binary(const std::string &binary, unsigned _mask);

    std::string getBinaryMask(unsigned _mask, Version _v) const;

    constexpr static const std::array<unsigned, count> maxMask = {32, 128};
    constexpr const static std::array<Mask, count> applyMask = {&getIPv4Binary, &getIPv6Binary};

    SubNetwork(IP *ip, unsigned mask, Version v) : ip(ip), mask(mask), v(v) {};
};

std::ostream &operator<<(std::ostream &os, const SubNetwork &subnet);

class SubNetworkComparator {
public:
    static bool cmp(const SubNetwork &subnet1, const SubNetwork &subnet2); //return subnet1<subnet2
};

class SubNetworkFactory {
public:
    static SubNetwork *newSubNetwork(IP *ip, unsigned mask);
};

#endif //LAB1_SUBNETWORK_H

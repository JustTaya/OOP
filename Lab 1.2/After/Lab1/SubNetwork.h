//
// Created by Taya on 22.04.2019.
//

#ifndef LAB1_SUBNETWORK_H
#define LAB1_SUBNETWORK_H

#include "IP.h"


class SubNetwork {
public:
    virtual ~SubNetwork();

    virtual std::vector<unsigned> getIP() const = 0;

    virtual unsigned getMask() const = 0;

    virtual std::string getBinary() const = 0;

    virtual void print(std::ostringstream &oss) const = 0;

    virtual bool check(IP *_ip) const = 0;

protected:
    IP *ip;
    unsigned mask;

    SubNetwork(IP *ip, unsigned mask) : ip(ip), mask(mask) {};

    friend class SubNetworkComparator;

    friend class SubNetworkFactory;
};

class IPv4SubNetwork : public SubNetwork {

public:
    ~IPv4SubNetwork() override;

    std::vector<unsigned> getIP() const override;

    unsigned getMask() const override;

    std::string getBinary() const override;

    void print(std::ostringstream &oss) const override;

    bool check(IP *_ip) const override;

private:

    friend class SubNetworkComparator;

    friend class SubNetworkFactory;

    static const unsigned maxMask = 32;

    IPv4SubNetwork(IP *ip, unsigned mask) : SubNetwork(ip, mask) {};
};

class IPv6SubNetwork : public SubNetwork {

public:
    ~IPv6SubNetwork() override;

    std::vector<unsigned> getIP() const override;

    unsigned getMask() const override;

    std::string getBinary() const override;

    void print(std::ostringstream &oss) const override;

    bool check(IP *_ip) const override;

private:

    friend class SubNetworkComparator;

    friend class SubNetworkFactory;

    static const unsigned maxMask = 128;

    IPv6SubNetwork(IP *ip, unsigned mask) : SubNetwork(ip, mask) {};
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

//
// Created by Taya on 24.03.2019.
//

#ifndef LAB1_IP_H
#define LAB1_IP_H

#include <iostream>
#include <string>

class IP {
public:
    IP();

    IP(const IP &ip);

    virtual void getBinary();

    virtual ~IP();

    friend std::ostream &operator<<(std::ostream &os, const IP &);

private:
    virtual void setRandom();
};

class IPv4 : public IP {
public:
    IPv4();

    IPv4(unsigned ip[4]);

    IPv4(const IPv4 &ip);

    void getBinary() override;

private:
    void setRandom() override;
};

class IPv6 : public IP {
public:
    IPv6();

    IPv6(std::string *ip);

    IPv6(const IPv6 &ip);

    void getBinary() override;

private:
    void setRandom() override;
};

class Subnet {
public:
    Subnet() : ip(IP()), mask(128) {};

    Subnet(const IP &ip, unsigned mask) : ip(ip), mask(mask);

    ~Subnet();

    bool check(const IP &ip);

    void getBinary();

    void getIPNumner();

private:
    const IP ip;
    const unsigned mask;
};

#endif //LAB1_IP_H

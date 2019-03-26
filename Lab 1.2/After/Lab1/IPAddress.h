//
// Created by taya on 02.10.18.
//

#ifndef LAB1_1_IPADRESS_H
#define LAB1_1_IPADRESS_H


#include <iostream>
#include <string>
#include <bitset>
#include <vector>


class IP {
public:
    virtual std::string getBinary() const = 0;

    virtual ~IP() = 0;

protected:
    virtual void setRandom() = 0;

    virtual void setBinary() = 0;
};

class IPv4 : public IP {
public:
    IPv4();

    explicit IPv4(const std::vector<unsigned> &ip);

    IPv4(const IPv4 &ip);

    std::string getBinary() const override;

private:
    std::vector<unsigned> octet;

    std::bitset<32> binary;

    void setRandom() override;

    void setBinary() override;
};

class IPv6 : public IP {
public:
    IPv6();

    IPv6(const std::vector<std::string> &ip);

    IPv6(const IPv6 &ip);

//    IPv6(const IPv4& ip);

    std::string getBinary() const override;

private:
    std::vector<std::string> octet;
    std::bitset<128> binary;

    void setRandom() override;

    void setBinary() override;

    void compress();

    void decompress();
};

class Subnet {
public:
    Subnet(const IP *ip, unsigned mask) : ip(ip), mask(mask) {};

    ~Subnet();

    bool check(const IP *ip);

    void getBinary();

    void getIPNumber();

private:
    const IP *ip;
    const unsigned mask;
};

#endif //LAB1_1_IPADRESS_H

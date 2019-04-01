//
// Created by taya on 02.10.18.
//

#ifndef LAB1_1_IPADRESS_H
#define LAB1_1_IPADRESS_H


#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <vector>

class IPFactory;

class IPParser {
public:
    virtual std::string parse(const std::string &ip) = 0;

protected:
    std::vector<std::string> split(const std::string &ip,  const char delimiter);

    virtual std::string parseLexem(std::string) = 0;
};

class IPv4Parser : public IPParser {
public:
    std::string parse(const std::string &ip) override;

private:
    std::string parseLexem(std::string) override;
};

class IPv6Parser : public IPParser {
public:
    std::string parse(const std::string &ip) override;

private:
    std::string parseLexem(std::string) override;
};

class IP {
public:
    virtual std::string getBinary() const = 0;

    virtual ~IP() = 0;

protected:
    static IPFactory factory;

    virtual void setRandom() = 0;

    virtual void setBinary() = 0;
};

class IPv4 : public IP {
public:

    std::string getBinary() const override;

    friend class IPFactory;

private:
    IPv4();

    IPv4(const std::string &ip);

    explicit IPv4(const std::vector<unsigned> &ip);

    IPv4(const IPv4 &ip);


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

    friend class IPFactory;

private:
    IPv6(const std::string &ip, const std::binary &binary);

    std::vector<std::string> octet;
    std::bitset<128> binary;

    void setRandom() override;

    void setBinary() override;
};

class IPFactory {
public:
    static IP newIP4(const std::string &ip) {
        return IPv4(ip);
    };

    static IP newIP6(const std::string &ip) {
        return IPv6(ip);
    };
private:
    static IPv4Parser ipv4Parser;
    static IPv4Parser ipv6Parser;
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

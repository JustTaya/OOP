//
// Created by Taya on 13.04.2019.
//

#ifndef LAB1_IPADDRESS_H
#define LAB1_IPADDRESS_H

#include "IPParser.h"

#include <string>
#include <vector>
#include <memory>
#include <bitset>

class IPFabric;

class IP {
public:
    virtual ~IP() = default;

    virtual std::string getBinary() = 0;

    virtual void print(std::ostringstream &oss) = 0;

protected:
    virtual void setBinary(const std::vector<unsigned> &_ip) = 0;
};

class IPv4 : public IP {
    friend class IPFactory;

    explicit IPv4(std::vector<unsigned> _ip);

    void print(std::ostringstream &oss) override;

public:
    ~IPv4() override = default;

    std::string getBinary() override;

private:
    std::vector<unsigned> ip;
    std::string binary;

    void setBinary(const std::vector<unsigned> &_ip) override;
};

class IPv6 : public IP {
    friend class IPFactory;

    explicit IPv6(std::vector<unsigned> _ip);

public:
    ~IPv6() override = default;

    std::string getBinary() override;

    void print(std::ostringstream &oss) override;

private:
    std::vector<unsigned> ip;
    std::string binary;

    void setBinary(const std::vector<unsigned> &_ip) override;

    std::size_t findPos();
};

#endif //LAB1_IPADDRESS_H
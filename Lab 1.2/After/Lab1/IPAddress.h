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

    virtual std::string getBinary() const = 0;

    virtual std::vector<unsigned> getIP() const = 0;

    virtual void print(std::ostringstream &oss) const = 0;

protected:
    virtual void setBinary(const std::vector<unsigned> &_ip) = 0;
};

class IPv4 : public IP {
    friend class IPFactory;

    explicit IPv4(std::vector<unsigned> _ip);

public:
    ~IPv4() override = default;

    std::vector<unsigned> getIP() const override;

    std::string getBinary() const override;

    void print(std::ostringstream &oss) const override;

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

    std::vector<unsigned> getIP() const override;

    std::string getBinary() const override;

    void print(std::ostringstream &oss) const override;

private:
    std::vector<unsigned> ip;
    std::string binary;

    void setBinary(const std::vector<unsigned> &_ip) override;

    std::size_t findPos() const;
};

#endif //LAB1_IPADDRESS_H
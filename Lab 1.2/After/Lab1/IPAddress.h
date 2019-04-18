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


//interface for IPs
class IP {
public:
    virtual ~IP() = default;

    virtual std::string getBinary() const = 0;

private:
    virtual void setBinary() = 0;
};

class IPv4 : public IP {
public:
    IPv4() = delete;

    ~IPv4() = default;

    std::string getBinary() const override;

    friend class IPFactory;

private:
    std::vector<unsigned> ip;
    std::string binary;

    explicit IPv4(std::vector<unsigned> ip);

    friend class IPFactory;

    void setBinary() override;
};

class IPv6 : public IP {
public:
    IPv6() = delete;

    ~IPv6() = default;

    std::string getBinary() const override;

    friend class IPFactory;

private:
    std::vector<unsigned> ip;
    std::string binary;

    explicit IPv6(std::vector<unsigned> ip);

    void setBinary() override;
};
/*
class IPFactoty {
    static std::unique_ptr<IP> newIP(const std::string &ip);
};

std::unique_ptr<IP> IPFactoty::newIP(const std::string &ip) {
    static IPParser parser = IPParser();
    auto parsed = parser.parse(ip);
    if (parsed.empty())
        return nullptr;
    switch (parsed.size()) {
        case 4:
            return std::make_unique<IP>(IPv4(parsed));
        case 8:
            return std::make_unique<IP>(IPv6(parsed));
    }
}
*/
#endif //LAB1_IPADDRESS_H
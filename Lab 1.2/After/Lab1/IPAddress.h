//
// Created by Taya on 13.04.2019.
//

#ifndef LAB1_IPADDRESS_H
#define LAB1_IPADDRESS_H

#include <string>
#include <vector>

//interface for IPs
class IP {
public:
    virtual ~IP() = default;

    virtual std::string getBinary() = 0;

private:
    virtual std::string setBinary() = 0;
};

class IPv4 : public IP {
public:
    ~IPv4();

    std::string getBinary() override;

private:
    std::vector<unsigned> ip;
    std::string binary;

    friend class IPFactory;

    IPv4(std::vector<unsigned> &ip);

    std::string setBinary() override;
};

class IPv6 : public IP {
public:
    ~IPv6();

    std::string getBinary() override;

private:

    std::vector<unsigned> ip;
    std::string binary;

    friend class IPFactory;

    IPv6(std::vector<unsigned> &ip);

    std::string setBinary() override;
};


#endif //LAB1_IPADDRESS_H

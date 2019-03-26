//
// Created by taya on 02.10.18.
//



#include "IPAddress.h"
#include "Convert.h"

/*

Subnet::Subnet() {
    this->ip = new IP();
    if (this->ip->version == v4)
        this->mask = rand() % 33;   //from 0 to 32
    else
        this->mask = rand() % 129;  //from 0 to 128
}

bool Subnet::check(IP *checkIP) {
    if (this->ip->version != checkIP->version) {
        IPv6 *tmp;
        std::bitset<128> subnet;    //bitset of subnet ip
        std::bitset<128> check;     //bitset of ip to check
        std::bitset<128> mask;
        if (this->ip->version == v6) {
            subnet = this->ip->address.ipv6->getBinary();
            tmp = checkIP->address.ipv4->converttoIPv6();
            check = tmp->getBinary();
            for (int i = 127; i >= (128 - this->mask); i--)
                mask[i] = 1;
        } else {
            tmp = this->ip->address.ipv4->converttoIPv6();
            subnet = tmp->getBinary();
            check = checkIP->address.ipv6->getBinary();
            for (int i = 127; i >= (96 + this->mask); i--)    //127-(32-this->mask)
                mask[i] = 1;
        }
        subnet = subnet & mask;
        check = check & mask;
        if (subnet == check)
            return true;
    } else {
        if (this->ip->version == v4) {
            std::bitset<32> subnet = this->ip->address.ipv4->getBinary();    //bitset of subnet ip
            std::bitset<32> check = checkIP->address.ipv4->getBinary();     //bitset of ip to check
            std::bitset<32> mask;
            for (int i = 31; i >= 32 - this->mask; i--)
                mask[i] = 1;
            subnet = subnet & mask;
            check = check & mask;
            if (subnet == check)
                return true;
        } else {

            std::bitset<128> subnet = this->ip->address.ipv6->getBinary();    //bitset of subnet ip
            std::bitset<128> check = checkIP->address.ipv6->getBinary();     //bitset of ip to check
            std::bitset<128> mask;
            for (int i = 127; i >= 128 - this->mask; i--)
                mask[i] = 1;
            subnet = subnet & mask;
            check = check & mask;
            if (subnet == check)
                return true;
        }
    }
    return false;
}

bool Subnet::compare(Subnet *right) {
    return (this->mask < right->mask);    //2^mask-2 is number of hosts in subnet, so compare masks
}

void Subnet::print() {
    this->ip->print();
    std::cout << "/" << this->mask;
}

*/
IPv4::IPv4() : octet(std::vector<unsigned>(4, 0)) {
    setRandom();
    setBinary();
}

IPv4::IPv4(const std::vector<unsigned int> &ip) : octet(std::vector<unsigned>(4, 0)) {
    for (size_t i = 0; (i < 4) && i < ip.size(); i++)
        octet[i] = ip[i];
    setBinary();
}

IPv4::IPv4(const IPv4 &ip) : octet(ip.octet), binary(ip.binary) {}

std::string IPv4::getBinary() const {
    return this->binary.to_string();
}

void IPv4::setRandom() {
    for (size_t i = 0; i < 4; i++) {
        this->octet[i] = rand() % 256;
    }
}

void IPv4::setBinary() {
    int it = 0;
    int tmp = 0;
    for (int i = 3; i >= 0; i--) {
        tmp = this->octet[i];
        for (int j = 0; j < 8; j++) {
            if (tmp % 2 == 0)
                this->binary[it] = 0;
            else
                this->binary[it] = 1;
            it++;
            tmp /= 2;
        }
    }
}

IPv6::IPv6() : octet(std::vector<std::string>(8, "")) {
    setRandom();
    setBinary();
}

IPv6::IPv6(const std::vector<std::string> &ip) {
    for (size_t i = 0; (i < 8) && (i < ip.size()); i++)
        octet[i] = ip[i];
    setBinary();
    compress();
}

IPv6::IPv6(const IPv6 &ip) : octet(ip.octet), binary(ip.binary) {}

std::string IPv6::getBinary() const {
    return this->binary.to_string();
}

void IPv6::setRandom() {
    int n = 0, tmp = 0;
    for (size_t i = 0; i < 8; i++) {
        tmp = rand() % 16;
        if (tmp < 10)
            this->octet[i].push_back(tmp + 48);
        else
            this->octet[i].push_back(tmp + 87);
    }
}

void IPv6::setBinary() {
    int it = 0;
    std::string tmp, buff;
    for (int i = 7; i >= 0; i--) {
        tmp = this->octet[i];
        for (int j = 3; j >= 0; j--) {
            buff = hextoBin[tmp[j]];
            for (int k = 3; k >= 0; k--) {
                if (buff[k] == '0')
                    this->binary[it] = 0;
                else
                    this->binary[it] = 1;
                it++;
            }
        }
    }
}

void IPv6::compress() {
    for (size_t i = 0; i < 8; i++) {
        while (this->octet[i][0] == '0')
            this->octet[i].erase(0, 1);
    }
}

void IPv6::decompress() {

}



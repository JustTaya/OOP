//
// Created by Taya on 13.04.2019.
//

#ifndef LAB1_IPPARSER_H
#define LAB1_IPPARSER_H

#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <functional>

#include <iostream>

typedef bool (*Convertor)(std::istringstream &, unsigned &);


class IPParser {
public:
    IPParser();

    std::vector<unsigned> parse(const std::string &ip);

    ~IPParser() = default;

private:
    enum Version {
        ipv4, ipv6, count
    };
    std::array<unsigned, count> octetNumb;
    std::array<unsigned, count> octetMax;
    std::array<Convertor, count> convertor;

    std::vector<std::string> splitIPv4(const std::string &ip, const char delimiter);

    std::vector<std::string> splitIPv6(const std::string &ip, const char delimiter);


    std::vector<unsigned> parseTokens(const std::vector<std::string> &tokens, const Version v);

    static bool parseIPv4Token(std::istringstream &iss, unsigned &parsed);

    static bool parseIPv6Token(std::istringstream &iss, unsigned &parsed);
};


#endif //LAB1_IPPARSER_H

//
// Created by Taya on 13.04.2019.
//

#include "IPParser.h"

IPParser::IPParser() {
    octetNumb[ipv4] = 4;
    octetNumb[ipv6] = 8;

    octetMax[ipv4] = 255;
    octetMax[ipv6] = 65535;
}

std::vector<unsigned> IPParser::parse(const std::string &ip) {
    //get delimiter
    unsigned pos = ip.find_first_of(":.");
    if (pos == std::string::npos)
        return std::vector<unsigned int>();

    char delimiter = ip[pos];
    std::vector<std::string> tokens;

    switch (ip[pos]) {
        case '.':
            tokens = splitIPv4(ip, delimiter);
            return parseTokens(tokens, ipv4);
        case ':':
            tokens = splitIPv6(ip, delimiter);
            return parseTokens(tokens, ipv6);
    }

    return std::vector<unsigned int>();
}

std::vector<std::string> IPParser::splitIPv4(const std::string &ip, const char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(ip);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> IPParser::splitIPv6(const std::string &ip, const char delimiter) {
    std::vector<std::string> tokens,
            buffer;
    tokens.reserve(octetNumb[ipv6]);
    std::string token;
    std::istringstream tokenStream(ip);
    //ipv6 can consist "::"
    while (std::getline(tokenStream, token, delimiter)) {
        if (token.empty()) {
            if (!tokens.empty())
                return std::vector<std::string>();
            tokens.insert(tokens.end(), buffer.begin(), buffer.end());
            buffer.clear();
            buffer.emplace_back("0");
        } else {
            buffer.push_back(token);
        }
    }

    //count shift after ::
    if (buffer.size() > octetNumb[ipv6])
        return std::vector<std::string>();
    tokens.resize(octetNumb[ipv6] - buffer.size(), "0");
    tokens.insert(tokens.end(), buffer.begin(), buffer.end());
    return tokens;
}

std::vector<unsigned>
IPParser::parseTokens(const std::vector<std::string> &tokens, const Version v) {
    if (tokens.size() != octetNumb[v])
        return std::vector<unsigned>();

    auto parsed = std::vector<unsigned>(octetNumb[v], 0);
    unsigned tmp, j = 0;

    typedef bool (*Convertor)(std::istringstream &, unsigned &);
    Convertor convertor;
    switch (v) {
        case ipv4:
            convertor = &parseIPv4Token;
            break;
        case ipv6:
            convertor = &parseIPv6Token;
            break;
    }

    for (auto i:tokens) {
        std::istringstream iss(i);
        if (convertor(iss, tmp)) {
            if (tmp <= octetMax[v])
                parsed[j] = tmp;
            else
                return std::vector<unsigned>();
        } else {
            return std::vector<unsigned>();
        }
        ++j;
    }
    return parsed;
}


bool IPParser::parseIPv4Token(std::istringstream &iss, unsigned &parsed) {
    if (iss >> parsed)
        return true;
    return false;
}

bool IPParser::parseIPv6Token(std::istringstream &iss, unsigned &parsed) {
    if (iss >> std::hex >> parsed)
        return true;
    return false;
}


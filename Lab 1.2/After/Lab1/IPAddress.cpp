//
// Created by taya on 02.10.18.
//



#include "IPAddress.h"
#include "Convert.h"


std::vector<std::string> IPParser::split(const std::string &ip, const char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(ip);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

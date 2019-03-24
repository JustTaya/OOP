//
// Created by Taya on 24.03.2019.
//

#ifndef LAB1_IP_H
#define LAB1_IP_H


class IP {
public:
    IP();
    IP(const IP& ip);
    //void print();
    friend std::ostream&operator<<(std::ostream& os, const IP&)

};

class IPv4{

};


#endif //LAB1_IP_H

#define CATCH_CONFIG_MAIN
//#include "Samples.h"
#include "IPAddress.h"
#include "Tree.h"
#include "catch.hpp"
#include <random>
#include <ctime>

TEST_CASE("Test IPv4", "[IPv4]"){
    std::vector<unsigned >ip4{209,2,53,165};
    ip4[0] = 209;
    ip4[1] = 1;
    ip4[2] = 53;
    ip4[3] = 165;
    IPv4 ip(ip4);
    //REQUIRE(ip.getBinary() == std::bitset<32>("11010001000000010011010110100101"));
}

/*
//IPAdress tests
TEST_CASE("Test IPv6", "[IPv6]") {
    std::string *ip6 = new std::string[8];
    ip6[0] = "2001";
    ip6[1] = "0db8";
    ip6[2] = "11a3";
    ip6[3] = "09d7";
    ip6[4] = "1f34";
    ip6[5] = "8a2e";
    ip6[6] = "07a0";
    ip6[7] = "765d";
    IPv6 ip(ip6);
    REQUIRE(ip.getBinary() == std::bitset<128>(
            "00100000000000010000110110111000000100011010001100001001110101110001111100110100100010100010111000000111101000000111011001011101"));
    delete[] ip6;
}

TEST_CASE("Test IPv4", "[IPv4]") {
    unsigned ip4[4];
    ip4[0] = 209;
    ip4[1] = 1;
    ip4[2] = 53;
    ip4[3] = 165;
    IPv4 ip(ip4);
    REQUIRE(ip.getBinary() == std::bitset<32>("11010001000000010011010110100101"));
    std::string *ip6 = new std::string[8];
    ip6[0] = "0";
    ip6[1] = "0";
    ip6[2] = "0";
    ip6[3] = "0";
    ip6[4] = "0";
    ip6[5] = "ffff";
    ip6[6] = "d101";
    ip6[7] = "35a5";
    IPv6 tmp = IPv6(ip6);
    REQUIRE((*ip.converttoIPv6()).getBinary() == tmp.getBinary());
    delete[] ip6;
}

TEST_CASE("Test IP", "[IP]") {

    unsigned ip4[4];
    ip4[0] = 209;
    ip4[1] = 1;
    ip4[2] = 53;
    ip4[3] = 165;

    std::string *ip6 = new std::string[8];
    ip6[0] = "0";
    ip6[1] = "0";
    ip6[2] = "0";
    ip6[3] = "0";
    ip6[4] = "0";
    ip6[5] = "ffff";
    ip6[6] = "d101";
    ip6[7] = "35a9";

    SECTION("test1") {
        unsigned ip4_1[4];
        ip4_1[0] = 209;
        ip4_1[1] = 1;
        ip4_1[2] = 53;
        ip4_1[3] = 165;

        IP ipv4(ip4),
                ipv6(ip4_1);
        REQUIRE(!ipv4.compare(&ipv6));
        REQUIRE(!ipv6.compare(&ipv4));
    }
    SECTION("test2") {
        IP ipv4_1(ip4),
                ipv6(ip6);
        REQUIRE(ipv4_1.compare(&ipv6));
        REQUIRE(!ipv6.compare(&ipv4_1));
    }
    SECTION("test3") {
        std::string *ip6_1 = new std::string[8];
        ip6_1[0] = "0";
        ip6_1[1] = "0";
        ip6_1[2] = "0";
        ip6_1[3] = "0";
        ip6_1[4] = "0";
        ip6_1[5] = "ffff";
        ip6_1[6] = "d110";
        ip6_1[7] = "35a9";
        IP ipv6(ip6),
                ipv6_1(ip6_1);
        REQUIRE(ipv6.compare(&ipv6_1));
        REQUIRE(!ipv6_1.compare(&ipv6));
        delete[] ip6_1;
    }
    delete[] ip6;
}

TEST_CASE("Subnetwork test", "[subnetwork]") {
    //check
    SECTION("Check method test") {
        unsigned ip4[4];
        ip4[0] = 209;
        ip4[1] = 1;
        ip4[2] = 53;
        ip4[3] = 165;
        IP ip(ip4);
        Subnet netw(&ip, 128);
        REQUIRE(netw.check(&ip));
    }
    //compare
    SECTION("Compare method test") {
        unsigned ip4[4];
        ip4[0] = 209;
        ip4[1] = 1;
        ip4[2] = 53;
        ip4[3] = 165;
        IP ip(ip4);
        Subnet netw1(&ip, 128),
                netw2(&ip, 120);
        REQUIRE(!netw1.compare(&netw1));
        REQUIRE(netw2.compare(&netw1));
        REQUIRE(!netw1.compare(&netw2));
    }
}

//Node tests
TEST_CASE("MultiNode class test", "[multinode]") {
    srand(time(NULL));
    int tmp = 10;
    MultiNode<int> node(tmp);
    REQUIRE(node.getKey() == tmp);
    REQUIRE(node.nodes.empty());
}

TEST_CASE("BinNode class test", "[binnode]") {
    srand(time(NULL));
    int tmp = 10;
    BinNode<int> node(tmp);
    REQUIRE(node.getKey() == tmp);
    REQUIRE(node.left == nullptr);
    REQUIRE(node.right == nullptr);
}

//TODO: fix copypaste
//TODO: put ips and subnetworks to tree

TEST_CASE("MultiTree class", "[multitree]") {
    SECTION("Empty tree") {
        MultiTree<int, std::less<int>> tree;
        REQUIRE(tree.getRoot() == nullptr);
        REQUIRE(tree.search(10) == nullptr);
        REQUIRE(!tree.deleteNode(10));
        SECTION("Add elements") {
            int tmp = 10,
                    tmp1 = 3,
                    tmp2 = 5;

            SECTION("root") {
                REQUIRE(tree.insertRoot(tmp));
                REQUIRE(tree.search(tmp)->getKey() == tmp);
                REQUIRE(tree.getRoot()->getKey() == tmp);
                REQUIRE(tree.getRoot() == tree.search(tmp));
                REQUIRE(!tree.insertRoot(tmp));


                SECTION("insert") {
                    REQUIRE(tree.search(tmp1) == nullptr);
                    tree.insert(tree.search(tmp), tmp1);
                    tree.insert(tree.search(tmp), tmp2);
                    REQUIRE(tree.search(tmp1)->getKey() == tmp1);
                    REQUIRE(tree.search(tmp2)->getKey() == tmp2);

                    SECTION("delete") {
                        tree.deleteNode(tmp1);
                        REQUIRE(tree.search(tmp1) == nullptr);
                    }
                }
            }
        }
    }
    SECTION("Tree with root") {
        int tmp = 10,
                tmp1 = 3,
                tmp2 = 5;
        MultiTree<int, std::less<int>> tree(tmp);

        SECTION("root") {
            REQUIRE(tree.search(tmp)->getKey() == tmp);
            REQUIRE(tree.getRoot()->getKey() == tmp);
            REQUIRE(tree.getRoot() == tree.search(tmp));
            REQUIRE(!tree.insertRoot(tmp));
        }

        SECTION("insert") {
            REQUIRE(tree.search(tmp1) == nullptr);
            tree.insert(tree.search(tmp), tmp1);
            tree.insert(tree.search(tmp), tmp2);
            REQUIRE(tree.search(tmp1)->getKey() == tmp1);
            REQUIRE(tree.search(tmp2)->getKey() == tmp2);
            SECTION("delete") {
                tree.deleteNode(tmp1);
                REQUIRE(tree.search(tmp1) == nullptr);
            }
        }
    }
}


TEST_CASE("BinTree class", "[bintree]") {
    SECTION("Empty tree") {
        BinTree<int, std::less<int>> tree;
        REQUIRE(tree.getRoot() == nullptr);
        REQUIRE(tree.search(10) == nullptr);
        REQUIRE(!tree.deleteNode(10));
        SECTION("Add elements") {
            int tmp = 10,
                    tmp1 = 3,
                    tmp2 = 5;
            SECTION("root") {
                REQUIRE(tree.insertRoot(tmp));
                REQUIRE(tree.search(tmp)->getKey() == tmp);
                REQUIRE(tree.getRoot()->getKey() == tmp);
                REQUIRE(tree.getRoot() == tree.search(tmp));
                REQUIRE(!tree.insertRoot(tmp));


                SECTION("insert") {
                    REQUIRE(tree.search(tmp1) == nullptr);
                    REQUIRE(tree.insertleft(tree.search(tmp), tmp1));
                    REQUIRE(tree.insertright(tree.search(tmp), tmp2));
                    REQUIRE(!tree.insertleft(tree.search(tmp), tmp1));
                    REQUIRE(!tree.insertright(tree.search(tmp), tmp2));
                    REQUIRE(tree.search(tmp1)->getKey() == tmp1);
                    REQUIRE(tree.search(tmp2)->getKey() == tmp2);

                    SECTION("delete") {
                        tree.deleteNode(tmp1);
                        REQUIRE(tree.search(tmp1) == nullptr);
                    }
                }
            }
        }
    }
    SECTION("Tree with root") {
        int tmp = 10,
                tmp1 = 3,
                tmp2 = 5;
        BinTree<int, std::less<int>> tree(tmp);

        SECTION("root") {
            REQUIRE(tree.search(tmp)->getKey() == tmp);
            REQUIRE(tree.getRoot()->getKey() == tmp);
            REQUIRE(tree.getRoot() == tree.search(tmp));
            REQUIRE(!tree.insertRoot(tmp));
        }

        SECTION("insert") {
            REQUIRE(tree.search(tmp1) == nullptr);
            REQUIRE(tree.insertleft(tree.search(tmp), tmp1));
            REQUIRE(tree.insertright(tree.search(tmp), tmp2));
            REQUIRE(!tree.insertleft(tree.search(tmp), tmp1));
            REQUIRE(!tree.insertright(tree.search(tmp), tmp2));
            REQUIRE(tree.search(tmp1)->getKey() == tmp1);
            REQUIRE(tree.search(tmp2)->getKey() == tmp2);
            SECTION("delete") {
                tree.deleteNode(tmp1);
                REQUIRE(tree.search(tmp1) == nullptr);
            }
        }
    }
}


TEST_CASE("BSTree class", "[bstree]") {
    SECTION("Empty tree") {
        BSTree<int> tree;
        REQUIRE(tree.search(10) == nullptr);
        REQUIRE(!tree.deleteNode(10));
        SECTION("Add elements") {
            int tmp = 10,
                    tmp1 = 3,
                    tmp2 = 5;
            SECTION("root") {
                REQUIRE(tree.insertRoot(tmp));
                REQUIRE(tree.search(tmp)->getKey() == tmp);
                REQUIRE(!tree.insertRoot(tmp));

                SECTION("insert") {
                    REQUIRE(tree.search(tmp1) == nullptr);
                    tree.insertNode(tmp1);
                    tree.insertNode(tmp2);
                    REQUIRE(tree.search(tmp1)->getKey() == tmp1);
                    REQUIRE(tree.search(tmp2)->getKey() == tmp2);
                    SECTION("delete") {
                        tree.deleteNode(tmp1);
                        REQUIRE(tree.search(tmp1) == nullptr);
                    }
                }
            }
        }
    }


    SECTION("Tree with root") {
        int tmp = 10,
                tmp1 = 3,
                tmp2 = 5;
        BSTree<int> tree(tmp);

        SECTION("insert") {
            REQUIRE(tree.search(tmp1) == nullptr);
            tree.insertNode(tmp1);
            tree.insertNode(tmp2);
            REQUIRE(tree.search(tmp1)->getKey() == tmp1);
            REQUIRE(tree.search(tmp2)->getKey() == tmp2);
            SECTION("delete") {
                tree.deleteNode(tmp1);
                REQUIRE(tree.search(tmp1) == nullptr);
            }
        }
    }
}


*/
/*
int main() {
    srand(time(NULL));
    int_sample();
    double_sample();
    string_sample();

    std::vector<std::vector<int> *> tmp(4);
    tmp[0]=new std::vector<int>({38,1235,3});
    tmp[1]=new std::vector<int>({88,21,21,0});
    tmp[2]=new std::vector<int>({443,1000,1000,2});
    tmp[3]=new std::vector<int>({1,1,0,1});

    vector_sample(tmp);
    ip_sample();
    subnet_sample();
    return 0;
}
*/

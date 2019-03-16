#define CATCH_CONFIG_MAIN
//#include "Samples.h"
#include "IPAddress.h"
#include "Tree.h"
#include "catch.hpp"
#include <random>
#include <ctime>

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

        IP *ipv4 = new IP(ip4),
                *ipv6 = new IP(ip4_1);
        REQUIRE(!ipv4->compare(ipv6));
        REQUIRE(!ipv6->compare(ipv4));
        delete ipv4, ipv6;
    }
    SECTION("test2") {
        IP *ipv4_1 = new IP(ip4),
                *ipv6 = new IP(ip6);
        REQUIRE(ipv4_1->compare(ipv6));
        REQUIRE(!ipv6->compare(ipv4_1));
        delete ipv4_1, ipv6;
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
        IP *ipv6 = new IP(ip6),
                *ipv6_1 = new IP(ip6_1);
        REQUIRE(ipv6->compare(ipv6_1));
        REQUIRE(!ipv6_1->compare(ipv6));
        delete[] ip6_1;
        delete ipv6, ipv6_1;
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
        IP *ip = new IP(ip4);
        Subnet *netw = new Subnet(ip, 128);
        REQUIRE(netw->check(ip));
        delete ip, netw;
    }
    //compare
    SECTION("Compare method test") {
        unsigned ip4[4];
        ip4[0] = 209;
        ip4[1] = 1;
        ip4[2] = 53;
        ip4[3] = 165;
        IP *ip = new IP(ip4);
        Subnet *netw1 = new Subnet(ip, 128),
                *netw2 = new Subnet(ip, 120);
        REQUIRE(!netw1->compare(netw1));
        REQUIRE(netw2->compare(netw1));
        REQUIRE(!netw1->compare(netw2));
        delete ip, netw1, netw2;
    }
}

//Node tests
TEST_CASE("MultiNode class test", "[multinode]") {
    srand(time(NULL));
    int tmp = rand() % 1000;
    MultiNode<int> *node = new MultiNode<int>(tmp);
    REQUIRE(node->getKey() == tmp);
    REQUIRE(node->nodes.empty());
    delete node;
}

TEST_CASE("BinNode class test", "[binnode]") {
    srand(time(NULL));
    int tmp = rand() % 1000;
    BinNode<int> *node = new BinNode<int>(tmp);
    REQUIRE(node->getKey() == tmp);
    REQUIRE(node->left == nullptr);
    REQUIRE(node->right == nullptr);
    delete node;
}

TEST_CASE("MultiTree class", "[multitree]") {
    SECTION("Empty tree") {
        MultiTree<int, std::less<int>> *tree = new MultiTree<int, std::less<int>>();
        REQUIRE(tree->getRoot() == nullptr);
        REQUIRE(tree->search(rand()) == nullptr);
        REQUIRE(!tree->deleteNode(rand()));
        SECTION("Add elements") {
            int tmp = rand() % 500,
                    tmp1 = rand() % 500 + 500,
                    tmp2 = rand() % 500 + 500;

            SECTION("root") {
                REQUIRE(tree->insertRoot(tmp));
                REQUIRE(tree->search(tmp)->getKey() == tmp);
                REQUIRE(tree->getRoot()->getKey() == tmp);
                REQUIRE(tree->getRoot() == tree->search(tmp));
                REQUIRE(!tree->insertRoot(tmp));


                SECTION("insert") {
                    REQUIRE(tree->search(tmp1) == nullptr);
                    tree->insert(tree->search(tmp), tmp1);
                    tree->insert(tree->search(tmp), tmp2);
                    REQUIRE(tree->search(tmp1)->getKey() == tmp1);
                    REQUIRE(tree->search(tmp2)->getKey() == tmp2);

                    SECTION("delete") {
                        tree->deleteNode(tmp1);
                        REQUIRE(tree->search(tmp1) == nullptr);
                    }
                }
            }
        }
    }
    SECTION("Tree with root") {
        int tmp = rand() % 500,
                tmp1 = rand() % 500 + 500,
                tmp2 = rand() % 500 + 500;
        MultiTree<int, std::less<int>> *tree = new MultiTree<int, std::less<int>>(tmp);

        SECTION("root") {
            REQUIRE(tree->search(tmp)->getKey() == tmp);
            REQUIRE(tree->getRoot()->getKey() == tmp);
            REQUIRE(tree->getRoot() == tree->search(tmp));
            REQUIRE(!tree->insertRoot(tmp));
        }

        SECTION("insert") {
            REQUIRE(tree->search(tmp1) == nullptr);
            tree->insert(tree->search(tmp), tmp1);
            tree->insert(tree->search(tmp), tmp2);
            REQUIRE(tree->search(tmp1)->getKey() == tmp1);
            REQUIRE(tree->search(tmp2)->getKey() == tmp2);
            SECTION("delete") {
                tree->deleteNode(tmp1);
                REQUIRE(tree->search(tmp1) == nullptr);
            }
        }
        delete tree;
    }
}


TEST_CASE("BinTree class", "[bintree]") {
    SECTION("Empty tree") {
        BinTree<int, std::less<int>> *tree = new BinTree<int, std::less<int>>();
        REQUIRE(tree->getRoot() == nullptr);
        REQUIRE(tree->search(rand()) == nullptr);
        REQUIRE(!tree->deleteNode(rand()));
        SECTION("Add elements") {
            int tmp = rand() % 500,
                    tmp1 = rand() % 500 + 500,
                    tmp2 = rand() % 500 + 500;

            SECTION("root") {
                REQUIRE(tree->insertRoot(tmp));
                REQUIRE(tree->search(tmp)->getKey() == tmp);
                REQUIRE(tree->getRoot()->getKey() == tmp);
                REQUIRE(tree->getRoot() == tree->search(tmp));
                REQUIRE(!tree->insertRoot(tmp));


                SECTION("insert") {
                    REQUIRE(tree->search(tmp1) == nullptr);
                    REQUIRE(tree->insertleft(tree->search(tmp), tmp1));
                    REQUIRE(tree->insertright(tree->search(tmp), tmp2));
                    REQUIRE(!tree->insertleft(tree->search(tmp),tmp1));
                    REQUIRE(!tree->insertright(tree->search(tmp),tmp2));
                    REQUIRE(tree->search(tmp1)->getKey() == tmp1);
                    REQUIRE(tree->search(tmp2)->getKey() == tmp2);

                    SECTION("delete") {
                        tree->deleteNode(tmp1);
                        REQUIRE(tree->search(tmp1) == nullptr);
                    }
                }
            }
        }
    }
    SECTION("Tree with root") {
        int tmp = rand() % 500,
                tmp1 = rand() % 500 + 500,
                tmp2 = rand() % 500 + 500;
        BinTree<int, std::less<int>> *tree = new BinTree<int, std::less<int>>(tmp);

        SECTION("root") {
            REQUIRE(tree->search(tmp)->getKey() == tmp);
            REQUIRE(tree->getRoot()->getKey() == tmp);
            REQUIRE(tree->getRoot() == tree->search(tmp));
            REQUIRE(!tree->insertRoot(tmp));
        }

        SECTION("insert") {
            REQUIRE(tree->search(tmp1) == nullptr);
            REQUIRE(tree->insertleft(tree->search(tmp), tmp1));
            REQUIRE(tree->insertright(tree->search(tmp), tmp2));
            REQUIRE(!tree->insertleft(tree->search(tmp),tmp1));
            REQUIRE(!tree->insertright(tree->search(tmp),tmp2));
            REQUIRE(tree->search(tmp1)->getKey() == tmp1);
            REQUIRE(tree->search(tmp2)->getKey() == tmp2);
            SECTION("delete") {
                tree->deleteNode(tmp1);
                REQUIRE(tree->search(tmp1) == nullptr);
            }
        }
        delete tree;
    }
}

TEST_CASE("BSTree class","[bstree]")
{
    SECTION("Empty tree") {
        MultiTree<int, std::less<int>> *tree = new MultiTree<int, std::less<int>>();
        REQUIRE(tree->getRoot() == nullptr);
        REQUIRE(tree->search(rand()) == nullptr);
        REQUIRE(!tree->deleteNode(rand()));
        SECTION("Add elements") {
            int tmp = rand() % 500,
                    tmp1 = rand() % 500 + 500,
                    tmp2 = rand() % 500 + 500;

            SECTION("root") {
                REQUIRE(tree->insertRoot(tmp));
                REQUIRE(tree->search(tmp)->getKey() == tmp);
                REQUIRE(tree->getRoot()->getKey() == tmp);
                REQUIRE(tree->getRoot() == tree->search(tmp));
                REQUIRE(!tree->insertRoot(tmp));


                SECTION("insert") {
                    REQUIRE(tree->search(tmp1) == nullptr);
                    tree->insert(tree->search(tmp), tmp1);
                    tree->insert(tree->search(tmp), tmp2);
                    REQUIRE(tree->search(tmp1)->getKey() == tmp1);
                    REQUIRE(tree->search(tmp2)->getKey() == tmp2);

                    SECTION("delete") {
                        tree->deleteNode(tmp1);
                        REQUIRE(tree->search(tmp1) == nullptr);
                    }
                }
            }
        }
    }
    SECTION("Tree with root") {
        int tmp = rand() % 500,
                tmp1 = rand() % 500 + 500,
                tmp2 = rand() % 500 + 500;
        MultiTree<int, std::less<int>> *tree = new MultiTree<int, std::less<int>>(tmp);

        SECTION("root") {
            REQUIRE(tree->search(tmp)->getKey() == tmp);
            REQUIRE(tree->getRoot()->getKey() == tmp);
            REQUIRE(tree->getRoot() == tree->search(tmp));
            REQUIRE(!tree->insertRoot(tmp));
        }

        SECTION("insert") {
            REQUIRE(tree->search(tmp1) == nullptr);
            tree->insert(tree->search(tmp), tmp1);
            tree->insert(tree->search(tmp), tmp2);
            REQUIRE(tree->search(tmp1)->getKey() == tmp1);
            REQUIRE(tree->search(tmp2)->getKey() == tmp2);
            SECTION("delete") {
                tree->deleteNode(tmp1);
                REQUIRE(tree->search(tmp1) == nullptr);
            }
        }
        delete tree;
    }
}

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

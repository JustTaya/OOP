//
// Created by Taya on 14.04.2019.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "IP.h"
#include "SubNetwork.h"
#include "Tree.h"

//IP tests

TEST_CASE("Parser", "[parser]") {
    auto parser = IPParser();
    SECTION("IPv4") {
        auto parsed = parser.parse("192.0.2.235");
        REQUIRE(parsed.size() == 4);
        REQUIRE(parsed[0] == 192);
        REQUIRE(parsed[1] == 0);
        REQUIRE(parsed[2] == 2);
        REQUIRE(parsed[3] == 235);
    }

    SECTION("wrong IPv4") {
        auto parsed = parser.parse("300.0.2.235");
        REQUIRE(parsed.empty());
    }

    SECTION("IPv6") {
        auto parsed = parser.parse("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
        REQUIRE(parsed.size() == 8);
        REQUIRE(parsed[0] == 0x2001);
        REQUIRE(parsed[1] == 0x0db8);
        REQUIRE(parsed[2] == 0x11a3);
        REQUIRE(parsed[3] == 0x09d7);
        REQUIRE(parsed[4] == 0x1f34);
        REQUIRE(parsed[5] == 0x8a2e);
        REQUIRE(parsed[6] == 0x07a0);
        REQUIRE(parsed[7] == 0x765d);
    }

    SECTION("abbreviated IPv6") {
        auto parsed = parser.parse("2001::1f34:8a2e:07a0:765d");
        REQUIRE(parsed.size() == 8);
        REQUIRE(parsed[0] == 0x2001);
        REQUIRE(parsed[1] == 0);
        REQUIRE(parsed[2] == 0);
        REQUIRE(parsed[3] == 0);
        REQUIRE(parsed[4] == 0x1f34);
        REQUIRE(parsed[5] == 0x8a2e);
        REQUIRE(parsed[6] == 0x07a0);
        REQUIRE(parsed[7] == 0x765d);
    }

    SECTION("zero IPv6") {
        auto parsed = parser.parse("::");
        REQUIRE(parsed.size() == 8);
        REQUIRE(parsed[0] == 0);
        REQUIRE(parsed[1] == 0);
        REQUIRE(parsed[2] == 0);
        REQUIRE(parsed[3] == 0);
        REQUIRE(parsed[4] == 0);
        REQUIRE(parsed[5] == 0);
        REQUIRE(parsed[6] == 0);
        REQUIRE(parsed[7] == 0);
    }

    SECTION("wrong abbreviated IPv6") {
        auto parsed = parser.parse("2001::1f34:8a2e::765d");
        REQUIRE(parsed.empty());
    }

    SECTION("not ip") {
        auto parsed = parser.parse("abc.abc");
        REQUIRE(parsed.empty());
    }
}

TEST_CASE("Factory", "[factory]") {
    SECTION("IPv4") {
        auto ip = IPFactory::newIP("192.0.2.235");
        REQUIRE(ip != nullptr);
    }
    SECTION("wrong IPv4") {
        auto ip = IPFactory::newIP("300.0.2.235");
        REQUIRE(ip == nullptr);
    }
    SECTION("IPv6") {
        auto ip = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
        REQUIRE(ip != nullptr);
    }
    SECTION("abbreviated IPv6") {
        auto ip = IPFactory::newIP("2001::1f34:8a2e:07a0:765d");
        REQUIRE(ip != nullptr);
    }
    SECTION("zero IPv6") {
        auto ip = IPFactory::newIP("::");
        REQUIRE(ip != nullptr);
    }
    SECTION("wrong abbreviated IPv6") {
        auto ip = IPFactory::newIP("2001::1f34:8a2e::765d");
        REQUIRE(ip == nullptr);
    }
    SECTION("not ip") {
        auto ip = IPFactory::newIP("abc.abc");
        REQUIRE(ip == nullptr);
    }
}

TEST_CASE("IPv4", "[ipv4]") {
    auto ip = IPFactory::newIP("192.0.2.235");
    REQUIRE(ip->getBinary() == "11000000000000000000001011101011");
    auto octets = ip->getIP();
    REQUIRE(octets.size() == 4);
    REQUIRE(octets[0] == 192);
    REQUIRE(octets[1] == 0);
    REQUIRE(octets[2] == 2);
    REQUIRE(octets[3] == 235);

    std::ostringstream oss;
    ip->print(oss);
    REQUIRE(oss.str() == "192.0.2.235");
    //std::cout << ip << std::endl;
}

TEST_CASE("IPv6", "[ipv6]") {
    auto ip = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
    REQUIRE(ip->getBinary() ==
            "00100000000000010000110110111000000100011010001100001001110101110001111100110100100010100010111000000111101000000111011001011101");
    auto octets = ip->getIP();
    REQUIRE(octets.size() == 8);
    REQUIRE(octets[0] == 0x2001);
    REQUIRE(octets[1] == 0x0db8);
    REQUIRE(octets[2] == 0x11a3);
    REQUIRE(octets[3] == 0x09d7);
    REQUIRE(octets[4] == 0x1f34);
    REQUIRE(octets[5] == 0x8a2e);
    REQUIRE(octets[6] == 0x07a0);
    REQUIRE(octets[7] == 0x765d);

    std::ostringstream oss;
    ip->print(oss);
    REQUIRE(oss.str() == "2001:db8:11a3:9d7:1f34:8a2e:7a0:765d");
    //std::cout << ip << std::endl;
}

TEST_CASE("IPConvertor", "[ipconvertor]") {
    auto ip1 = IPFactory::newIP("192.168.99.1");
    auto ip2 = IPtoIPv6::convert(ip1);
    auto octets = ip2->getIP();
    REQUIRE(octets.size() == 8);
    REQUIRE(octets[0] == 0);
    REQUIRE(octets[1] == 0);
    REQUIRE(octets[2] == 0);
    REQUIRE(octets[3] == 0);
    REQUIRE(octets[4] == 0);
    REQUIRE(octets[5] == 0xffff);
    REQUIRE(octets[6] == 0xc0a8);
    REQUIRE(octets[7] == 0x631);
}

TEST_CASE("IPComparator", "[ipcomparator]") {
    IPComparator cmp;
    SECTION("Compare ipv4 with same ipv4") {
        auto ip1 = IPFactory::newIP("209.1.53.165");
        auto ip2 = IPFactory::newIP("209.1.53.165");
        REQUIRE(!cmp(ip1, ip2));
        REQUIRE(!cmp(ip2, ip1));
    }
    SECTION("Compare ipv4 with ipv4") {
        auto ip1 = IPFactory::newIP("209.1.53.165");
        auto ip2 = IPFactory::newIP("209.10.52.165");
        REQUIRE(cmp(ip1, ip2));
        REQUIRE(!cmp(ip2, ip1));
    }
    SECTION("Compare ipv6 with same ipv6") {
        auto ip1 = IPFactory::newIP("2001:db8:11a3:9d7:1f34:8a2e:7a0:765d");
        auto ip2 = IPFactory::newIP("2001:db8:11a3:9d7:1f34:8a2e:7a0:765d");
        REQUIRE(!cmp(ip1, ip2));
        REQUIRE(!cmp(ip2, ip1));
    }
    SECTION("Compare ipv6 with ipv6") {
        auto ip1 = IPFactory::newIP("2001:db8:11a3:9d7:1f34:8a2e:7a0:765d");
        auto ip2 = IPFactory::newIP("2001:db9:10a3:9d7:1f34:8a2e:7a0:765d");
        REQUIRE(cmp(ip1, ip2));
        REQUIRE(!cmp(ip2, ip1));
    }
    SECTION("Compare ipv4 with same ipv6") {
        auto ip1 = IPFactory::newIP("192.168.99.1");
        auto ip2 = IPFactory::newIP("::ffff:c0a8:631");
        REQUIRE(!cmp(ip1, ip2));
        REQUIRE(!cmp(ip2, ip1));
    }
    SECTION("Compare ipv4 with ipv6") {
        auto ip1 = IPFactory::newIP("192.168.99.1");
        auto ip2 = IPFactory::newIP("::ffff:c1a8:631");
        REQUIRE(cmp(ip1, ip2));
        REQUIRE(!cmp(ip2, ip1));
    }
}

//Subnetwork tests

TEST_CASE("SubNetwork", "[SubNetwork]") {
    SECTION("ipv4") {
        auto ip = IPFactory::newIP("192.0.2.235");
        auto checkIP1 = IPFactory::newIP("192.0.2.234");
        auto checkIP2 = IPFactory::newIP("192.0.2.238");
        auto checkIP3 = IPFactory::newIP("2000:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
        auto subnet = SubNetworkFactory::newSubNetwork(ip, 31);
        auto octets = subnet->getIP();
        auto ipOctets = ip->getIP();
        REQUIRE(octets.size() == 4);
        REQUIRE(octets[0] == 192);
        REQUIRE(octets[1] == 0);
        REQUIRE(octets[2] == 2);
        REQUIRE(octets[3] == 235);
        REQUIRE(octets == ipOctets);
        REQUIRE(subnet->getMask() == 31);
        REQUIRE(subnet->getBinary() == "11000000000000000000001011101010");
        REQUIRE(subnet->check(ip));
        REQUIRE(subnet->check(checkIP1));
        REQUIRE(!subnet->check(checkIP2));
        REQUIRE(!subnet->check(checkIP3));
        std::ostringstream oss;
        subnet->print(oss);
        REQUIRE(oss.str() == "192.0.2.235/31");
    }
    SECTION("ipv6") {
        auto ip = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
        auto checkIP1 = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
        auto checkIP2 = IPFactory::newIP("2000:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
        auto subnet = SubNetworkFactory::newSubNetwork(ip, 127);
        auto octets = subnet->getIP();
        auto ipOctets = ip->getIP();
        REQUIRE(octets.size() == 8);
        REQUIRE(octets[0] == 0x2001);
        REQUIRE(octets[1] == 0x0db8);
        REQUIRE(octets[2] == 0x11a3);
        REQUIRE(octets[3] == 0x09d7);
        REQUIRE(octets[4] == 0x1f34);
        REQUIRE(octets[5] == 0x8a2e);
        REQUIRE(octets[6] == 0x07a0);
        REQUIRE(octets[7] == 0x765d);
        REQUIRE(octets == ipOctets);
        REQUIRE(subnet->getMask() == 127);
        REQUIRE(subnet->getBinary() ==
                "00100000000000010000110110111000000100011010001100001001110101110001111100110100100010100010111000000111101000000111011001011100");
        REQUIRE(subnet->check(checkIP1));
        REQUIRE(!subnet->check(checkIP2));
        std::ostringstream oss;
        subnet->print(oss);
        REQUIRE(oss.str() == "2001:db8:11a3:9d7:1f34:8a2e:7a0:765d/127");
    }
}

TEST_CASE("SubNetworkComparator", "[SubNetworkComparator]") {
    SubNetworkComparator cmp;
    SECTION("ipv4 subnetwork comparison") {
        SECTION("equal ip & mask") {
            auto ip1 = IPFactory::newIP("192.0.2.235");
            auto ip2 = IPFactory::newIP("192.0.2.235");

            auto subnet1 = SubNetworkFactory::newSubNetwork(ip1, 31);
            auto subnet2 = SubNetworkFactory::newSubNetwork(ip2, 31);

            REQUIRE(!cmp(subnet1, subnet2));
            REQUIRE(!cmp(subnet2, subnet1));
        }
        SECTION("equal ip") {
            auto ip1 = IPFactory::newIP("192.0.2.235");
            auto ip2 = IPFactory::newIP("192.0.2.235");

            auto subnet1 = SubNetworkFactory::newSubNetwork(ip1, 31);
            auto subnet2 = SubNetworkFactory::newSubNetwork(ip2, 28);

            REQUIRE(!cmp(subnet1, subnet2));
            REQUIRE(cmp(subnet2, subnet1));
        }
        SECTION("equal mask") {
            auto ip1 = IPFactory::newIP("192.0.2.235");
            auto ip2 = IPFactory::newIP("190.0.2.235");

            auto subnet1 = SubNetworkFactory::newSubNetwork(ip1, 31);
            auto subnet2 = SubNetworkFactory::newSubNetwork(ip2, 31);

            REQUIRE(!cmp(subnet1, subnet2));
            REQUIRE(cmp(subnet2, subnet1));
        }
        SECTION("different") {
            auto ip1 = IPFactory::newIP("192.0.2.235");
            auto ip2 = IPFactory::newIP("190.0.2.235");

            auto subnet1 = SubNetworkFactory::newSubNetwork(ip1, 31);
            auto subnet2 = SubNetworkFactory::newSubNetwork(ip2, 28);

            REQUIRE(!cmp(subnet1, subnet2));
            REQUIRE(cmp(subnet2, subnet1));
        }
    }
    SECTION("ipv6 subnetwork comparison") {
        SECTION("equal ip & mask") {
            auto ip1 = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
            auto ip2 = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");

            auto subnet1 = SubNetworkFactory::newSubNetwork(ip1, 127);
            auto subnet2 = SubNetworkFactory::newSubNetwork(ip2, 127);

            REQUIRE(!cmp(subnet1, subnet2));
            REQUIRE(!cmp(subnet2, subnet1));
        }
        SECTION("equal ip") {
            auto ip1 = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
            auto ip2 = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");

            auto subnet1 = SubNetworkFactory::newSubNetwork(ip1, 127);
            auto subnet2 = SubNetworkFactory::newSubNetwork(ip2, 120);

            REQUIRE(!cmp(subnet1, subnet2));
            REQUIRE(cmp(subnet2, subnet1));
        }
        SECTION("equal mask") {
            auto ip1 = IPFactory::newIP("2001:0db8:ffff:09d7:1f34:8a2e:07a0:765d");
            auto ip2 = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");

            auto subnet1 = SubNetworkFactory::newSubNetwork(ip1, 127);
            auto subnet2 = SubNetworkFactory::newSubNetwork(ip2, 127);

            REQUIRE(!cmp(subnet1, subnet2));
            REQUIRE(cmp(subnet2, subnet1));
        }
        SECTION("different") {
            auto ip1 = IPFactory::newIP("2001:0db8:ffff:09d7:1f34:8a2e:07a0:765d");
            auto ip2 = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");

            auto subnet1 = SubNetworkFactory::newSubNetwork(ip1, 127);
            auto subnet2 = SubNetworkFactory::newSubNetwork(ip2, 120);

            REQUIRE(!cmp(subnet1, subnet2));
            REQUIRE(cmp(subnet2, subnet1));
        }
    }
    SECTION("ipv4 & ipv6 subnetwork comparison") {
        SECTION("equal ip & mask") {
            auto ip1 = IPFactory::newIP("192.168.99.1");
            auto ip2 = IPFactory::newIP("::ffff:c0a8:631");

            auto subnet1 = SubNetworkFactory::newSubNetwork(ip1, 31);
            auto subnet2 = SubNetworkFactory::newSubNetwork(ip2, 31);

            REQUIRE(!cmp(subnet1, subnet2));
            REQUIRE(!cmp(subnet2, subnet1));
        }
        SECTION("equal ip") {
            auto ip1 = IPFactory::newIP("192.168.99.1");
            auto ip2 = IPFactory::newIP("::ffff:c0a8:631");

            auto subnet1 = SubNetworkFactory::newSubNetwork(ip1, 31);
            auto subnet2 = SubNetworkFactory::newSubNetwork(ip2, 20);

            REQUIRE(!cmp(subnet1, subnet2));
            REQUIRE(cmp(subnet2, subnet1));
        }
        SECTION("equal mask") {
            auto ip1 = IPFactory::newIP("192.168.99.1");
            auto ip2 = IPFactory::newIP("::ffff:c1a8:631");

            auto subnet1 = SubNetworkFactory::newSubNetwork(ip1, 31);
            auto subnet2 = SubNetworkFactory::newSubNetwork(ip2, 31);

            REQUIRE(cmp(subnet1, subnet2));
            REQUIRE(!cmp(subnet2, subnet1));
        }
        SECTION("different") {
            auto ip1 = IPFactory::newIP("192.168.99.1");
            auto ip2 = IPFactory::newIP("::ffff:c1a8:631");

            auto subnet1 = SubNetworkFactory::newSubNetwork(ip1, 31);
            auto subnet2 = SubNetworkFactory::newSubNetwork(ip2, 20);

            REQUIRE(!cmp(subnet1, subnet2));
            REQUIRE(cmp(subnet2, subnet1));
        }
    }
}

//Tree tests

TEST_CASE("MultiNode", "[MultiNode]") {
    SECTION("int") {
        auto node = new MultiNode<int>(10, nullptr);
        REQUIRE(node->getKey() == 10);
        REQUIRE(node->getParent() == nullptr);
        REQUIRE(node->getChildren().empty());
    }
    SECTION("ip") {
        SECTION("ipv4") {
            auto ip = IPFactory::newIP("192.0.2.235");
            auto node = new MultiNode<IP *>(ip, nullptr);
            REQUIRE(node->getKey() == ip);
            REQUIRE(node->getParent() == nullptr);
            REQUIRE(node->getChildren().empty());
        }
        SECTION("ipv6") {
            auto ip = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
            auto node = new MultiNode<IP *>(ip, nullptr);
            REQUIRE(node->getKey() == ip);
            REQUIRE(node->getParent() == nullptr);
            REQUIRE(node->getChildren().empty());
        }
    }
    SECTION("subnet") {
        SECTION("ipv4") {
            auto ip = IPFactory::newIP("192.0.2.235");
            auto subnet = SubNetworkFactory::newSubNetwork(ip, 31);
            auto node = new MultiNode<SubNetwork *>(subnet, nullptr);
            REQUIRE(node->getKey() == subnet);
            REQUIRE(node->getParent() == nullptr);
            REQUIRE(node->getChildren().empty());
        }
        SECTION("ipv6") {
            auto ip = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
            auto subnet = SubNetworkFactory::newSubNetwork(ip, 127);
            auto node = new MultiNode<SubNetwork *>(subnet, nullptr);
            REQUIRE(node->getKey() == subnet);
            REQUIRE(node->getParent() == nullptr);
            REQUIRE(node->getChildren().empty());
        }
    }
}

TEST_CASE("BinNode", "[BinNode]") {
    SECTION("int") {
        auto node = new BinaryNode<int>(10, nullptr);
        REQUIRE(node->getKey() == 10);
        REQUIRE(node->getParent() == nullptr);
        REQUIRE(node->getChildren().size() == 2);
        REQUIRE(node->getLeft() == nullptr);
        REQUIRE(node->getRight() == nullptr);
    }
    SECTION("ip") {
        SECTION("ipv4") {
            auto ip = IPFactory::newIP("192.0.2.235");
            auto node = new BinaryNode<IP *>(ip, nullptr);
            REQUIRE(node->getKey() == ip);
            REQUIRE(node->getParent() == nullptr);
            REQUIRE(node->getChildren().size() == 2);
            REQUIRE(node->getLeft() == nullptr);
            REQUIRE(node->getRight() == nullptr);
        }
        SECTION("ipv6") {
            auto ip = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
            auto node = new BinaryNode<IP *>(ip, nullptr);
            REQUIRE(node->getKey() == ip);
            REQUIRE(node->getParent() == nullptr);
            REQUIRE(node->getChildren().size() == 2);
            REQUIRE(node->getLeft() == nullptr);
            REQUIRE(node->getRight() == nullptr);
        }
    }
    SECTION("subnet") {
        SECTION("ipv4") {
            auto ip = IPFactory::newIP("192.0.2.235");
            auto subnet = SubNetworkFactory::newSubNetwork(ip, 31);
            auto node = new BinaryNode<SubNetwork *>(subnet, nullptr);
            REQUIRE(node->getKey() == subnet);
            REQUIRE(node->getParent() == nullptr);
            REQUIRE(node->getChildren().size() == 2);
            REQUIRE(node->getLeft() == nullptr);
            REQUIRE(node->getRight() == nullptr);
        }
        SECTION("ipv6") {
            auto ip = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
            auto subnet = SubNetworkFactory::newSubNetwork(ip, 127);
            auto node = new BinaryNode<SubNetwork *>(subnet, nullptr);
            REQUIRE(node->getKey() == subnet);
            REQUIRE(node->getParent() == nullptr);
            REQUIRE(node->getChildren().size() == 2);
            REQUIRE(node->getLeft() == nullptr);
            REQUIRE(node->getRight() == nullptr);
        }
    }
}

TEST_CASE("MultiTree", "[MultiTree]") {
    SECTION("int") {
        SECTION("Empty tree") {
            auto tree = new MultiTree<int, std::less<>>();
            REQUIRE(tree->getRoot() == nullptr);
            REQUIRE(tree->search(10) == nullptr);

            SECTION("Insertion") {
                tree->insert(3);
                REQUIRE(tree->getRoot() != nullptr);
                REQUIRE(tree->getRoot()->getKey() == 3);
                tree->insert(5);
                REQUIRE(tree->search(5) != nullptr);
                REQUIRE(tree->getRoot()->getChildren()[0]->getKey() == 5);
                std::string path = "0";
                tree->insert(10, path, ' ', 0);
                REQUIRE(tree->search(10) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(7, pathVector, 1);
                REQUIRE(tree->search(7) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(3);
                tree->insert(5);
                std::string path = "0";
                tree->insert(10, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(7, pathVector, 1);

                tree->deleteNode(7);
                REQUIRE(tree->search(7) == nullptr);
                tree->deleteNode(10);
                REQUIRE(tree->search(10) == nullptr);
                tree->deleteNode(5);
                REQUIRE(tree->search(5) == nullptr);
                tree->deleteNode(3);
                REQUIRE(tree->search(3) == nullptr);
            }
        }
        SECTION("Tree with root") {
            auto tree = new MultiTree<int, std::less<>>(3);
            SECTION("Insertion") {
                REQUIRE(tree->getRoot() != nullptr);
                REQUIRE(tree->getRoot()->getKey() == 3);
                tree->insert(5);
                REQUIRE(tree->search(5) != nullptr);
                REQUIRE(tree->getRoot()->getChildren()[0]->getKey() == 5);
                std::string path = "0";
                tree->insert(10, path, ' ', 0);
                REQUIRE(tree->search(10) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(7, pathVector, 1);
                REQUIRE(tree->search(7) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(5);
                std::string path = "0";
                tree->insert(10, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(7, pathVector, 1);

                tree->deleteNode(7);
                REQUIRE(tree->search(7) == nullptr);
                tree->deleteNode(10);
                REQUIRE(tree->search(10) == nullptr);
                tree->deleteNode(5);
                REQUIRE(tree->search(5) == nullptr);
                tree->deleteNode(3);
                REQUIRE(tree->search(3) == nullptr);
            }
        }
    }
    SECTION("ip") {
        auto ip1 = IPFactory::newIP("192.0.2.235");
        auto ip2 = IPFactory::newIP("192.0.2.236");
        auto ip3 = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
        auto ip4 = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:ffff:07a0:765d");

        SECTION("Empty tree") {
            auto tree = new MultiTree<IP *, IPComparator>();
            REQUIRE(tree->getRoot() == nullptr);
            REQUIRE(tree->search(IPFactory::newIP("192.0.2.235")) == nullptr);

            SECTION("Insertion") {
                tree->insert(ip1);
                REQUIRE(tree->getRoot() != nullptr);
                tree->insert(ip2);
                REQUIRE(tree->search(ip2) != nullptr);
                std::string path = "0";
                tree->insert(ip3, path, ' ', 0);
                REQUIRE(tree->search(ip3) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(ip4, pathVector, 1);
                REQUIRE(tree->search(ip4) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(ip1);
                tree->insert(ip2);
                std::string path = "0";
                tree->insert(ip3, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(ip4, pathVector, 1);

                tree->deleteNode(ip4);
                REQUIRE(tree->search(ip4) == nullptr);
                tree->deleteNode(ip3);
                REQUIRE(tree->search(ip3) == nullptr);
                tree->deleteNode(ip2);
                REQUIRE(tree->search(ip2) == nullptr);
                tree->deleteNode(ip1);
                REQUIRE(tree->search(ip1) == nullptr);
            }
        }
        SECTION("Tree with root") {
            auto tree = new MultiTree<IP *, IPComparator>(ip1);
            SECTION("Insertion") {
                REQUIRE(tree->getRoot() != nullptr);
                tree->insert(ip2);
                REQUIRE(tree->search(ip2) != nullptr);
                std::string path = "0";
                tree->insert(ip3, path, ' ', 0);
                REQUIRE(tree->search(ip3) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(ip4, pathVector, 1);
                REQUIRE(tree->search(ip4) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(ip2);
                std::string path = "0";
                tree->insert(ip3, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(ip4, pathVector, 1);

                tree->deleteNode(ip4);
                REQUIRE(tree->search(ip4) == nullptr);
                tree->deleteNode(ip3);
                REQUIRE(tree->search(ip3) == nullptr);
                tree->deleteNode(ip2);
                REQUIRE(tree->search(ip2) == nullptr);
                tree->deleteNode(ip1);
                REQUIRE(tree->search(ip1) == nullptr);
            }
        }
    }

    SECTION("subnet") {
        auto subnet1 = SubNetworkFactory::newSubNetwork(IPFactory::newIP("192.0.2.235"), 31);
        auto subnet2 = SubNetworkFactory::newSubNetwork(IPFactory::newIP("192.0.2.236"), 27);
        auto subnet3 = SubNetworkFactory::newSubNetwork(IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d"),
                                                        127);
        auto subnet4 = SubNetworkFactory::newSubNetwork(IPFactory::newIP("2001:0db8:11a3:09d7:1f34:ffff:07a0:765d"),
                                                        120);


        SECTION("Empty tree") {
            auto tree = new MultiTree<SubNetwork *, SubNetworkComparator>();
            REQUIRE(tree->getRoot() == nullptr);
            REQUIRE(tree->search(SubNetworkFactory::newSubNetwork(IPFactory::newIP("192.0.2.235"), 31)) == nullptr);

            SECTION("Insertion") {
                tree->insert(subnet1);
                REQUIRE(tree->getRoot() != nullptr);
                tree->insert(subnet2);
                REQUIRE(tree->search(subnet2) != nullptr);
                std::string path = "0";
                tree->insert(subnet3, path, ' ', 0);
                REQUIRE(tree->search(subnet3) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(subnet4, pathVector, 1);
                REQUIRE(tree->search(subnet4) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(subnet1);
                tree->insert(subnet2);
                std::string path = "0";
                tree->insert(subnet3, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(subnet4, pathVector, 1);

                tree->deleteNode(subnet4);
                REQUIRE(tree->search(subnet4) == nullptr);
                tree->deleteNode(subnet3);
                REQUIRE(tree->search(subnet3) == nullptr);
                tree->deleteNode(subnet2);
                REQUIRE(tree->search(subnet2) == nullptr);
                tree->deleteNode(subnet1);
                REQUIRE(tree->search(subnet1) == nullptr);
            }
        }
        SECTION("Tree with root") {
            auto tree = new MultiTree<SubNetwork *, SubNetworkComparator>(subnet1);
            SECTION("Insertion") {
                REQUIRE(tree->getRoot() != nullptr);
                tree->insert(subnet2);
                REQUIRE(tree->search(subnet2) != nullptr);
                std::string path = "0";
                tree->insert(subnet3, path, ' ', 0);
                REQUIRE(tree->search(subnet3) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(subnet4, pathVector, 1);
                REQUIRE(tree->search(subnet4) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(subnet2);
                std::string path = "0";
                tree->insert(subnet3, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(subnet4, pathVector, 1);

                tree->deleteNode(subnet4);
                REQUIRE(tree->search(subnet4) == nullptr);
                tree->deleteNode(subnet3);
                REQUIRE(tree->search(subnet3) == nullptr);
                tree->deleteNode(subnet2);
                REQUIRE(tree->search(subnet2) == nullptr);
                tree->deleteNode(subnet1);
                REQUIRE(tree->search(subnet1) == nullptr);
            }
        }
    }
}

TEST_CASE("BinaryTree", "[BinaryTree]") {
    SECTION("int") {

        SECTION("Empty tree") {
            auto tree = new BinTree<int, std::less<>>();
            REQUIRE(tree->getRoot() == nullptr);
            REQUIRE(tree->search(10) == nullptr);

            SECTION("Insertion") {
                tree->insert(3);
                REQUIRE(tree->getRoot() != nullptr);
                REQUIRE(tree->getRoot()->getKey() == 3);
                tree->insert(5, tree->getRoot(), 0);
                REQUIRE(tree->search(5) != nullptr);
                REQUIRE(tree->getRoot()->getChildren()[0]->getKey() == 5);
                std::string path = "0";
                tree->insert(10, path, ' ', 0);
                REQUIRE(tree->search(10) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(7, pathVector, 1);
                REQUIRE(tree->search(7) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(3);
                tree->insert(5);
                std::string path = "0";
                tree->insert(10, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(7, pathVector, 1);

                tree->deleteNode(7);
                REQUIRE(tree->search(7) == nullptr);
                tree->deleteNode(10);
                REQUIRE(tree->search(10) == nullptr);
                tree->deleteNode(5);
                REQUIRE(tree->search(5) == nullptr);
                tree->deleteNode(3);
                REQUIRE(tree->search(3) == nullptr);
            }
        }
        SECTION("Tree with root") {
            auto tree = new BinTree<int, std::less<>>(3);
            SECTION("Insertion") {
                REQUIRE(tree->getRoot() != nullptr);
                REQUIRE(tree->getRoot()->getKey() == 3);
                tree->insert(5, tree->getRoot(), 0);
                REQUIRE(tree->search(5) != nullptr);
                REQUIRE(tree->getRoot()->getChildren()[0]->getKey() == 5);
                std::string path = "0";
                tree->insert(10, path, ' ', 0);
                REQUIRE(tree->search(10) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(7, pathVector, 1);
                REQUIRE(tree->search(7) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(5);
                std::string path = "0";
                tree->insert(10, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(7, pathVector, 1);

                tree->deleteNode(7);
                REQUIRE(tree->search(7) == nullptr);
                tree->deleteNode(10);
                REQUIRE(tree->search(10) == nullptr);
                tree->deleteNode(5);
                REQUIRE(tree->search(5) == nullptr);
                tree->deleteNode(3);
                REQUIRE(tree->search(3) == nullptr);
            }
        }

    }
    SECTION("ip") {
        auto ip1 = IPFactory::newIP("192.0.2.235");
        auto ip2 = IPFactory::newIP("192.0.2.236");
        auto ip3 = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
        auto ip4 = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:ffff:07a0:765d");

        SECTION("Empty tree") {
            auto tree = new BinTree<IP *, IPComparator>();
            REQUIRE(tree->getRoot() == nullptr);
            REQUIRE(tree->search(IPFactory::newIP("192.0.2.235")) == nullptr);

            SECTION("Insertion") {
                tree->insert(ip1);
                REQUIRE(tree->getRoot() != nullptr);
                tree->insert(ip2, tree->getRoot(), 0);
                REQUIRE(tree->search(ip2) != nullptr);
                std::string path = "0";
                tree->insert(ip3, path, ' ', 0);
                REQUIRE(tree->search(ip3) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(ip4, pathVector, 1);
                REQUIRE(tree->search(ip4) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(ip1);
                tree->insert(ip2);
                std::string path = "0";
                tree->insert(ip3, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(ip4, pathVector, 1);

                tree->deleteNode(ip4);
                REQUIRE(tree->search(ip4) == nullptr);
                tree->deleteNode(ip3);
                REQUIRE(tree->search(ip3) == nullptr);
                tree->deleteNode(ip2);
                REQUIRE(tree->search(ip2) == nullptr);
                tree->deleteNode(ip1);
                REQUIRE(tree->search(ip1) == nullptr);
            }
        }
        SECTION("Tree with root") {
            auto tree = new BinTree<IP *, IPComparator>(ip1);
            SECTION("Insertion") {
                REQUIRE(tree->getRoot() != nullptr);
                tree->insert(ip2, tree->getRoot(), 0);
                REQUIRE(tree->search(ip2) != nullptr);
                std::string path = "0";
                tree->insert(ip3, path, ' ', 0);
                REQUIRE(tree->search(ip3) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(ip4, pathVector, 1);
                REQUIRE(tree->search(ip4) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(ip2);
                std::string path = "0";
                tree->insert(ip3, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(ip4, pathVector, 1);

                tree->deleteNode(ip4);
                REQUIRE(tree->search(ip4) == nullptr);
                tree->deleteNode(ip3);
                REQUIRE(tree->search(ip3) == nullptr);
                tree->deleteNode(ip2);
                REQUIRE(tree->search(ip2) == nullptr);
                tree->deleteNode(ip1);
                REQUIRE(tree->search(ip1) == nullptr);
            }
        }
    }

    SECTION("subnet") {
        auto subnet1 = SubNetworkFactory::newSubNetwork(IPFactory::newIP("192.0.2.235"), 31);
        auto subnet2 = SubNetworkFactory::newSubNetwork(IPFactory::newIP("192.0.2.236"), 27);
        auto subnet3 = SubNetworkFactory::newSubNetwork(IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d"),
                                                        127);
        auto subnet4 = SubNetworkFactory::newSubNetwork(IPFactory::newIP("2001:0db8:11a3:09d7:1f34:ffff:07a0:765d"),
                                                        120);


        SECTION("Empty tree") {
            auto tree = new MultiTree<SubNetwork *, SubNetworkComparator>();
            REQUIRE(tree->getRoot() == nullptr);
            REQUIRE(tree->search(SubNetworkFactory::newSubNetwork(IPFactory::newIP("192.0.2.235"), 31)) == nullptr);

            SECTION("Insertion") {
                tree->insert(subnet1);
                REQUIRE(tree->getRoot() != nullptr);
                tree->insert(subnet2,tree->getRoot(),0);
                REQUIRE(tree->search(subnet2) != nullptr);
                std::string path = "0";
                tree->insert(subnet3, path, ' ', 0);
                REQUIRE(tree->search(subnet3) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(subnet4, pathVector, 1);
                REQUIRE(tree->search(subnet4) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(subnet1);
                tree->insert(subnet2,tree->getRoot(),0);
                std::string path = "0";
                tree->insert(subnet3, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(subnet4, pathVector, 1);

                tree->deleteNode(subnet4);
                REQUIRE(tree->search(subnet4) == nullptr);
                tree->deleteNode(subnet3);
                REQUIRE(tree->search(subnet3) == nullptr);
                tree->deleteNode(subnet2);
                REQUIRE(tree->search(subnet2) == nullptr);
                tree->deleteNode(subnet1);
                REQUIRE(tree->search(subnet1) == nullptr);
            }
        }
        SECTION("Tree with root") {
            auto tree = new MultiTree<SubNetwork *, SubNetworkComparator>(subnet1);
            SECTION("Insertion") {
                REQUIRE(tree->getRoot() != nullptr);
                tree->insert(subnet2,tree->getRoot(),0);
                REQUIRE(tree->search(subnet2) != nullptr);
                std::string path = "0";
                tree->insert(subnet3, path, ' ', 0);
                REQUIRE(tree->search(subnet3) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(subnet4, pathVector, 1);
                REQUIRE(tree->search(subnet4) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(subnet2,tree->getRoot(),0);
                std::string path = "0";
                tree->insert(subnet3, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(subnet4, pathVector, 1);

                tree->deleteNode(subnet4);
                REQUIRE(tree->search(subnet4) == nullptr);
                tree->deleteNode(subnet3);
                REQUIRE(tree->search(subnet3) == nullptr);
                tree->deleteNode(subnet2);
                REQUIRE(tree->search(subnet2) == nullptr);
                tree->deleteNode(subnet1);
                REQUIRE(tree->search(subnet1) == nullptr);
            }
        }
    }
}

TEST_CASE("BSTree", "[BSTree]") {
    SECTION("Empty tree") {
        auto tree = new MultiTree<int, std::less<>>();
        REQUIRE(tree->getRoot() == nullptr);
        REQUIRE(tree->search(10) == nullptr);

        SECTION("Insertion") {
            tree->insert(3);
            REQUIRE(tree->getRoot() != nullptr);
            REQUIRE(tree->getRoot()->getKey() == 3);
            tree->insert(5);
            REQUIRE(tree->search(5) != nullptr);
            REQUIRE(tree->getRoot()->getChildren()[0]->getKey() == 5);
            std::string path = "0";
            tree->insert(10, path, ' ', 0);
            REQUIRE(tree->search(10) != nullptr);
            std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
            tree->insert(7, pathVector, 1);
            REQUIRE(tree->search(7) != nullptr);
        }

        SECTION("Deletion") {
            tree->insert(3);
            tree->insert(5);
            std::string path = "0";
            tree->insert(10, path, ' ', 0);
            std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
            tree->insert(7, pathVector, 1);

            tree->deleteNode(7);
            REQUIRE(tree->search(7) == nullptr);
            tree->deleteNode(10);
            REQUIRE(tree->search(10) == nullptr);
            tree->deleteNode(5);
            REQUIRE(tree->search(5) == nullptr);
            tree->deleteNode(3);
            REQUIRE(tree->search(3) == nullptr);
        }

        SECTION("Tree with root") {
            auto tree = new MultiTree<int, std::less<>>(3);
            SECTION("Insertion") {
                REQUIRE(tree->getRoot() != nullptr);
                REQUIRE(tree->getRoot()->getKey() == 3);
                tree->insert(5);
                REQUIRE(tree->search(5) != nullptr);
                REQUIRE(tree->getRoot()->getChildren()[0]->getKey() == 5);
                std::string path = "0";
                tree->insert(10, path, ' ', 0);
                REQUIRE(tree->search(10) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(7, pathVector, 1);
                REQUIRE(tree->search(7) != nullptr);
            }
            SECTION("Deletion") {
                tree->insert(5);
                std::string path = "0";
                tree->insert(10, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(7, pathVector, 1);

                tree->deleteNode(7);
                REQUIRE(tree->search(7) == nullptr);
                tree->deleteNode(10);
                REQUIRE(tree->search(10) == nullptr);
                tree->deleteNode(5);
                REQUIRE(tree->search(5) == nullptr);
                tree->deleteNode(3);
                REQUIRE(tree->search(3) == nullptr);
            }
        }
    }
    SECTION("ip") {
        auto ip1 = IPFactory::newIP("192.0.2.235");
        auto ip2 = IPFactory::newIP("192.0.2.236");
        auto ip3 = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d");
        auto ip4 = IPFactory::newIP("2001:0db8:11a3:09d7:1f34:ffff:07a0:765d");

        SECTION("Empty tree") {
            auto tree = new BSTree<IP *, IPComparator>();
            REQUIRE(tree->getRoot() == nullptr);
            REQUIRE(tree->search(IPFactory::newIP("192.0.2.235")) == nullptr);

            SECTION("Insertion") {
                tree->insert(ip1);
                REQUIRE(tree->getRoot() != nullptr);
                tree->insert(ip2);
                REQUIRE(tree->search(ip2) != nullptr);
                std::string path = "0";
                tree->insert(ip3, path, ' ', 0);
                REQUIRE(tree->search(ip3) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(ip4, pathVector, 1);
                REQUIRE(tree->search(ip4) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(ip1);
                tree->insert(ip2);
                std::string path = "0";
                tree->insert(ip3, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(ip4, pathVector, 1);

                tree->deleteNode(ip4);
                REQUIRE(tree->search(ip4) == nullptr);
                tree->deleteNode(ip3);
                REQUIRE(tree->search(ip3) == nullptr);
                tree->deleteNode(ip2);
                REQUIRE(tree->search(ip2) == nullptr);
                tree->deleteNode(ip1);
                REQUIRE(tree->search(ip1) == nullptr);
            }
        }
        SECTION("Tree with root") {
            auto tree = new BSTree<IP *, IPComparator>(ip1);
            SECTION("Insertion") {
                REQUIRE(tree->getRoot() != nullptr);
                tree->insert(ip2);
                REQUIRE(tree->search(ip2) != nullptr);
                std::string path = "0";
                tree->insert(ip3, path, ' ', 0);
                REQUIRE(tree->search(ip3) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(ip4, pathVector, 1);
                REQUIRE(tree->search(ip4) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(ip2);
                std::string path = "0";
                tree->insert(ip3, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(ip4, pathVector, 1);

                tree->deleteNode(ip4);
                REQUIRE(tree->search(ip4) == nullptr);
                tree->deleteNode(ip3);
                REQUIRE(tree->search(ip3) == nullptr);
                tree->deleteNode(ip2);
                REQUIRE(tree->search(ip2) == nullptr);
                tree->deleteNode(ip1);
                REQUIRE(tree->search(ip1) == nullptr);
            }
        }
    }

    SECTION("subnet") {
        auto subnet1 = SubNetworkFactory::newSubNetwork(IPFactory::newIP("192.0.2.235"), 31);
        auto subnet2 = SubNetworkFactory::newSubNetwork(IPFactory::newIP("192.0.2.236"), 27);
        auto subnet3 = SubNetworkFactory::newSubNetwork(IPFactory::newIP("2001:0db8:11a3:09d7:1f34:8a2e:07a0:765d"),
                                                        127);
        auto subnet4 = SubNetworkFactory::newSubNetwork(IPFactory::newIP("2001:0db8:11a3:09d7:1f34:ffff:07a0:765d"),
                                                        120);


        SECTION("Empty tree") {
            auto tree = new MultiTree<SubNetwork *, SubNetworkComparator>();
            REQUIRE(tree->getRoot() == nullptr);
            REQUIRE(tree->search(SubNetworkFactory::newSubNetwork(IPFactory::newIP("192.0.2.235"), 31)) == nullptr);

            SECTION("Insertion") {
                tree->insert(subnet1);
                REQUIRE(tree->getRoot() != nullptr);
                tree->insert(subnet2);
                REQUIRE(tree->search(subnet2) != nullptr);
                std::string path = "0";
                tree->insert(subnet3, path, ' ', 0);
                REQUIRE(tree->search(subnet3) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(subnet4, pathVector, 1);
                REQUIRE(tree->search(subnet4) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(subnet1);
                tree->insert(subnet2);
                std::string path = "0";
                tree->insert(subnet3, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(subnet4, pathVector, 1);

                tree->deleteNode(subnet4);
                REQUIRE(tree->search(subnet4) == nullptr);
                tree->deleteNode(subnet3);
                REQUIRE(tree->search(subnet3) == nullptr);
                tree->deleteNode(subnet2);
                REQUIRE(tree->search(subnet2) == nullptr);
                tree->deleteNode(subnet1);
                REQUIRE(tree->search(subnet1) == nullptr);
            }
        }
        SECTION("Tree with root") {
            auto tree = new MultiTree<SubNetwork *, SubNetworkComparator>(subnet1);
            SECTION("Insertion") {
                REQUIRE(tree->getRoot() != nullptr);
                tree->insert(subnet2);
                REQUIRE(tree->search(subnet2) != nullptr);
                std::string path = "0";
                tree->insert(subnet3, path, ' ', 0);
                REQUIRE(tree->search(subnet3) != nullptr);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(subnet4, pathVector, 1);
                REQUIRE(tree->search(subnet4) != nullptr);
            }

            SECTION("Deletion") {
                tree->insert(subnet2);
                std::string path = "0";
                tree->insert(subnet3, path, ' ', 0);
                std::vector<unsigned> pathVector = std::vector<unsigned>({0, 0});
                tree->insert(subnet4, pathVector, 1);

                tree->deleteNode(subnet4);
                REQUIRE(tree->search(subnet4) == nullptr);
                tree->deleteNode(subnet3);
                REQUIRE(tree->search(subnet3) == nullptr);
                tree->deleteNode(subnet2);
                REQUIRE(tree->search(subnet2) == nullptr);
                tree->deleteNode(subnet1);
                REQUIRE(tree->search(subnet1) == nullptr);
            }
        }
    }
}

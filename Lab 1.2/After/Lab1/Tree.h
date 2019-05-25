//
// Created by Taya on 22.04.2019.
//

#ifndef LAB1_TREE_H
#define LAB1_TREE_H

#include "TreeNode.h"

class Tree {
public:
    virtual ~Tree() = default;
};

class MultiTree : public Tree {
public:
    ~MultiTree() override = default;
};

class BinTree : public Tree {
public:
    ~BinTree() override = default;

};

class BSTree : public BinTree {
public:
    ~BSTree() override = default;

};


#endif //LAB1_TREE_H

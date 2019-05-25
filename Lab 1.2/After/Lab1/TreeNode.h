//
// Created by Taya on 25.05.2019.
//

#ifndef LAB1_TREENODE_H
#define LAB1_TREENODE_H

template<typename Key>
class Node {
public:
    virtual ~Node() = default;

    virtual Key getKey() const = 0;

protected:
    virtual Key setKey() = 0;
};


#endif //LAB1_TREENODE_H

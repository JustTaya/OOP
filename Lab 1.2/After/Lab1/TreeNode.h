//
// Created by Taya on 25.05.2019.
//

#ifndef LAB1_TREENODE_H
#define LAB1_TREENODE_H

#include <vector>

template<typename Key>
class AbstractNode {
public:
    AbstractNode(const Key &key, AbstractNode<Key> *parent) : keys(std::vector<Key>(1, key)), parent(parent) {};

    virtual ~AbstractNode() = default;

    virtual Key getKey() const = 0;

    virtual std::vector<AbstractNode<Key> *> getChildren() const;

    virtual AbstractNode *getParent() const;

protected:
    std::vector<Key> keys;
    std::vector<AbstractNode<Key> *> children = std::vector<AbstractNode<Key> *>(0);
    AbstractNode<Key> *parent;

    virtual void addKey(const Key &key);

    virtual void addChild(AbstractNode<Key> *child);

    virtual void setParent(AbstractNode<Key> *node);

};

template<typename Key>
std::vector<AbstractNode<Key> *> AbstractNode<Key>::getChildren() const {
    return this->children;
}

template<typename Key>
void AbstractNode<Key>::addKey(const Key &key) {
    this->keys.push_back(key);
}

template<typename Key>
AbstractNode<Key> *AbstractNode<Key>::getParent() const {
    return this->parent;
}

template<typename Key>
void AbstractNode<Key>::addChild(AbstractNode<Key> *child) {
    AbstractNode<Key>::children.push_back(child);
}

template<typename Key>
void AbstractNode<Key>::setParent(AbstractNode<Key> *node) {
    this->parent = node;
}

template<typename Key>
class MultiNode : public AbstractNode<Key> {
public:
    MultiNode(const Key &key, AbstractNode<Key> *parent) : AbstractNode<Key>(key, parent) {};

    ~MultiNode() override = default;

    Key getKey() const override;
};

template<typename Key>
Key MultiNode<Key>::getKey() const {
    return AbstractNode<Key>::keys[0];
}

template<typename Key>
class BinaryNode : public AbstractNode<Key> {
public:
    BinaryNode(Key key, BinaryNode<Key> *parent) : AbstractNode<Key>(key, parent) {
        AbstractNode<Key>::children.resize(2, nullptr);
    };

    ~BinaryNode() override = default;

    Key getKey() const override;

    AbstractNode<Key> *getLeft() const;

    AbstractNode<Key> *getRight() const;

};

template<typename Key>
Key BinaryNode<Key>::getKey() const {
    return AbstractNode<Key>::keys[0];
}

template<typename Key>
AbstractNode<Key> *BinaryNode<Key>::getLeft() const {
    return AbstractNode<Key>::children[0];
}

template<typename Key>
AbstractNode<Key> *BinaryNode<Key>::getRight() const {
    return AbstractNode<Key>::children[1];
}

#endif //LAB1_TREENODE_H

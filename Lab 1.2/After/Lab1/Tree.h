//
// Created by Taya on 22.04.2019.
//

#ifndef LAB1_TREE_H
#define LAB1_TREE_H

#include "TreeNode.h"

template<typename Key, typename Cmp>
class Tree {
public:
    virtual ~Tree() = default;

    virtual AbstractNode<Key> *getRoot() const = 0;

    virtual bool insert(const Key &key, std::string &path, const char delimiter, AbstractNode<Key> *node = nullptr) = 0;

    virtual bool insert(const Key &key, const std::vector<unsigned> &path, AbstractNode<Key> *node = nullptr) = 0;

    virtual bool insert(const Key &key, AbstractNode<Key> *node = nullptr) = 0;

    virtual AbstractNode<Key> *search(const Key &key) = 0;

    virtual bool deleteNode(const Key &key) = 0;
};

template<typename Key, typename Cmp>
class MultiTree : public Tree<Key, Cmp> {
public:
    MultiTree() = default;

    explicit MultiTree(Key key) : root(new MultiNode<Key>(key)) {};

    ~MultiTree() override = default;

    AbstractNode<Key> *getRoot() const override;

    bool insert(const Key &key, std::string &path, const char delimiter, AbstractNode<Key> *node = nullptr) override;

    bool insert(const Key &key, const std::vector<unsigned> &path, AbstractNode<Key> *node = nullptr) override;

    bool insert(const Key &key, AbstractNode<Key> *node = nullptr) override;

    AbstractNode<Key> *search(const Key &key) override;

    bool deleteNode(const Key &key) override;

private:
    MultiNode<Key> *root = nullptr;

};

template<typename Key, typename Cmp>
AbstractNode<Key> *MultiTree<Key, Cmp>::getRoot() const {
    return this->root;
}

template<typename Key, typename Cmp>
class BinTree : public Tree<Key, Cmp> {
public:
    BinTree() = default;

    explicit BinTree(Key key) : root(new BinaryNode<Key>(key)) {};

    ~BinTree() override = default;

    AbstractNode<Key> *getRoot() const override;

    bool insert(const Key &key, std::string &path, const char delimiter, AbstractNode<Key> *node = nullptr) override;

    bool insert(const Key &key, const std::vector<unsigned> &path, AbstractNode<Key> *node = nullptr) override;

    bool insert(const Key &key, AbstractNode<Key> *node = nullptr) override;

    AbstractNode<Key> *search(const Key &key) override;

    bool deleteNode(const Key &key) override;

protected:
    BinaryNode<Key> *root = nullptr;
};

template<typename Key, typename Cmp>
AbstractNode<Key> *BinTree<Key, Cmp>::getRoot() const {
    return this->root;
}

template<typename Key, typename Cmp>
class BSTree : public BinTree<Key, Cmp> {
public:
    BSTree() : BinTree<Key,Cmp>() {};

    explicit BSTree(Key key) : BinTree<Key,Cmp>(key) {};

    ~BSTree() override = default;

    bool insert(const Key &key, std::string &path, const char delimiter, AbstractNode<Key> *node = nullptr) override;

    bool insert(const Key &key, const std::vector<unsigned> &path, AbstractNode<Key> *node = nullptr) override;

    bool insert(const Key &key, AbstractNode<Key> *node = nullptr) override;

    AbstractNode<Key> *search(const Key &key) override;

    bool deleteNode(const Key &key) override;

};

template<typename Key, typename Cmp>
AbstractNode<Key> *BSTree<Key, Cmp>::search(const Key &key) {
    auto current = getRoot();
    while (current != nullptr) {
        if (current->getKey() > key) {
            current = current->getLeft();
        } else if (Cmp.cmp(current->getKey() < key)) {
            current = current->getRight();
        } else {
            return current;
        }
    }
    return nullptr;
}


#endif //LAB1_TREE_H

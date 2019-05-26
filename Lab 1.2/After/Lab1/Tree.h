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
    BSTree() : BinTree<Key, Cmp>() {};

    explicit BSTree(Key key) : BinTree<Key, Cmp>(key) {};

    ~BSTree() override = default;

    bool insert(const Key &key, std::string &path, const char delimiter, AbstractNode<Key> *node = nullptr) override;

    bool insert(const Key &key, const std::vector<unsigned> &path, AbstractNode<Key> *node = nullptr) override;

    bool insert(const Key &key, AbstractNode<Key> *node = nullptr) override;

    AbstractNode<Key> *search(const Key &key) override;

    bool deleteNode(const Key &key) override;

private:

    BinaryNode<Key> *_deleteNode(BinaryNode<Key> *node, const Key &key);

    BinaryNode<Key> *_findMin(BinaryNode<Key> *node);

    BinaryNode<Key> *_deleteMin(BinaryNode<Key> *node);

    bool _insertNode(BinaryNode<Key> *node);

};

template<typename Key, typename Cmp>
AbstractNode<Key> *BSTree<Key, Cmp>::search(const Key &key) {
    Cmp cmp;
    auto current = this->getRoot();
    while (current != nullptr) {
        if (cmp(key, current->getKey())) {
            current = current->getLeft();
        } else if (cmp(current->getKey(), key)) {
            current = current->getRight();
        } else {
            return current;
        }
    }
    return nullptr;
}

template<typename Key, typename Cmp>
bool BSTree<Key, Cmp>::deleteNode(const Key &key) {
    this->root = _deleteNode(this->root, key);
}

template<typename Key, typename Cmp>
BinaryNode<Key> *BSTree<Key, Cmp>::_deleteNode(BinaryNode<Key> *node, const Key &key) {
    if (node == nullptr) {
        return nullptr;
    }
    Cmp cmp;
    if (cmp(key, node->getKey())) {
        node->setLeft(_deleteNode(node->getLeft(), key));
    } else if (cmp(node->getKey(), key)) {
        node->setRight(_deleteNode(node->getRight(), key));
    } else {
        auto left = node->getLeft();
        auto right = node->getRight();
        delete node;
        if (right == nullptr) {
            return left;
        }
        auto min = _finMin(right);
        min.right = _deleteMin(right);
        min.left = left;
        return min;
    }
}

template<typename Key, typename Cmp>
BinaryNode<Key> *BSTree<Key, Cmp>::_findMin(BinaryNode<Key> *node) {
    auto current = node;
    while (current->getLeft() != nullptr) {
        current = current->getLeft();
    }
    return current;
}

template<typename Key, typename Cmp>
BinaryNode<Key> *BSTree<Key, Cmp>::_deleteMin(BinaryNode<Key> *node) {
    if (node->getLeft() == nullptr) {
        return node->getRight();
    }
    node->setLeft(_deleteMin(node->getLeft()));
    return node;
}

template<typename Key, typename Cmp>
bool BSTree<Key, Cmp>::insert(const Key &key, std::string &path, const char delimiter, AbstractNode<Key> *node) {
    return false;
}

template<typename Key, typename Cmp>
bool BSTree<Key, Cmp>::insert(const Key &key, const std::vector<unsigned> &path, AbstractNode<Key> *node) {
    return false;
}

template<typename Key, typename Cmp>
bool BSTree<Key, Cmp>::insert(const Key &key, AbstractNode<Key> *node) {
    auto newNode = new BinaryNode<Key>(key, nullptr);
    _insertNode(node);
}

template<typename Key, typename Cmp>
bool BSTree<Key, Cmp>::_insertNode(BinaryNode<Key> *node) {
    Cmp cmp;
    if (this->root == nullptr) {
        this->root = node;
    } else {
        auto current = this->root;
        while (current != nullptr) {
            if (cmp(node->getKey(), current->getKey())) {
                if (current->getLeft() == nullptr) {
                    current->left = node;
                    node->setParent(current);
                    break;
                } else {
                    current = current->getLeft();
                }
            }
            else{
                if(current->getRight()==nullptr){
                    current->setRight(node);
                    node->setParent(current);
                    break;
                }
                else{
                    current=current->getRight();
                }
            }
        }
    }
}


#endif //LAB1_TREE_H

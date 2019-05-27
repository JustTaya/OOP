//
// Created by Taya on 22.04.2019.
//

#ifndef LAB1_TREE_H
#define LAB1_TREE_H

#include <vector>
#include <sstream>
#include <stack>

template<typename Key>
class AbstractNode {
public:
    AbstractNode(const Key &key, AbstractNode<Key> *parent = nullptr) : keys(std::vector<Key>(1, key)),
                                                                        parent(parent) {};

    virtual ~AbstractNode() = default;

    virtual Key getKey() const = 0;

    virtual std::vector<AbstractNode<Key> *> getChildren() const;

    virtual AbstractNode *getParent() const;

protected:
    std::vector<Key> keys;
    std::vector<AbstractNode<Key> *> children = std::vector<AbstractNode<Key> *>(0);
    AbstractNode<Key> *parent;

    virtual void addKey(const Key &key);

    virtual void addChild(AbstractNode<Key> *child, int pos = -1);

    virtual void setParent(AbstractNode<Key> *node);

    template<typename> friend
    class MultiNode;

    template<typename, typename> friend
    class MultiTree;

    template<typename, typename> friend
    class BinaryTree;

    template<typename, typename> friend
    class BSTree;

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
void AbstractNode<Key>::addChild(AbstractNode<Key> *child, int pos) {
    if (pos < 0) {
        AbstractNode<Key>::children.push_back(child);
    } else {
        if (children.size() <= pos) {
            children.resize(pos + 1);
        }
        children[pos] = child;
    }
}

template<typename Key>
void AbstractNode<Key>::setParent(AbstractNode<Key> *node) {
    this->parent = node;
}

template<typename Key>
class MultiNode : public AbstractNode<Key> {
public:
    MultiNode(const Key &key, AbstractNode<Key> *parent = nullptr) : AbstractNode<Key>(key, parent) {};

    ~MultiNode() override;

    Key getKey() const override;

private:
    template<typename, typename> friend
    class MultiTree;

    void setKey(const Key &key);
};

template<typename Key>
Key MultiNode<Key>::getKey() const {
    return AbstractNode<Key>::keys[0];
}

template<typename Key>
class BinaryNode : public AbstractNode<Key> {
public:
    BinaryNode(Key key, BinaryNode<Key> *parent = nullptr) : AbstractNode<Key>(key, parent) {
        AbstractNode<Key>::children.resize(2, nullptr);
    };

    ~BinaryNode() override = default;

    Key getKey() const override;

    AbstractNode<Key> *getLeft() const;

    AbstractNode<Key> *getRight() const;

private:
    template<typename, typename> friend
    class BinaryTree;

    template<typename, typename> friend
    class BSTree;

    void setKey(const Key &key);

    void setLeft(BinaryNode<Key> *node);

    void setRight(BinaryNode<Key> *node);

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

template<typename Key, typename Cmp>
class Tree {
public:
    virtual ~Tree() = default;

    virtual AbstractNode<Key> *getRoot() const = 0;

    virtual void insert(const Key &key, std::string &path, const char delimiter, int pos = -1,
                        AbstractNode<Key> *node = nullptr) = 0;

    virtual void
    insert(const Key &key, const std::vector<unsigned> &path, int pos = -1, AbstractNode<Key> *node = nullptr) = 0;

    virtual void insert(const Key &key, AbstractNode<Key> *node = nullptr, int pos = -1) = 0;

    virtual AbstractNode<Key> *search(const Key &key) = 0;

    virtual void deleteNode(const Key &key) = 0;

protected:
    std::vector<unsigned> getPathVector(std::string &path, const char delimiter);
};

template<typename Key, typename Cmp>
std::vector<unsigned> Tree<Key, Cmp>::getPathVector(std::string &path, const char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(path);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    std::vector<unsigned> pathVector;
    unsigned tmp;
    pathVector.reserve(tokens.size());
    for (auto i:tokens) {
        std::istringstream iss(i);
        iss >> tmp;
        pathVector.push_back(tmp);
    }
    return pathVector;
}

template<typename Key, typename Cmp>
class MultiTree : public Tree<Key, Cmp> {
public:
    MultiTree() = default;

    explicit MultiTree(Key key) : root(new MultiNode<Key>(key)) {};

    ~MultiTree() override = default;

    AbstractNode<Key> *getRoot() const override;

    void insert(const Key &key, std::string &path, const char delimiter, int pos = -1,
                AbstractNode<Key> *node = nullptr) override;

    void
    insert(const Key &key, const std::vector<unsigned> &path, int pos = -1, AbstractNode<Key> *node = nullptr) override;

    void insert(const Key &key, AbstractNode<Key> *node = nullptr, int pos = -1) override;

    AbstractNode<Key> *search(const Key &key) override;

    void deleteNode(const Key &key) override;

private:
    MultiNode<Key> *root = nullptr;

};

template<typename Key>
void MultiNode<Key>::setKey(const Key &key) {
    this->keys[0] = key;
}

template<typename Key>
MultiNode<Key>::~MultiNode() {
    if (this->parent != nullptr) {
        for (auto i:this->parent->children) {
            if (i == this) {
                i = nullptr;
            }
        }
    }
}

template<typename Key, typename Cmp>
AbstractNode<Key> *MultiTree<Key, Cmp>::getRoot() const {
    return this->root;
}

template<typename Key, typename Cmp>
void
MultiTree<Key, Cmp>::insert(const Key &key, std::string &path, const char delimiter, int pos, AbstractNode<Key> *node) {
    std::vector<unsigned> pathVector = this->getPathVector(path, delimiter);
    insert(key, pathVector, pos, this->root);
}

template<typename Key, typename Cmp>
void MultiTree<Key, Cmp>::insert(const Key &key, const std::vector<unsigned> &path, int pos, AbstractNode<Key> *node) {
    auto current = node;
    for (auto i:path) {
        if (current == nullptr) {
            return;
        }
        auto children = node->getChildren();
        if (children.size() <= i) {
            return;
        }
        current = children[i];
    }
    insert(key, current, pos);
}

template<typename Key, typename Cmp>
void MultiTree<Key, Cmp>::insert(const Key &key, AbstractNode<Key> *node, int pos) {
    if (node == nullptr) {
        if (this->root == nullptr)
            return;
        node->addChild(new MultiNode<Key>(key, this->root), pos);
    }
    node->addChild(new MultiNode<Key>(key, node), pos);
}

template<typename Key, typename Cmp>
AbstractNode<Key> *MultiTree<Key, Cmp>::search(const Key &key) {
    if (this->root == nullptr || this->root->getKey() == key)
        return this->root;
    AbstractNode<Key> *tmp = nullptr;
    std::stack<AbstractNode<Key> *> stack;
    stack.push(this->root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->getKey() == key)
            return tmp;
        auto nodes = tmp->getChildren();
        if (!nodes.empty()) {
            for (auto i:nodes) {
                stack.push(i);
            }
        }
    }
    return nullptr;
}

template<typename Key, typename Cmp>
void MultiTree<Key, Cmp>::deleteNode(const Key &key) {
    auto node = search(key);
    if (node == this->root && node->getChildren().empty()) {
        delete this->root;
        this->root = nullptr;
        return;
    }
    for (auto i:node->getChildren()) {
        if (i != nullptr)
            return;
    }
    delete node;
}

template<typename Key, typename Cmp>
class BinTree : public Tree<Key, Cmp> {
public:
    BinTree() = default;

    explicit BinTree(Key key) : root(new BinaryNode<Key>(key)) {};

    ~BinTree() override = default;

    AbstractNode<Key> *getRoot() const override;

    void insert(const Key &key, std::string &path, const char delimiter, int pos = -1,
                AbstractNode<Key> *node = nullptr) override;

    void
    insert(const Key &key, const std::vector<unsigned> &path, int pos = -1,
           AbstractNode<Key> *node = nullptr) override;

    void insert(const Key &key, AbstractNode<Key> *node = nullptr, int pos = -1) override;

    AbstractNode<Key> *search(const Key &key) override;

    void deleteNode(const Key &key) override;

protected:
    BinaryNode<Key> *root = nullptr;

private:
    template<typename, typename> friend
    class BinTree;
};

template<typename Key, typename Cmp>
AbstractNode<Key> *BinTree<Key, Cmp>::getRoot() const {
    return this->root;
}

template<typename Key, typename Cmp>
void
BinTree<Key, Cmp>::insert(const Key &key, std::string &path, const char delimiter, int pos,
                          AbstractNode<Key> *node) {
    std::vector<unsigned> pathVector = this->getPathVector(path, delimiter);
    insert(key, pathVector, this->root);
}

template<typename Key, typename Cmp>
void
BinTree<Key, Cmp>::insert(const Key &key, const std::vector<unsigned> &path, int pos, AbstractNode<Key> *node) {
    auto current = node;
    for (auto i:path) {
        if (current == nullptr) {
            return;
        }
        auto children = node->getChildren();
        if (children.size() <= i || i > 1) {
            return;
        }
        current = children[i];
    }
    insert(key, pos, current);
}

template<typename Key, typename Cmp>
void BinTree<Key, Cmp>::insert(const Key &key, AbstractNode<Key> *node, int pos) {
    auto children = node->getChildren();
    if (pos == -1) {
        if (children[0] == nullptr) {
            node->addChild(new BinaryNode<Key>(key, node), 0);
        } else if (children[1] == nullptr) {
            node->addChild(new BinaryNode<Key>(key, node), 1);
        } else {
            return;
        }
    }
    node->addChild(new BinaryNode<Key>(key, node), pos);
}

template<typename Key, typename Cmp>
void BinTree<Key, Cmp>::deleteNode(const Key &key) {
    auto node = search(key);
    if (node == this->_root && node->getChildren().empty()) {
        delete this->_root;
        this->_root = nullptr;
        return;
    }
    auto children = node->getChildren();
    if (children[0] == nullptr && children[1] == nullptr) {
        delete node;
    }
}

template<typename Key, typename Cmp>
AbstractNode<Key> *BinTree<Key, Cmp>::search(const Key &key) {
    if (this->root == nullptr)
        return nullptr;
    std::stack<BinaryNode<Key> *> stack;
    BinaryNode<Key> *tmp = nullptr;
    stack.push(this->_root);
    while (!stack.empty()) {
        tmp = stack.top();
        stack.pop();
        if (tmp->getKey() == key) {
            return tmp;
        } else {
            if (tmp->getLeft() != nullptr)
                stack.push(tmp->getLeft());
            if (tmp->getRight() != nullptr)
                stack.push(tmp->getRight());
        }
    }
    return nullptr;
}

template<typename Key, typename Cmp>
class BSTree : public BinTree<Key, Cmp> {
public:
    BSTree() : BinTree<Key, Cmp>() {};

    explicit BSTree(Key key) : BinTree<Key, Cmp>(key) {};

    ~BSTree() override = default;

    void insert(const Key &key, std::string &path, const char delimiter, int pos = -1,
                AbstractNode<Key> *node = nullptr) override;

    void
    insert(const Key &key, const std::vector<unsigned> &path, int pos = -1,
           AbstractNode<Key> *node = nullptr) override;

    void insert(const Key &key, int pos = -1, AbstractNode<Key> *node = nullptr) override;

    AbstractNode<Key> *search(const Key &key) override;

    void deleteNode(const Key &key) override;

private:

    BinaryNode<Key> *_deleteNode(BinaryNode<Key> *node, const Key &key);

    BinaryNode<Key> *_findMin(BinaryNode<Key> *node);

    BinaryNode<Key> *_deleteMin(BinaryNode<Key> *node);

    void _insertNode(BinaryNode<Key> *node);

};

template<typename Key>
void BinaryNode<Key>::setKey(const Key &key) {
    this->keys[0] = key;
}

template<typename Key>
void BinaryNode<Key>::setLeft(BinaryNode<Key> *node) {
    this->children[0] = node;
}

template<typename Key>
void BinaryNode<Key>::setRight(BinaryNode<Key> *node) {
    this->children[1] = node;
}

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
void BSTree<Key, Cmp>::deleteNode(const Key &key) {
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
void
BSTree<Key, Cmp>::insert(const Key &key, std::string &path, const char delimiter, int pos,
                         AbstractNode<Key> *node) {
}

template<typename Key, typename Cmp>
void BSTree<Key, Cmp>::insert(const Key &key, const std::vector<unsigned> &path, int pos, AbstractNode<Key> *node) {
}

template<typename Key, typename Cmp>
void BSTree<Key, Cmp>::insert(const Key &key, int pos, AbstractNode<Key> *node) {
    auto newNode = new BinaryNode<Key>(key, nullptr);
    _insertNode(node);
}

template<typename Key, typename Cmp>
void BSTree<Key, Cmp>::_insertNode(BinaryNode<Key> *node) {
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
            } else {
                if (current->getRight() == nullptr) {
                    current->setRight(node);
                    node->setParent(current);
                    break;
                } else {
                    current = current->getRight();
                }
            }
        }
    }
}


#endif //LAB1_TREE_H

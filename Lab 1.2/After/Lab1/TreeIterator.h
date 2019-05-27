//
// Created by Taya on 25.05.2019.
//

#ifndef LAB1_TREEITERATOR_H
#define LAB1_TREEITERATOR_H

#include "Tree.h"

template<typename Key, typename Cmp>
class TreeIterator {
public:
    TreeIterator(Tree<Key, Cmp> *tree) : tree(tree), current(tree->getRoot()) {};

    virtual ~TreeIterator() = default;

    virtual bool isEqual(TreeIterator<Key, Cmp> *other);

    virtual AbstractNode<Key> *getCurrent();

    virtual void next() = 0;

    AbstractNode<Key> *end();

protected:
    Tree<Key, Cmp> *tree;

    AbstractNode<Key> *current;
};

template<typename Key, typename Cmp>
bool TreeIterator<Key, Cmp>::isEqual(TreeIterator<Key, Cmp> *other) {
    return this->current == other->current;
}

template<typename Key, typename Cmp>
AbstractNode<Key> *TreeIterator<Key, Cmp>::getCurrent() {
    return this->current;
}

AbstractNode<Key> *TreeIterator<Key, Cmp>::end() {
    auto endIterator = new TreeIterator<Key, Cmp>(tree);
    endIterator->current = nullptr;
}

#endif //LAB1_TREEITERATOR_H

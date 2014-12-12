#ifndef _RBTREE_H_
#define _RBTREE_H_

// COLOR    getColor() = 0;
// CRBTree *getLeft() = 0;
// CRBTree *getRight() = 0;
// void     setColor(COLOR c) = 0;
// void     setLeft(CRBTree *l) = 0;
// void     setRight(CRBTree *r) = 0;
// bool     lessThan(CRBTree *lhs, CRBTree *rhs) = 0;
// bool     equalTo(CRBTree *lhs, CRBTree *rhs) = 0;

#ifndef ASSERT
#ifdef UNIT_TEST
#include "assert.h"
#define ASSERT(x) assert(x)
#else
#define ASSERT(x)
#endif
#endif

template<class T>
class TRBTree
{
protected:
    typedef typename T::Key Key;

    // T should defind its own 'operator ==' and 'operator <' at least for following two functions.
    static bool defaultEq(const Key &lhs, const Key &rhs) { return (lhs == rhs); }
    static bool defaultLess(const Key &lhs, const Key &rhs) { return (lhs < rhs); }

public:
    enum COLOR {
        RED,
        BLACK,
    };

    void  insert(T *item);

    // return value is the found item or null.
    T    *remove(const Key &k,
                 bool (*eq)(const Key &lhs, const Key &rhs) = (defaultEq),
                 bool (*less)(const Key &lhs, const Key &rhs) = (defaultLess));
    T    *removeLeastGreater(const Key &k,
                             bool (*eq)(const Key &lhs, const Key &rsh) = (defaultEq),
                             bool (*less)(const Key &lhs, const Key &rsh) = (defaultLess));
    T    *root() { return _root; }

    TRBTree();
protected:
    T *_root;

private:
    static T    *_insert(T *tree, T *item);
    static T    *_insAdj(T *tree);
    static T    *_rotateLeft(T *tree);
    static T    *_rotateRight(T *tree);
    static void  _swapColorLeft(T *tree);
    static void  _swapColorRight(T *tree);

    // return value: true to do adjustment (lack 1 black depth.)
    static bool  _remove(T **pTree, // In and out. Carry the balance-adjusted tree after return.
                         T **pItem, // Carry the removed item.
                         const Key &k,
                         bool (*eq)(const Key &lhs, const Key &rhs),
                         bool (*less)(const Key &lhs, const Key &rhs));
    static bool  _removeLeastGreater(T **pTree, // In and out. Carry the balance-adjusted tree after return.
                                     T **pItem, // Carry the removed item.
                                     const Key &k,
                                     bool (*eq)(const Key &lhs, const Key &rhs),
                                     bool (*less)(const Key &lhs, const Key &rhs));
    static bool  _rmRightMost(T **pTree, T **pItem);
    static bool  _rmAdjLeft(T **pTree);
    static bool  _rmAdjRight(T **pTree);
};

template<class T>
TRBTree<T>::TRBTree()
    : _root(0)
{
}

template<class T>
void TRBTree<T>::insert(T *item)
{
    item->setColor(RED);
    item->setLeft(0);
    item->setRight(0);

    _root = _insert(_root, item);
    _root->setColor(BLACK);
}

template<class T>
T *TRBTree<T>::_insAdj(T *tree)
{
    ASSERT(0 != tree);
    if(BLACK == tree->color()) {
        T *l = tree->left();
        T *r = tree->right();

        if(0 != l && 0 != r && RED == l->color() && RED == r->color()) {
            tree->setColor(RED);
            tree->left()->setColor(BLACK);
            tree->right()->setColor(BLACK);
            return tree;
        }

        if(0 != l && RED == l->color()) {
            T *lr = l->right();
            if(0 != lr && RED == lr->color()) {
                l = _rotateLeft(l);
            }

            T *ll = l->left();
            if(0 != ll && RED == ll->color()) {
                tree = _rotateRight(tree);
                _swapColorRight(tree);
            }
        }

        if(0 != r && RED == r->color()) {
            T *rl = r->left();
            if(0 != rl && RED == rl->color()) {
                r = _rotateRight(r);
            }

            T *rr = r->right();
            if(0 != rr && RED == rr->color()) {
                tree = _rotateLeft(tree);
                _swapColorLeft(tree);
            }
        }
    }
    return tree;
}


template<class T>
T *TRBTree<T>::_insert(T *tree, T *item)
{
    if(0 == tree) return item;

    if(item->key() < tree->key()) {
        tree->setLeft(_insert(tree->left(), item));
    } else {
        tree->setRight(_insert(tree->right(), item));
    }
    tree = _insAdj(tree);
    return tree;
}

template<class T>
T *TRBTree<T>::_rotateLeft(T *tree)
{
    T *r  = tree->right();
    ASSERT(0 != r);

    T *rl = r->left();

    r->setLeft(tree);
    tree->setRight(rl);

    return r;
}

template<class T>
T *TRBTree<T>::_rotateRight(T *tree)
{
    T *l = tree->left();
    ASSERT(0 != l);

    T *lr = l->right();

    l->setRight(tree);
    tree->setLeft(lr);

    return l;
}

template<class T>
void TRBTree<T>::_swapColorLeft(T *tree)
{
    ASSERT(0 != tree->left());
    COLOR tmp = tree->color();
    tree->setColor(tree->left()->color());
    tree->left()->setColor(tmp);
}

template<class T>
void TRBTree<T>::_swapColorRight(T *tree)
{
    ASSERT(0 != tree->right());
    COLOR tmp = tree->color();
    tree->setColor(tree->right()->color());
    tree->right()->setColor(tmp);
}

template<class T>
bool TRBTree<T>::_remove(T **pTree, // [In/out]. Carry the balance-adjusted tree after return.
                         T **pItem, // [Out   ]. Carry the removed item.
                         const Key &k,
                         bool (*eq)(const Key &lhs, const Key &rhs),
                         bool (*less)(const Key &lhs, const Key &rhs))
{
    T *&tree = (*pTree);
    T *&item = (*pItem);
    bool toAdj = false;

    if(less(k, tree->key())) {
        T *l = tree->left();
        if(0 == l) {
            item = 0; // Can not found item of key.
        } else {
            toAdj = _remove(&l, &item, k, eq, less);
            tree->setLeft(l);
            if(toAdj) toAdj = _rmAdjLeft(&tree);
        }
    } else if(eq(k, tree->key())) {
        T *l = tree->left();
        if(0 == l) {
            // If there is a right child, it must be a red leaf.
            ASSERT(0 == tree->right() || (RED == tree->right()->color() && 0 == tree->right()->left() && 0 == tree->right()->right()));
            item = tree;
            if(0 != tree->right()) tree->right()->setColor(tree->color());
            tree = tree->right();
            item->setLeft(0);
            item->setRight(0);

            if(BLACK == item->color() && 0 == tree) toAdj = true; // Remove block node without red to replace.
        } else {
            T *rMost;
            toAdj = _rmRightMost(&l, &rMost);
            rMost->setRight(tree->right());
            rMost->setLeft(l);
            rMost->setColor(tree->color());
            item = tree;
            tree = rMost;
            item->setLeft(0);
            item->setRight(0);
            if(toAdj) toAdj = _rmAdjLeft(&tree);
        }
    } else {
        T *r = tree->right();
        if(0 == r) {
        } else {
            toAdj = _remove(&r, &item, k, eq, less);
            tree->setRight(r);
            if(toAdj) toAdj = _rmAdjRight(&tree);
        }
    }
    return toAdj;
}

template<class T>
T *TRBTree<T>::remove(const typename T::Key &k,
                      bool (*eq)(const Key &lhs, const Key &rhs),
                      bool (*less)(const Key &lhs, const Key &rhs))
{
    T *item = 0;
    (void)_remove(&_root, &item, k, eq, less);

    if(0 != item) {
        item->setLeft(0);
        item->setRight(0);
    }

    if(0 != _root) _root->setColor(BLACK);

    return item;
}

template<class T>
bool TRBTree<T>::_removeLeastGreater(T **pTree, // [In/out]. Carry the balance-adjusted tree after return.
                                     T **pItem, // [Out   ]. Carry the removed item.
                                     const Key &k,
                                     bool (*eq)(const Key &lhs, const Key &rhs),
                                     bool (*less)(const Key &lhs, const Key &rhs))
{
    T *&tree = (*pTree);
    T *&item = (*pItem);
    bool toAdj = false;

    if(less(k, tree->key())) {
        T *l = tree->left();
        if(0 == l) {
            // If there is a right child, it must be a red leaf.
            ASSERT(0 == tree->right() || (RED == tree->right()->color() && 0 == tree->right()->left() && 0 == tree->right()->right()));
            item = tree;
            if(0 != tree->right()) tree->right()->setColor(tree->color());
            tree = tree->right();
            item->setLeft(0);
            item->setRight(0);

            if(BLACK == item->color() && 0 == tree) toAdj = true; // Remove block node without red to replace.
        } else {
            item = 0;

            if(!eq(k, tree->key())) {
                toAdj = _removeLeastGreater(&l, &item, k, eq, less);
                tree->setLeft(l);
                if(toAdj) toAdj = _rmAdjLeft(&tree);
            }

            if(0 == item) {
                T *rMost;
                toAdj = _rmRightMost(&l, &rMost);
                rMost->setRight(tree->right());
                rMost->setLeft(l);
                rMost->setColor(tree->color());
                item = tree;
                tree = rMost;
                item->setLeft(0);
                item->setRight(0);
                if(toAdj) toAdj = _rmAdjLeft(&tree);
            }
        }
    } else if(eq(k, tree->key())) {
        T *l = tree->left();
        if(0 == l) {
            // If there is a right child, it must be a red leaf.
            ASSERT(0 == tree->right() || (RED == tree->right()->color() && 0 == tree->right()->left() && 0 == tree->right()->right()));
            item = tree;
            if(0 != tree->right()) tree->right()->setColor(tree->color());
            tree = tree->right();
            item->setLeft(0);
            item->setRight(0);

            if(BLACK == item->color() && 0 == tree) toAdj = true; // Remove block node without red to replace.
        } else {
            T *rMost;
            toAdj = _rmRightMost(&l, &rMost);
            rMost->setRight(tree->right());
            rMost->setLeft(l);
            rMost->setColor(tree->color());
            item = tree;
            tree = rMost;
            item->setLeft(0);
            item->setRight(0);
            if(toAdj) toAdj = _rmAdjLeft(&tree);
        }
    } else {
        T *r = tree->right();
        if(0 == r) {
        } else {
            toAdj = _removeLeastGreater(&r, &item, k, eq, less);
            tree->setRight(r);
            if(toAdj) toAdj = _rmAdjRight(&tree);
        }
    }
    return toAdj;
}

template<class T>
T *TRBTree<T>::removeLeastGreater(const typename T::Key &k,
                                  bool (*eq)(const Key &lhs, const Key &rhs),
                                  bool (*less)(const Key &lhs, const Key &rhs))
{
    T *item = 0;
    (void)_removeLeastGreater(&_root, &item, k, eq, less);

    if(0 != item) {
        item->setLeft(0);
        item->setRight(0);
    }

    if(0 != _root) _root->setColor(BLACK);

    return item;
}

template<class T>
bool TRBTree<T>::_rmRightMost(T **pTree, T **pItem)
{
    bool toAdj = false;
    T *&tree = *pTree;
    T *&item = *pItem;

    T *r = tree->right();
    if(0 == r) {
        item = tree;
        tree = tree->left();
        if(BLACK == item->color() && 0 != tree && RED == tree->color()) tree->setColor(BLACK);
        else if(BLACK == item->color())                                 toAdj = true;
    } else {
        toAdj = _rmRightMost(&r, &item);
        tree->setRight(r);
        if(toAdj) toAdj = _rmAdjRight(&tree);
    }
    return toAdj;
}

template<class T>
bool TRBTree<T>::_rmAdjRight(T **pTree)
{
    bool toAdj = false;
    T *&tree = *pTree;

    T *l = tree->left();
    ASSERT(0 != l);

    T *ll = l->left();
    T *lr = l->right();

    if(BLACK == tree->color() &&
       BLACK == l->color() &&
       (0 == ll || BLACK == ll->color()) &&
       (0 == lr || BLACK == lr->color())   ) {
        l->setColor(RED);
        toAdj = true;
    } else if(RED == l->color()) {
        tree = _rotateRight(tree);
        _swapColorRight(tree);
        T *r = tree->right();
        toAdj = _rmAdjRight(&r);
        tree->setRight(r);
        if(toAdj) toAdj = _rmAdjRight(&tree);
    } else if(0 != ll && RED == ll->color()) {
        tree = _rotateRight(tree);
        _swapColorRight(tree);
        tree->left()->setColor(BLACK);
    } else if(0 != lr && RED == lr->color()) {
        l = _rotateLeft(l);
        _swapColorLeft(l);
        tree->setLeft(l);
        toAdj = _rmAdjRight(&tree);
    } else if(RED == tree->color()) {
        ASSERT(BLACK == l->color());
        tree = _rotateRight(tree);
    } else {
        ASSERT(false);
    }
    return toAdj;
}

template<class T>
bool TRBTree<T>::_rmAdjLeft(T **pTree)
{
    bool toAdj = false;
    T *&tree = *pTree;

    T *r = tree->right();
    ASSERT(0 != r);

    T *rr = r->right();
    T *rl = r->left();

    if(BLACK == tree->color() &&
       BLACK == r->color() &&
       (0 == rr || BLACK == rr->color()) &&
       (0 == rl || BLACK == rl->color())   ) {
        r->setColor(RED);
        toAdj = true;
    } else if(RED == r->color()) {
        tree = _rotateLeft(tree);
        _swapColorLeft(tree);
        T *l = tree->left();
        toAdj = _rmAdjLeft(&l);
        tree->setLeft(l);
        if(toAdj) toAdj = _rmAdjLeft(&tree);
    } else if(0 != rr && RED == rr->color()) {
        tree = _rotateLeft(tree);
        _swapColorLeft(tree);
        tree->right()->setColor(BLACK);
    } else if(0 != rl && RED == rl->color()) {
        r = _rotateRight(r);
        _swapColorRight(r);
        tree->setRight(r);
        toAdj = _rmAdjLeft(&tree);
    } else if(RED == tree->color()) {
        ASSERT(BLACK == r->color());
        tree = _rotateLeft(tree);
    } else {
        ASSERT(false);
    }
    return toAdj;
}


#endif // _RBTREE_H_


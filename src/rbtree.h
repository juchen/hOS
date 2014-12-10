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
public:
    enum COLOR {
        RED,
        BLACK,
    };

    T    *find(T *sample, bool (T::*equalFn)(const T*) = T::equalTo);   // sample should carry a key the same as the target to find.
    void  insert(T *item);
    T    *remove(T *sample); // sample should carry a key the same as the target to find.

    TRBTree();
protected:
    T *_root;

private:
    T *_insert(T *tree, T *item);
};

template<class T>
TRBTree<T>::TRBTree()
    : _root(0)
{
}

template<class T>
void TRBTree<T>::insert(T *item)
{
    _root = _insert(_root, item);
    _root->setColor(BLACK);
}

template<class T>
T *TRBTree<T>::_insert(T *tree, T *item)
{
    if(0 == tree) return item;

    tree->setLeft(item);
    return tree;
}

#endif // _RBTREE_H_


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

    T    *find(typename T::Key k,
               bool (T::*eq)(const typename T::Key &k) = (T::operator ==),
               bool (T::*less)(const typename T::Key &k) = (T::operator <));   // sample should carry a key the same as the target to find.
    void  insert(T *item);
    T    *remove(typename T::Key k,
                 bool (T::*eq)(const typename T::Key &k) = (T::operator ==),
                 bool (T::*lessFn)(const typename T::Key &k) = (T::operator <));   // sample should carry a key the same as the target to find.
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

#endif // _RBTREE_H_


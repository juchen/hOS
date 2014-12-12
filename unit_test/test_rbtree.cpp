#include "rbtree.h"
#include "stdio.h"

#define TRACE_HEX(x) printf(__FILE__ ":%d:" #x " = 0x%08x\n", __LINE__, (unsigned int)(x))
#define TRACE_DEC(x) printf(__FILE__ ":%d:" #x " = %d\n", __LINE__, (unsigned int)(x))
#define CHECK_POINT printf(__FILE__ ":%d: check point\n", __LINE__)

class TestNode
{
public:
    typedef int Key;

private:
    typedef TRBTree<TestNode>::COLOR COLOR;

public:
                TestNode(int value);
    COLOR       color();
    TestNode   *left();
    TestNode   *right();
    void        setColor(TRBTree<TestNode>::COLOR c);
    void        setLeft(TestNode *l);
    void        setRight(TestNode *r);
    Key         key() { return _value; }

    void        showTree(int indent = 0);
    const char *colorString(COLOR c);
    int         value() { return _value; }

    static const COLOR RED   = TRBTree<TestNode>::RED;
    static const COLOR BLACK = TRBTree<TestNode>::BLACK;

private:
    int       _value;
    COLOR     _color;
    TestNode *_left;
    TestNode *_right;

};


TestNode::TestNode(int value)
    : _value(value),
      _color(TRBTree<TestNode>::RED),
      _left(0),
      _right(0)
{
}

void TestNode::setLeft(TestNode *l)
{
    _left = l;
}

void TestNode::setRight(TestNode *r)
{
    _right = r;
}

TestNode *TestNode::left()
{
    return _left;
}

TestNode *TestNode::right()
{
    return _right;
}

TestNode::COLOR TestNode::color()
{
    return _color;
}

void TestNode::setColor(COLOR c)
{
    _color = c;
}

static void printIndent(int n)
{
    for(int i = 0; i < n; ++i) printf("\t");
}

const char *TestNode::colorString(COLOR c)
{
    return RED == c ? "Red" : "Black";
}

void TestNode::showTree(int indent)
{
    if(0 != left()) {
        left()->showTree(indent + 1);
    }

    printIndent(indent);
    printf("%s %d\n", colorString(color()), _value);

    if(0 != right()) {
        right()->showTree(indent + 1);
    }
}

void testShowTree()
{
    CHECK_POINT;
    TestNode n1(1);
    TestNode n2(2);
    TestNode n3(3);
    n1.setLeft(&n2);
    n1.setRight(&n3);
    n1.showTree();
}

static int blackDepth(TestNode *tree)
{
    if(0 == tree) return 0;

    int incDepth = (TestNode::BLACK == tree->color() ? 1 : 0);

    if(0 == tree->left() && 0 == tree->right()) return incDepth;

    int lDepth = blackDepth(tree->left());
    int rDepth = blackDepth(tree->right());

    if(lDepth != rDepth) return -1;

    return incDepth + lDepth;
}

static bool propWellSorted(TestNode *tree)
{
    if(0 == tree) return true;

    if(0 != tree->left() && !(tree->left()->key() < tree->key())) return false;

    if(0 != tree->right() && !(tree->key() < tree->right()->key())) return false;

    return propWellSorted(tree->left()) && propWellSorted(tree->right());
}

static bool propNoTwoRed(TestNode *tree)
{
    if(0 == tree) return true;

    if(tree->color() == TestNode::RED) {
        if(0 != tree->left()  && tree->left()->color()  == TestNode::RED) return false;
        if(0 != tree->right() && tree->right()->color() == TestNode::RED) return false;
    }

    return propNoTwoRed(tree->left()) && propNoTwoRed(tree->right());
}

void testInsertRemove()
{
    CHECK_POINT;
    TRBTree<TestNode> tree;

    for(int i = 10000; i > 0; --i) {
        tree.insert(new TestNode(i));
    }

    tree.root()->showTree();

    TRACE_DEC(blackDepth(tree.root()));
    ASSERT(blackDepth(tree.root()) >= 3);
    ASSERT(propWellSorted(tree.root()));
    ASSERT(propNoTwoRed(tree.root()));

    for(int i = 5000; i < 10000; ++i) {
        TestNode *n = tree.remove(i);
        ASSERT(n->value() == i);
    }

    TRACE_DEC(blackDepth(tree.root()));
    ASSERT(blackDepth(tree.root()) >= 0);
    ASSERT(propWellSorted(tree.root()));
    ASSERT(propNoTwoRed(tree.root()));

    tree.root()->showTree();
}

void testInsertRemoveLeastGreater()
{
    CHECK_POINT;
    TRBTree<TestNode> tree;

    for(int i = 0; i <= 10000; i+=10) {
        tree.insert(new TestNode(i));
    }

    tree.root()->showTree();

    TRACE_DEC(blackDepth(tree.root()));
    ASSERT(blackDepth(tree.root()) >= 3);
    ASSERT(propWellSorted(tree.root()));
    ASSERT(propNoTwoRed(tree.root()));

    for(int i = 5005; i <= 10000; i+=10) {
        TestNode *n = tree.removeLeastGreater(i);
        ASSERT(n->value() == i+5);
    }

    TRACE_DEC(blackDepth(tree.root()));
    ASSERT(blackDepth(tree.root()) >= 0);
    ASSERT(propWellSorted(tree.root()));
    ASSERT(propNoTwoRed(tree.root()));

    tree.root()->showTree();
}


int main(int argc, char **argv)
{
    testShowTree();
    testInsertRemove();
    testInsertRemoveLeastGreater();
    return 0;
}


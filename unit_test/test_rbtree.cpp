#include "rbtree.h"
#include "stdio.h"

#define TRACE_HEX(x) printf(__FILE__ ":%d:" #x " = 0x%08x\n", __LINE__, (unsigned int)(x))
#define CHECK_POINT printf(__FILE__ ":%d: check point\n", __LINE__)

class TestNode
{
private:
    typedef TRBTree<TestNode>::COLOR COLOR;

public:
                TestNode(int value);
    COLOR       getColor();
    TestNode   *getLeft();
    TestNode   *getRight();
    void        setColor(TRBTree<TestNode>::COLOR c);
    void        setLeft(TestNode *l);
    void        setRight(TestNode *r);
    bool        lessThan(TestNode *lhs, TestNode *rhs);
    bool        equalTo(TestNode *lhs, TestNode *rhs);

    void        showTree(int indent = 0);
    const char *colorString(COLOR c);

private:
    int       _value;
    COLOR     _color;
    TestNode *_left;
    TestNode *_right;

    static const COLOR RED   = TRBTree<TestNode>::RED;
    static const COLOR BLACK = TRBTree<TestNode>::BLACK;
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

TestNode *TestNode::getLeft()
{
    return _left;
}

TestNode *TestNode::getRight()
{
    return _right;
}

TestNode::COLOR TestNode::getColor()
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
    if(0 != getLeft()) {
        printIndent(indent + 1);
        getLeft()->showTree();
    }

    printf("%s %d\n", colorString(getColor()), _value);

    if(0 != getRight()) {
        printIndent(indent + 1);
        getRight()->showTree();
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

void testInsert()
{
    CHECK_POINT;
    TestNode n1(1);
    TRBTree<TestNode> tree;
    tree.insert(&n1);
    n1.showTree();
}

int main(int argc, char **argv)
{
    testShowTree();
    testInsert();
    return 0;
}


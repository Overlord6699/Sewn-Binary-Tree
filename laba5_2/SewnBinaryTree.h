#pragma once
#include "BinaryTree.h"


class SewnBinaryTree : public BinaryTree
{

    nodeptr head;
    

private:
    void sewLeft(nodeptr current, nodeptr prevPtr);
    void sewRight(nodeptr current, nodeptr prevPtr);

    void sewAgain();
    void stitchLeftAgain(nodeptr curPtr, nodeptr prevPtr);
    void stitchRightAgain(nodeptr curPtr, nodeptr prevPtr);

    nodeptr& insertInSewnTree(nodeptr& ptr, const int value);

    void symmetricSewnPrint(nodeptr ptr);

    nodeptr getLeftLeaf(nodeptr ptr);

    void inOrderWithCopy(nodeptr ptr);

    nodeptr delNodeWith1Childs(nodeptr ptr, nodeptr parent, nodeptr current);
    nodeptr delNodeWith2Childs(nodeptr ptr, nodeptr current);
    nodeptr delNodeWith0Childs(nodeptr ptr, nodeptr parent, nodeptr current);

    nodeptr findNext(nodeptr current);
    nodeptr findPrev(nodeptr current);
public:
    //прошито ли дерево в данный момент
    bool isSewn = false, isLeftSewn = false, isRightSewn = false;

    void initHead();
    void insertInSewnTree(const int value);
    nodeptr remove(nodeptr ptr, const int value);
    void sew(const int choice);
    nodeptr findInSewnTree(const int value);

    //подходит только для симметричной прошивки(и правой, и левой).
    void print();

    //для визуализации нужно сделать копирование дерева
    void visualize();
    SewnBinaryTree(const SewnBinaryTree& other);

    SewnBinaryTree();
    SewnBinaryTree(BinaryTree& tree);
    ~SewnBinaryTree() = default;
};
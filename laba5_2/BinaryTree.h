#pragma once
#include "Node.h"
#include <cstddef>
#include <string>
#include <iostream>
#include <queue>
using namespace std;

class BinaryTree
{ 
protected:
    int node_length;
    int space_length;
    int tree_height_;
    int tree_nodes_;
    string** values_;

    int node_length_;
    int node_type_;
    int node_shift_factor_;
    string empty_node_;

    int space_length_;
    int space_shift_factor_;

    int get_nodes_count(int) const;
    int get_subtree_width(int) const;

    int deletemin(nodeptr&);

    nodeptr getMostLeftChild(nodeptr ptr);

    int max(int, int);
public:
    nodeptr root;

    int CalculateLeftAndRightChilds(nodeptr ptr, int allChild);

    void printTreeHeight();
    int btheight(nodeptr);
    int get_tree_height(nodeptr root) const;

    void insert(int value, nodeptr& ptr);
    void del(int value, nodeptr& ptr);
 

    nodeptr& find(int x, nodeptr& ptr);
    nodeptr findmin(nodeptr);
    nodeptr findmax(nodeptr);

    
    queue<nodeptr> breadth_first_search();

    //добавлен bool для отображения нулей(для моей лабы)
    void preorder(nodeptr, const bool showZeros);
    void inorder(nodeptr, const bool showZeros);
    void postorder(nodeptr, const bool showZeros);


    nodeptr srl(nodeptr&);
    nodeptr drl(nodeptr&);
    nodeptr srr(nodeptr&);
    nodeptr drr(nodeptr&);

    //для визуализации нужно сделать копирование дерева
    void visualize();

    BinaryTree() = default;
    //конструктор копирования
    BinaryTree(const BinaryTree&);
    ~BinaryTree() = default;
};
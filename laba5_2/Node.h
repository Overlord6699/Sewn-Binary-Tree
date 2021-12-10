#pragma once
#include <cstddef>

struct node
{
    int element;
    int height;
    node* left;
    node* right;
    //дл€ прошивки дерева
    bool rightTag, leftTag; //true - типична€ св€зь, false - прошив. нить

    node(const int value, const bool l_tag, const bool r_tag)
    {
        this->element = value;
        this->height = 0;
        this->right = NULL;
        this->left = NULL;
        this->leftTag = l_tag;
        this->rightTag = r_tag;
    }

    node()
    {
        this->right = NULL;
        this->left = NULL;
        this->rightTag = true;
        this->leftTag = true;
    }
};
typedef struct node* nodeptr;

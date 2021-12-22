#include "SewnBinaryTree.h"
#include <cassert>
#include <iomanip>

SewnBinaryTree::SewnBinaryTree(const SewnBinaryTree& other)
{
    this->isSewn = other.isSewn;
    this->root = other.root;
    initHead();

    int leftNodeLength = 0, rightNodeLength = 0;

    auto min_node_len = 0;
    auto min_space_len = 0;

    root = other.root;
    node_length = -1;
    space_length = -1;
    tree_height_ = get_tree_height(root);
    tree_nodes_ = get_nodes_count(tree_height_) - 1;
    queue<nodeptr> nodes = breadth_first_search();
    values_ = new string * [tree_nodes_];

    for (auto level = 0; level < tree_height_; level++)
    {
        values_[level] = new string[get_nodes_count(level)];
        for (auto node = 0; node < get_nodes_count(level); node++)
        {
            leftNodeLength = 0;
            rightNodeLength = 0;
            auto ptr = nodes.front();
            // Convert node to string and add it to values vector
            // also add empty string if node is empty
            auto value = ptr == nullptr ? "" : to_string(ptr->element);
            
            //поиск прошивок дерева
            if (isSewn && !value.empty()) {
                if (!ptr->rightTag && ptr->right) {
                    value += "-(" + to_string(ptr->right->element) + ")";
                    //3 символа - "-()"
                    rightNodeLength = 3 + to_string(ptr->right->element).length();
                }


                if (!ptr->leftTag && ptr->left) {
                    value = "(" + to_string(ptr->left->element) + ")-" + value;
                    leftNodeLength = 3 + to_string(ptr->left->element).length();
                }
            }

            values_[level][node] = value;
            nodes.pop();

            // Calculate minimum required node length
            const int length = value.length();

            if (min_node_len < length) min_node_len = length;
        }
    }

    // Initialize node-related variables
    node_length_ = node_length > min_node_len ? node_length : min_node_len;       // Choose suitable node length
    node_type_ = node_length_ % 2;                                              // ZERO if length is even and ONE if odd
    node_shift_factor_ = node_length_ / 2;                                              // Shifting factor used in visualizing
    empty_node_ = string(node_length_, ' ');                                     // Represents an empty node

    // Initialize space-related variables
    min_space_len = node_type_ ? 3 : 4;                                            // Calculate minimum required space length
    space_length_ = space_length > min_space_len ? space_length : min_space_len;   // Choose suitable node length
    space_shift_factor_ = space_length_ / 2;                                             // Shifting factor used in visualizing

    // Make sure that  both values are either even or odd
    assert(node_type_ == space_length_ % 2);
}

void SewnBinaryTree::visualize()
{
    const auto last_level = tree_height_ - 1;

    //drawing tree
    for (auto level = 0; level < tree_height_; level++)
    {
        const auto nodes_count = get_nodes_count(level);
        const auto last_node = nodes_count - 1;
        const auto subtree_width = get_subtree_width(level);
        const auto node_indentation = subtree_width / 2 - node_shift_factor_;
        const auto nodes_spacing = subtree_width - 2 * (node_shift_factor_ - space_shift_factor_);
        const auto branch_height = (subtree_width + 1) / 4;

        cout << string(node_indentation, ' ');

        //drawing level
        for (auto node = 0; node < nodes_count; node++)
        {
            auto node_value = values_[level][node].empty() ? empty_node_ : values_[level][node];
            //вывод значения вершины

            //заполнение пустоты в значении нулями
            if(node_value[0] == '(' || node_value[node_value.length()-1] == ')')
                cout << setw(node_length_) << setfill(' ') << node_value;
            else
                cout << setw(node_length_) << setfill('0') << node_value;
            //отступ от вершин
            cout << string(nodes_spacing * (node != last_node), ' ');
        }

        cout << endl;

        //drawing connections
        for (auto i = 0; i < branch_height && level != last_level; i++)
        {
            const auto branch_indentation = subtree_width / 2 - 1 - i;
            cout << string(branch_indentation, ' ');

            for (auto node = 0; node < nodes_count; node++)
            {
                const auto has_left_child = !values_[level + 1][2 * node].empty();
                const auto has_right_child = !values_[level + 1][2 * node + 1].empty();
                const auto branch_width = node_type_ + 2 * i;
                const auto branches_spacing = nodes_spacing + 2 * (node_shift_factor_ - 1 - i);

                cout << (has_left_child ? '/' : ' ');
                cout << string(branch_width, ' ');
                cout << (has_right_child ? '\\' : ' ');
                //отступ соседних палок
                cout << string(branches_spacing * (node != last_node), ' ');
            }

            cout << endl;
        }
    }
}

nodeptr SewnBinaryTree::findInSewnTree(const int value)
{
    nodeptr current = head->left;
    current = getLeftLeaf(current);
    while (current->element != head->element) {
        if (current->element == value) {
            break;
        }
        if (current->rightTag && current->right) {
            current = current->right;
            current = getLeftLeaf(current);
        }
        else {
            if (current->element == value) {
                break;
            }

            if(current->right)
                current = current->right;
        }
    }

    return (current->element == head->element) ? NULL : current;
}

SewnBinaryTree::SewnBinaryTree()
{
    initHead();
}

//копирование узлов из BinaryTree в SewnNodeTree
SewnBinaryTree::SewnBinaryTree(BinaryTree& tree)
{
    this->root = tree.root;
    initHead();
    //inOrderWithCopy(tree.root);   
}

void SewnBinaryTree::initHead()
{
    head = new node();
    head->element = root->element;
    head->left = root;
    head->right = head;
}


void SewnBinaryTree::print()
{
    nodeptr realRoot = head->left;
    symmetricSewnPrint(realRoot);
}

void SewnBinaryTree::sewLeft(nodeptr current, nodeptr prevPtr)
{
    if (current) {
        if (current->left)
        {
            current->leftTag = true;
            sewLeft(current->left, prevPtr);
        }
        else {
            current->leftTag = false;
            current->left = prevPtr;
        }

        prevPtr = current;
        sewLeft(current->right, prevPtr);
    }
}

void SewnBinaryTree::sewRight(nodeptr current, nodeptr prevPtr)
{
    if (current) {
        if (current->right) {
            current->rightTag = true;
            sewRight(current->right, prevPtr);
        }
        else {
            current->rightTag = false;
            current->right = prevPtr;
        }

        prevPtr = current;

        if (current->leftTag)
            sewRight(current->left, prevPtr);
    }
}

void SewnBinaryTree::sewAgain()
{
    nodeptr prevPtr = head;
    nodeptr curPtr = head->left;

    if (isLeftSewn)
        stitchLeftAgain(curPtr, prevPtr);
    if (isRightSewn)
        stitchRightAgain(curPtr, prevPtr);
}

void SewnBinaryTree::stitchLeftAgain(nodeptr curPtr, nodeptr prevPtr)
{
    if (curPtr) {
        if (curPtr->leftTag)
            stitchLeftAgain(curPtr->left, prevPtr);
        else
            curPtr->left = prevPtr;

        prevPtr = curPtr;

        if (curPtr->rightTag)
            stitchLeftAgain(curPtr->right, prevPtr);
    }
}

void SewnBinaryTree::stitchRightAgain(nodeptr curPtr, nodeptr prevPtr)
{
    if (curPtr) {
        if (curPtr->rightTag) {
            stitchRightAgain(curPtr->right, prevPtr);
        }
        else {
            curPtr->right = prevPtr;
        }

        prevPtr = curPtr;
        if (curPtr->leftTag)
            stitchRightAgain(curPtr->left, prevPtr);
    }
}

void SewnBinaryTree::insertInSewnTree(const int value)
{
    insertInSewnTree(root, value);
    
    sewAgain();
}

nodeptr SewnBinaryTree::remove(nodeptr ptr, const int value)
{
    nodeptr parent = NULL;
    nodeptr current = ptr;

    bool found = false;

    while (current != NULL) {
        if (value == current->element) { 
            found = true;           
            break; 
        }     

        parent = current;

        if (value < current->element) {
            if (current->leftTag)
                current = current->left;        
            else 
                break; 
        } 
        else { 
            if (current->rightTag)
                current = current->right;
            else 
                break; 
        }
    }

    if (found)
    {
        if ((current->leftTag && current->left) && (current->rightTag && current->right))
            ptr = delNodeWith2Childs(ptr, current);
        else if ((current->leftTag && current->left) || (current->rightTag && current->right))
            ptr = delNodeWith1Childs(ptr, parent, current);
        else
            ptr = delNodeWith0Childs(ptr, parent, current);
    }    
    
    return ptr;
}

void SewnBinaryTree::sew(const int choice)
{
    nodeptr prevPtr = head;
    nodeptr curPtr = head->left;

    if (1 == choice) {
        sewRight(curPtr, prevPtr);
        isRightSewn = true;
        cout << "\nПравая прошивка успешно выполнена.";
    }
    else if (2 == choice)
    {
        sewLeft(curPtr, prevPtr);
        isLeftSewn = true;
        cout << "\nЛевая прошивка успешно выполнена.";
    }
    else
    {
        sewLeft(curPtr, prevPtr);
        sewRight(curPtr, prevPtr);
        isLeftSewn = true;
        isRightSewn = true;
        cout << "\nСимметричная прошивка успешно выполнена.";
    }

    isSewn = true;
}

nodeptr& SewnBinaryTree::insertInSewnTree(nodeptr& ptr, const int value)
{
    if (ptr) {
        if (value < ptr->element) {
            if (ptr->leftTag && ptr->left)
                ptr->left = insertInSewnTree(ptr->left, value);
            else {
                ptr->left = new node(value, false, false);
                ptr->leftTag = true;
            }
        }

        if (value > ptr->element) {
            if (ptr->rightTag && ptr->right)
                ptr->right = insertInSewnTree(ptr->right, value);
            else {
                ptr->right = new node(value, false, false);
                ptr->rightTag = true;
            }
        }
    }
    
    return ptr;
}

nodeptr SewnBinaryTree::getLeftLeaf(nodeptr ptr)
{
    while (ptr->leftTag)
        ptr = ptr->left;

    return ptr;
}

void SewnBinaryTree::inOrderWithCopy(nodeptr ptr)
{
    if (ptr)
    {
        inOrderWithCopy(ptr->left);

        insert(ptr->element, root);

        inOrderWithCopy(ptr->right);
    }
}

nodeptr SewnBinaryTree::delNodeWith1Childs(nodeptr ptr, nodeptr parent, nodeptr current)
{
    nodeptr child;

    if (current->leftTag)
        child = current->left;
    else
        child = current->right;

    if (parent == NULL)
        ptr = child;
    else if (current == parent->left)
        parent->left = child;
    else
        parent->right = child;

    nodeptr next = findNext(current);
    nodeptr prev = findPrev(current);
    if (current->leftTag)
        prev->right = next;
    else
        next->left = prev;

    return ptr;
}

nodeptr SewnBinaryTree::delNodeWith2Childs(nodeptr ptr, nodeptr current)
{
    nodeptr nextParent = current;
    nodeptr next = current->right;

    while (next->leftTag && next->left) {
        nextParent = next; 
        next = next->left; 
    }

    current->element = next->element;

    if (!next->rightTag || !next->right)
        ptr = delNodeWith0Childs(ptr, nextParent, next);
    else if(next->right)
        ptr = delNodeWith1Childs(ptr, nextParent, next);

    return ptr;
}

nodeptr SewnBinaryTree::delNodeWith0Childs(nodeptr ptr, nodeptr parent, nodeptr current)
{
    if (parent == NULL)
        ptr = NULL;
    else if (current == parent->left) {
        parent->leftTag = false;
        parent->left = current->left; 
    }
    else { 
        parent->rightTag = false;
        parent->right = current->right; 
    }

    return ptr;
}

nodeptr SewnBinaryTree::findNext(nodeptr current)
{
    if (!current->rightTag)
        return current->right;

    if(current->right)
        current = current->right;

    while (current->leftTag && current->left)
        current = current->left;

    return current;
}

nodeptr SewnBinaryTree::findPrev(nodeptr current)
{
    if (!current->leftTag)
        return current->left;

    if(current->left)
        current = current->left;

    while (current->rightTag && current->right)
        current = current->right;

    return current;
}

void SewnBinaryTree::symmetricSewnPrint(nodeptr ptr)
{
    ptr = getLeftLeaf(ptr);

    while (ptr->element != head->element) {
        if (ptr->element != head->element)
            cout << ptr->element << '\t';
        if (ptr->rightTag) {
            ptr = ptr->right;

            if (ptr->leftTag) {
                ptr = getLeftLeaf(ptr);
            }
        }
        else {
            ptr = ptr->right;
        }
    }
}
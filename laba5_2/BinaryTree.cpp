#include "BinaryTree.h"
#include "Node.h"
#include <iomanip>
#include <cassert>

//�����������
BinaryTree::BinaryTree(const BinaryTree& other)
{
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
            // Convert node to string and add it to values vector
            // also add empty string if node is empty
            auto value = nodes.front() == nullptr ? "" : to_string(nodes.front()->element);
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

    // Make sure that both values are either even or odd
    assert(node_type_ == space_length_ % 2);
}

int BinaryTree::get_tree_height(nodeptr ptr) const
{
    int right_height = 0, left_height = 0;

    if (ptr == nullptr) return 0;

    if(ptr->left && ptr->leftTag)
        left_height = get_tree_height(ptr->left);
    if(ptr->right && ptr->rightTag)
        right_height = get_tree_height(ptr->right);

    return left_height > right_height ? left_height + 1 : right_height + 1;
}

int BinaryTree::get_nodes_count(const int level) const
{
    return int(pow(2, level));
}

int BinaryTree::get_subtree_width(const int level) const
{
    const auto levels_below = tree_height_ - level - 1;
    const auto nodes_count = get_nodes_count(levels_below);
    const auto spaces_count = nodes_count - 1;
    return node_length_ * nodes_count + space_length_ * spaces_count;
}

void BinaryTree::visualize()
{
    const auto last_level = tree_height_ - 1;

    for (auto level = 0; level < tree_height_; level++)
    {
        const auto nodes_count = get_nodes_count(level);
        const auto last_node = nodes_count - 1;
        const auto subtree_width = get_subtree_width(level);
        const auto node_indentation = subtree_width / 2 - node_shift_factor_;
        const auto nodes_spacing = subtree_width - 2 * (node_shift_factor_ - space_shift_factor_);
        const auto branch_height = (subtree_width + 1) / 4;

        cout << string(node_indentation, ' ');

        for (auto node = 0; node < nodes_count; node++)
        {
            auto node_value = values_[level][node].empty() ? empty_node_ : values_[level][node];
            //����� �������� �������
            
            /*
            //��
            
            nodeptr findPtr = (stoi(node_value), root);


            if (!findPtr->rightTag && findPtr->right)
                node_value = "-(" + to_string(findPtr->right->element) + ")" + node_value;
             */

            cout << setw(node_length_) << setfill('0') << node_value;
            //������
            cout << string(nodes_spacing * (node != last_node), ' ');
        }

        cout << endl;

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
                cout << string(branches_spacing * (node != last_node), ' ');
            }

            cout << endl;
        }
    }
}

void BinaryTree::insert(int value, nodeptr& ptr)
{
    if (ptr == NULL)
    {
        ptr = new node();
        ptr->element = value;
        ptr->left = NULL;
        ptr->right = NULL;
        ptr->height = 0;
        if (ptr == NULL)
        {
            cout << "������ �������� ������!\n" << endl;
        }
    }
    else
    {
        if (value < ptr->element) // �����
        {
            insert(value, ptr->left);
            if ((btheight(ptr->left) - btheight(ptr->right)) == 2)
            {
                if (value < ptr->left->element)
                {
                    ptr = srl(ptr);
                }
                else
                {
                    ptr = drl(ptr);
                }
            }
        }
        else if (value > ptr->element) // ������
        {
            insert(value, ptr->right);
            if ((btheight(ptr->right) - btheight(ptr->left)) == 2)
            {
                if (value > ptr->right->element)
                {
                    ptr = srr(ptr);
                }
                else
                {
                    ptr = drr(ptr);
                }
            }
        }
        else
        {
            cout << "������� ��� ����������.\n" << endl;
        }
    }

    int m, n, d; // ����� ������ ������
    m = btheight(ptr->left);
    n = btheight(ptr->right);
    d = max(m, n);
    ptr->height = d + 1;
}

nodeptr BinaryTree::findmin(nodeptr ptr)
{
    if (ptr == NULL)
    {
        cout << "� ������ ��� ���������.\n" << endl;
    }
    else
    {
        while (ptr->left != NULL)
        {
            ptr = ptr->left;
        }
    }
    return ptr;
}

nodeptr BinaryTree::findmax(nodeptr ptr)
{
    if (ptr == NULL)
    {
        cout << "� ������ ��� ���������.\n" << endl;
    }
    else
    {
        while (ptr->right != NULL)
        {
            ptr = ptr->right;
        }
    }
    return ptr;
}

void BinaryTree::printTreeHeight()
{
    cout << "������ ������ �����: " <<
        to_string(btheight(root)) << endl;
}

//����� �������� ���-�� �������� ����� � ������
int BinaryTree::CalculateLeftAndRightChilds(nodeptr ptr, int allChild)
{
    int countLeft, countRight;
    if (ptr == NULL) //����� �� ���(���� �����).
    {
        allChild = 0;//�������� ���.
    }
    else
    {       //���� ���� ����������.
        //������� ���������� �������� ��� �������� ����.
        countLeft = CalculateLeftAndRightChilds(ptr->left, allChild);  //��� ����� �����.
        countRight = CalculateLeftAndRightChilds(ptr->right, allChild); //��� ������ �����.
        if (countLeft != countRight)
        {
            cout << "(" << ptr->element << "): �������� ����� = " << countLeft << " �������� ������ = " << countRight << endl;
        }
        allChild = 1 + countLeft + countRight;    //������� ������� ������� = 1 + ������� ����� + ������� ������
    }
    return allChild;
}

queue<nodeptr> BinaryTree::breadth_first_search()
{
    queue<nodeptr> temp, nodes;
    temp.push(root);

    for (auto i = 0; i < tree_nodes_; i++)
    {
        nodeptr current = temp.front();
        temp.pop();
        nodes.push(current);

        if (current == nullptr)
        {
            temp.push(nullptr);
            temp.push(nullptr);
        }
        else
        {
            //��������� �������� �����
            if(current->leftTag)
                temp.push(current->left);
            else
                temp.push(nullptr);

            if(current->rightTag)
                temp.push(current->right);
            else
                temp.push(nullptr);
        }
    }

    return nodes;
}

nodeptr& BinaryTree::find(int x, nodeptr& ptr)
{
    if (ptr == NULL)
    {
        cout << "������ �������� �� ����������.\n" << endl;

        return ptr;
    }
    else
    {
        if (x < ptr->element) // ��� �����
        {
            if(ptr->leftTag)
                find(x, ptr->left);
        }
        else
        {
            if (x > ptr->element) // ��� ������
            {
                if (ptr->rightTag)
                    find(x, ptr->right);
            }
            else
            {
                cout << "�������, ������� �� ������, ���� � ������!\n" << endl;
                return ptr;
            }
        }
    }
}

void BinaryTree::del(int value, nodeptr& ptr)
{
    nodeptr tmp = NULL;

    if (ptr == NULL)
    {
        cout << "������ �������� �� ����������.\n" << endl;
    }
    else if (value < ptr->element) // �����
    {
        del(value, ptr->left);
    }
    else if (value > ptr->element) // ������
    {
        del(value, ptr->right);
    }
    else if ((ptr->left == NULL) && (ptr->right == NULL)) // ���� ��� ����
    {
        tmp = ptr;
        free(tmp);
        ptr = NULL;
        cout << "������� ������\n" << endl;
    }
    else if (ptr->left == NULL)
    {
        tmp = ptr;
        free(tmp);
        ptr = ptr->right; // ��������� ������ ������ ���������
        cout << "������� ������\n" << endl;
    }
    else if (ptr->right == NULL)
    {
        tmp = ptr;
        free(tmp);
        ptr = ptr->left; // ��������� �����
        cout << "������� ������\n" << endl;
    }
    else
    {
        cout << "������� �������� ������������ ��������.\n" << endl;
        ptr->element = deletemin(ptr->right);
    }
}

int BinaryTree::deletemin(nodeptr& ptr)
{
    int tmpElem;
    if (ptr->left == NULL) // ���� ����� ������ ���, �� ����������� ������� ����� ������
    {
        tmpElem = ptr->element;
        ptr = ptr->right;
    }
    else
    {
        tmpElem = deletemin(ptr->left);
    }
    return tmpElem;
}

void BinaryTree::preorder(nodeptr ptr)
{
    if (ptr != NULL)
    {
        cout << ptr->element << "\t";

        if (ptr->leftTag)
            preorder(ptr->left);

        if (ptr->rightTag)
            preorder(ptr->right);
    }
}

void BinaryTree::inorder(nodeptr ptr)
{
    if (ptr != NULL)
    {
        if(ptr->leftTag)
            inorder(ptr->left);

        cout << ptr->element << "\t";

        if(ptr->rightTag)
            inorder(ptr->right);
    }
}

nodeptr BinaryTree::getMostLeftChild(nodeptr ptr)
{
    nodeptr current = ptr;

    while (current->left)
    {
        current = current->left;
    }

    return current;
}

void BinaryTree::postorder(nodeptr ptr)
{
    if (ptr != NULL)
    {
        if (ptr->leftTag)
            postorder(ptr->left);

        if (ptr->rightTag)
            postorder(ptr->right);

        cout << ptr->element << "\t";
    }
}

int BinaryTree::max(int value1, int value2)
{
    return ((value1 > value2) ? value1 : value2); // ���� ������, �� ������, ����� ������
}

//������ ����
int BinaryTree::btheight(nodeptr ptr)
{
    int tmpHeight;
    if (ptr == NULL)
    {
        tmpHeight = -1;
    }
    else
    {
        tmpHeight = ptr->height;
    }
    return tmpHeight;
}

nodeptr BinaryTree::srl(nodeptr& ptr1)
{
    nodeptr ptr2;
    ptr2 = ptr1->left;
    ptr1->left = ptr2->right;
    ptr2->right = ptr1;
    ptr1->height = max(btheight(ptr1->left), btheight(ptr1->right)) + 1;
    ptr2->height = max(btheight(ptr2->left), ptr1->height) + 1;

    return ptr2;
}

nodeptr BinaryTree::srr(nodeptr& ptr1)
{
    nodeptr ptr2;
    ptr2 = ptr1->right;
    ptr1->right = ptr2->left;
    ptr2->left = ptr1;
    ptr1->height = max(btheight(ptr1->left), btheight(ptr1->right)) + 1;
    ptr2->height = max(ptr1->height, btheight(ptr2->right)) + 1;
    return ptr2;
}

nodeptr BinaryTree::drl(nodeptr& ptr1)
{
    ptr1->left = srr(ptr1->left);
    return srl(ptr1);
}

nodeptr BinaryTree::drr(nodeptr& ptr1)
{
    ptr1->right = srl(ptr1->right);
    return srr(ptr1);
}
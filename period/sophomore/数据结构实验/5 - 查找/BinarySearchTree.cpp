#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;


// 二叉查找树的结点
struct Node
{
    int value;
    Node *left_child = nullptr;
    Node *right_child = nullptr;
    
    Node(int value, Node *left_child = nullptr, Node *right_child = nullptr)
    {
        this->value = value;
        this->left_child = left_child;
        this->right_child = right_child;
    }
};


// 二叉查找树
class BinarySearchTree
{
private:
    Node *root = nullptr;

    // 从树中删除node结点
    void removeNode(Node * node)
    {
        if (node != nullptr) {
            removeNode(node->left_child);
            removeNode(node->right_child);
        }
        delete node;
    }

public:
    BinarySearchTree() = default;
    BinarySearchTree(int value)
    {
        root = new Node(value);
    }

    ~BinarySearchTree()
    {
        removeNode(root);
    }

    // 向树中添加值为value的结点
    void AddNode(int value)
    {
        Node *current = root, *parent = nullptr;
        while (current != nullptr)
        {
            if (current->value == value) return;  // 树中已存在结点，不进行添加
            
            parent = current;
            current = (current->value < value ? current->right_child : current->left_child);  // 根据根节点的值决定向左搜索或向右搜索
        }
        if (parent == nullptr) {  // 处理空树的情况
            root = new Node(value);
            return;
        }
        if (parent->value < value) parent->right_child = new Node(value);
        if (parent->value > value) parent->left_child = new Node(value);
    }

    // 向树中添加取值为values数组中各元素值的结点
    void AddNodes(vector<int> values)
    {
        for (int value : values) {
            AddNode(value);
        }
    }

    // 按升序打印结点值
    vector<int> GetAscendOrderNodeValue()
    {
        vector<int> values;

        function<void(Node *)> visitNode = [&](Node *node){
            if (node == nullptr) return;
            visitNode(node->left_child);
            values.push_back(node->value);
            visitNode(node->right_child);
        };

        visitNode(root);
        return values;
    }

    // 按降序打印结点值
    vector<int> GetDescendOrderNodeValue()
    {
        vector<int> values;

        function<void(Node *)> visitNode = [&](Node *node){
            if (node == nullptr) return;
            visitNode(node->right_child);
            values.push_back(node->value);
            visitNode(node->left_child);
        };

        visitNode(root);
        return values;
    }
};


// 生成随机数
vector<int> Generate10RandomNumbers()
{
    vector<int> random_numbers;
    for (int i = 0; i < 10; ++i)
        random_numbers.push_back(rand());
    return random_numbers;
}


// 打印数字
void ShowNumbers(vector<int> numbers)
{
    for (int number : numbers)
    {
        cout << number << ' ';
    }
    cout << endl;
}


int main()
{
    BinarySearchTree tree;
    vector<int> random_numbers(Generate10RandomNumbers());
    tree.AddNodes(random_numbers);
    cout << "随机产生的数字："; ShowNumbers(random_numbers);
    cout << "升序序列："; ShowNumbers(tree.GetAscendOrderNodeValue());
    cout << "降序序列："; ShowNumbers(tree.GetDescendOrderNodeValue());
}

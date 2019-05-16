#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;


// 结点定义
struct Node
{
    char value;  // 结点的值
    Node * left_child, * right_child;  // 结点的左孩子、右孩子指针
};


// 二叉树定义
using Tree = Node*;


// 根据先序序列和中序序列创建二叉树
// tree: 树根
// pre_order_string: 树对应的先序序列
// mid_order_string: 树对应的中序序列
void CreateTree(Tree& tree, const string& pre_order_string, const string& mid_order_string)
{
    if (pre_order_string.length() == 0) {
        tree = nullptr;
        return;
    }
    tree = new Node{pre_order_string[0], nullptr, nullptr};
    unsigned pos = mid_order_string.find_first_of(pre_order_string[0]);  // 中序遍历中根结点的位置
    CreateTree(tree->left_child, pre_order_string.substr(1, pos), mid_order_string.substr(0, pos));  // 递归创建左子树
    CreateTree(tree->right_child, pre_order_string.substr(pos + 1), mid_order_string.substr(pos + 1));  // 递归创建右子树
}


// 求二叉树的深度
int TreeDepth(Tree & tree)
{
    if (tree) {
        return max(TreeDepth(tree->left_child), TreeDepth(tree->right_child)) + 1;
    }
    return 0;
}


// 在标准输出中打印二叉树
// 打印格式形如：
//        F       
//    Q       B   
//  D   E   A   F 
// # F # # # # # #
void TreePrint(Tree & tree)
{
    int tree_depth = TreeDepth(tree);  // 待打印二叉树的深度
    function<void(int)> print_space = [](int space_count){
        while (space_count--) cout << ' ';
    };  // 输出space_count个空格的函数
    
    queue<Node *> que;
    que.push(tree);  // 树根结点入队
    
    // 按层打印二叉树
    for (int current_depth = 1; current_depth <= tree_depth; ++current_depth)
    {
        int next_level_node_count = 0;  // 下一层非空结点的个数
        int space_count = (1 << (tree_depth - current_depth)) - 1;  // 结点字符前后空格的数量
        queue<Node *> nxt;  // 下一层待打印的结点
        
        while (!que.empty())  // 当本层还有待打印的结点
        {
            print_space(space_count);  // 打印前导空格
            Node * front = que.front();  // 取结点
            if (front != nullptr) {  // 如果结点不是空结点
                cout << front->value;  // 打印结点
                nxt.push(front->left_child);  // 将左右孩子结点加入队列
                nxt.push(front->right_child);
                next_level_node_count += int(front->left_child != nullptr);  // 计算下一层待打印的结点的个数
                next_level_node_count += int(front->right_child != nullptr);
            }
            else {  // 如果结点是空结点
                cout << '#';  // 打印空结点符号
                nxt.push(nullptr);  // 放入表示空结点的值
                nxt.push(nullptr);
            }
            que.pop();  // 弹出当前结点
            que.empty() ? print_space(0) : print_space(space_count + 1);  // 打印后导空格
        }

        cout << '\n';  // 换行
        que = nxt;
        if (next_level_node_count == 0) break;
    }
}


int main()
{
    cout << "根据先序遍历和中序遍历构建二叉树。" << endl;

    string pre_order_string, mid_order_string;  // 先序序列和中序序列
    cout << "请输入先序序列："; cin >> pre_order_string;
    cout << "请输入中序序列："; cin >> mid_order_string;

    if (*pre_order_string.rbegin() != '#' || *mid_order_string.rbegin() != '#') 
    {  // 检查是否先序序列和中序序列是否以“#”标志结尾
        cout << "请以#作为序列的结束标志。" << endl;
        return -1;
    }
    pre_order_string.pop_back(), mid_order_string.pop_back();  // 在序列中移除末尾的“#”

    Tree tree;
    CreateTree(tree, pre_order_string, mid_order_string);
    TreePrint(tree);
}

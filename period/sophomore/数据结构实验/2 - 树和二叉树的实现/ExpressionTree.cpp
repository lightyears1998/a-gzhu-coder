#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

// 结点定义
struct Node
{
    string value;  // 结点的值
    Node * left_child, * right_child;  // 结点的左孩子、右孩子指针
};


// 二叉树定义
using Tree = Node*;


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
//        +       
//    -       *   
//  /   +   -   / 
// 2 3 4 5 6 7 8 9
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


// 使用后续遍历计算表达式树的值
double Calculate(Tree tree)
{
    if (tree == nullptr) {
        return 0;
    }
    string value = tree->value;  // 取根节点的值
    switch (value[0]) {
        case '+':
            return Calculate(tree->left_child) + Calculate(tree->right_child);
        case '-':
            return Calculate(tree->left_child) - Calculate(tree->right_child);
        case '*':
            return Calculate(tree->left_child) * Calculate(tree->right_child);
        case '/':
            return Calculate(tree->left_child) / Calculate(tree->right_child);
        default:
            return stof(value);
    }
}


// 根据中缀表达式建立表达式树
void BuildTree(vector<string> vec, Tree& tree)
{
    if (vec.empty()) {  // 如果表达式为空返回0
        tree = nullptr;
        return;
    }
    if (vec.size() == 1) {  // 如果表达式只有一个数，则返回这个数
        tree = new Node{vec[0], nullptr, nullptr};
        return;
    }

    // 若表达式以左括号开始且以右括号结束，并且开头的左括号与此右括号匹配，
    // 将表达式两端的括号去掉，并递归建树
    if (*vec.begin() == "(" && *vec.rbegin() == ")") {
        int unclosed_parentheses = 1;
        for (auto it = vec.begin() + 1; it != vec.end() - 1; ++it)
        {
            if (*it == "(") ++unclosed_parentheses;
            if (*it == ")") --unclosed_parentheses;
            if (unclosed_parentheses == 0) break;
        }
        if (unclosed_parentheses == 1) {
            BuildTree(vector<string>(vec.begin()+1, vec.end()-1), tree);
            return;
        }
    }

    // 寻找优先级最低的运算符
    auto pos = vec.end();  // 优先级最低的运算符的位置
    string lowerest_operator = "*";  // 假设优先级最低的运算符为*
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (*it == "(") {  // 跳过括号
            int count = 1;  // 进入的括号层数 
            while (count != 0) {
                ++it;
                if (*it == "(") ++count;
                if (*it == ")") --count;
            }
            continue;
        }
        if ((*it == "*" || *it == "/") && (lowerest_operator == "*" || lowerest_operator == "/")) {
            pos = it;
            lowerest_operator = *it;
        }
        if (*it == "+" || *it == "-") {
            pos = it;
            lowerest_operator = *it;
        }
    }
    
    // 以最低优先级的运算符为界，将表达式划分为两部分，递归建树
    tree = new Node{*pos, nullptr, nullptr};
    BuildTree(vector<string>(vec.begin(), pos), tree->left_child);
    BuildTree(vector<string>(pos+1, vec.end()), tree->right_child);
}


int main()
{
    cout << "将中缀表达式转换成表达式树，" << endl;
    cout << "然后使用后序遍历计算表达式的值。" << endl; 
    
    cout << "请输入中缀表达式，并以#结尾" << endl;
    string expression;  // 待处理的中缀表达式
    
    {  // 处理用户输入
        getline(cin, expression);
        if (*expression.rbegin() == '#') 
            expression.pop_back();  // 删除表达式末尾的“#”
    }
    
    vector<string> vec;  // 中缀表达式中运算数和运算符的队列
    Tree tree;  // 表达式树

    {  // 解析中缀表达式中的符号
        for (unsigned index = 0; index < expression.length(); ++index)
        {
            string token;
            if (isspace(expression[index])) continue;
            if (isdigit(expression[index])) {  // 处理运算数
                while (isdigit(expression[index])) {
                    token += expression[index];
                    ++index;        
                }
                vec.push_back(token);
                --index;
                continue;
            }
            else {  // 处理运算符
                token = expression[index];
                vec.push_back(token); 
                continue;
            }
        }
    }

    BuildTree(vec, tree);
    TreePrint(tree);
    cout << "表达式的计算结果为：" << Calculate(tree) << endl;
}

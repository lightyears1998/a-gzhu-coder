#include <cctype>
#include <iostream>
#include <string>
using namespace std;


// 结点
struct Node
{
    char elem;
    Node * next = nullptr;
};

// 单链表
// 链表中头节点保存数据结点的个数，数据结点从1开始编号。
typedef Node *LinkList;

// 栈
struct Stack
{
    Node * base, * top;  // 指向栈底与栈顶元素的指针
};


// 构造链表
void InitList(LinkList & list)
{
    list = new Node;
    list->elem = 0;
    list->next = nullptr;
}


// 析构链表
void DestroyList(LinkList & list)
{
    Node * cur = list, * next;
    while (cur) {
        next = cur->next;
        delete cur;
        cur = next;
    }
    list = nullptr;
}

// 在链表末尾插入值为val的结点
void ListAppend(LinkList & list, char val)
{
    Node * tail = list;
    while (tail->next) {
        tail = tail->next;
    }
    list->elem += 1;
    tail->next = new Node{val, nullptr};
}


// 构造栈
void InitStack(Stack & stk)
{
    stk.base = stk.top = nullptr;
}


// 判断栈是否为空
bool StackEmpty(Stack & stk)
{
    return stk.base == nullptr;
}


// 向栈中压入值为val的结点
Node* StackPush(Stack & stk, char val)
{
    Node * neo = new Node {val, nullptr};
    if (stk.top == nullptr) {
        stk.base = stk.top = neo;
    }
    else {
        stk.top->next = neo;
        stk.top = neo;
    }
}


// 取栈顶结点的值
char StackTop(Stack & stk)
{
    return stk.top->elem;
}


// 弹出栈顶元素
void StackPop(Stack & stk)
{
    if (stk.base == stk.top) {  // 正在弹出栈中最后一个结点
        delete stk.top;
        stk.base = stk.top = nullptr;  // 最后一个结点被弹出
    }
    else {
        Node * pre = stk.base, * tail = stk.base->next;
        while (tail->next != nullptr) {
            pre = pre->next, tail = tail->next;
        }  // 定位栈顶指针的前一位指针及栈顶指针
        delete tail; pre->next = nullptr;  // 弹出栈顶
        stk.top = pre;  // 设置新的栈顶指针
    }
}


// 析构栈
void DestroyStack(Stack & stk)
{
    while (!StackEmpty(stk))
        StackPop(stk);
}


// 测试用例
// 将一串字符压入栈后弹出，测试栈是否能正常工作
void test()
{
    Stack stk; InitStack(stk);
    char ch; while (cin >> ch)
    {
        StackPush(stk, ch);
    }
    while (!StackEmpty(stk)) {
        cout << StackTop(stk) << ' ';
        StackPop(stk);
    }
    cout << endl;
    DestroyStack(stk);
}


int main()
{
    LinkList list; InitList(list);  // 初始化用于存放值的单链表
    {
        cout << "请输入等待匹配的括号表达式：" << endl;
        cout << "（按Ctrl+Z[ENTER]结束输入）" << endl;
        char ch; while (cin.get(ch) && !cin.eof()) {
            if (!isspace(ch)) {  // 若当前输入的字符不是“ ”或“\n”等空格字符
                ListAppend(list, ch);  // 将字符输入链表中
            }
        }
    }

    Stack stack; InitStack(stack);  // 初始用于解决括号匹配问题的栈
    
    bool match = true;  // 假设括号能成功匹配
    Node * cur = list->next;  // 等待匹配的括号结点
    while (match && cur)
    {
        char ch = cur->elem;  // 等待匹配的括号字符
        if (ch == '(' || ch == '[' || ch == '{') {
            StackPush(stack, ch);  // 左括号入栈
        }
        else {  // 处理右括号
            if (StackEmpty(stack)) {  // 栈为空则匹配失败
                match = false; continue;
            }
            char top = StackTop(stack);
            if ((ch == ')' && top == '(') || (ch == ']' && top == '[') || (ch == '}' && top == '{') ) {
                StackPop(stack);  // 弹出栈顶结点
            } else {
                match = false;
            }
        }
        cur = cur->next;  // 前进到下一个结点
    }
    if (!StackEmpty(stack)) match = false;

    cout << (match ? "匹配成功" : "匹配失败") << endl;

    DestroyList(list), DestroyStack(stack);
}

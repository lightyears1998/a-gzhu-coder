#include <iostream>
using namespace std;

// 定义结点
struct Node {
    int elem;
    Node * next;
};


// 单链表
// 链表中头节点保存数据结点的个数，数据结点从1开始编号。
typedef Node *LinkList;


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


// 向链表中升序插入数据
void ListInsert(LinkList & list, int elem)
{
    Node * cur = list;
    while (cur->next) {
        if (elem <= cur->next->elem) break;
        cur = cur->next;
    }
    Node * neo = new Node;
    neo->elem = elem;
    neo->next = cur->next;
    cur->next = neo;
    list->elem += 1;
}


// 删除链表中序号为pos的结点
void ListRemoveAt(LinkList & list, int pos)
{
    if (pos < 0 || pos > list->elem) return;  // 边界检查
    
    Node * pre = list;
    while (--pos) pre = pre->next;  // 将pre指针定位到待删除结点的前一个结点
    
    Node * tbd = pre->next;  // 将tbd指针定位到待删除结点
    pre->next = tbd->next;
    delete tbd;
    
    list->elem -= 1;
}


// 删除链表中值为val的结点
void ListRemoveVal(LinkList & list, int val)
{
    Node * pre = list, * cur = list->next;
    while (cur) {
        Node * nxt = cur->next;
        if (cur->elem == val) {
            delete cur; list->elem -= 1;
            pre->next = nxt, cur = pre;
        }
        pre = cur, cur = nxt;
    }
}


// 反转链表
void ListReverse(LinkList & list)
{
    Node * pre = nullptr, * cur = list->next, * nxt = nullptr;
    while (cur) {
        nxt = cur->next;
        cur->next = pre;
        pre = cur, cur = nxt;
    }  // 离开循环时，pre指针指向反转前链表的末尾结点，即新链表的首元结点
    list->next = pre;
}


// 输出链表
void ListDump(LinkList & list)
{
    cout << "[" << list->elem << "] ";  // 输出头节点的存放的值，即链表中元素的个数
    
    Node * cur = list->next;
    while (cur) {
        cout << cur->elem;
        cout << (cur->next ? ' ' : '\n');
        cur = cur->next;
    } // 输出数据结点中存放的值
}


// 测试用例
void test()
{
    LinkList a; InitList(a);
    
    cout << "初始化链表：" << endl;
    ListInsert(a, 5), ListInsert(a, 4), ListInsert(a, 6);
    ListInsert(a, 3), ListInsert(a, 10), ListInsert(a, -2);
    ListDump(a);

    cout << "测试按序号删除结点功能，删除序号1、3、5的结点。" << endl;
    ListRemoveAt(a, 1), ListRemoveAt(a, 3), ListRemoveAt(a, 5);
    ListDump(a);

    cout << "测试按值删除结点功能，插入2个值为12的结点和1个值为6的结点，删除值为4或12的结点。" << endl;
    ListInsert(a, 12); ListInsert(a, 12); ListInsert(a, 6);
    ListDump(a);
    ListRemoveVal(a, 4); ListRemoveVal(a, 12);
    ListDump(a);

    cout << "测试翻转链表功能。" << endl;
    ListReverse(a);
    ListDump(a);
    ListReverse(a);
    ListDump(a);

    cout << "综合测试。" << endl;
    DestroyList(a), InitList(a);
    ListInsert(a, -8), ListInsert(a, 12), ListInsert(a, 6);
    ListReverse(a);
    ListDump(a);

    DestroyList(a);
}


int main()
{   
    cout << "单链表定义及基本操作验证性实验" << endl << endl;
    cout << "链表的数据类型定义为INT，第一个数据结点的下标为1。" << endl;
    cout << "请使用Ctrl+Z[ENTER]标志输入结束。" << endl << endl;

    LinkList list; InitList(list);
    cout << "请输入链表的初始值：" << endl;
    {
        int neo; while (cin >> neo) {
            ListInsert(list, neo);
            ListDump(list);
        }
        cin.clear();
    }

    cout << "请输入欲删除结点的序号：" << endl;
    {
        int pos; while (cin >> pos) {
            ListRemoveAt(list, pos);
            ListDump(list);
        }
        cin.clear();
    }
    
    cout << "请输入欲删除结点的值：" << endl;
    {
        int val; while (cin >> val) {
            ListRemoveVal(list, val);
            ListDump(list);
        }
        cin.clear();
    }

    cout << "翻转链表" << endl;
    ListReverse(list), ListDump(list);
    cout << "再次反转链表" << endl;
    ListReverse(list); ListDump(list);

    cout << "程序结束" << endl;
}

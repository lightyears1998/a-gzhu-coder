#include <iostream>
#include <string>
using namespace std;

// 结点
struct Node {
    int elem;
    Node * next;
};


// 循环链表
// 链表中头节点保存数据结点的个数，数据结点从1开始编号。
typedef Node *CycleLinkList;


// 构造链表
void InitList(CycleLinkList & list)
{
    list = new Node;
    list->elem = 0;
    list->next = list;
}


// 析构链表
void DestroyList(CycleLinkList & list)
{
    Node * cur = list->next, * next;
    while (cur != list) {
        next = cur->next;
        delete cur;
        cur = next;
    }  // 删除数据结点
    delete list, list = nullptr;  // 删除头节点
}


// 向链表中升序插入数据
void ListInsert(CycleLinkList & list, int elem)
{
    Node * cur = list;
    while (cur->next != list) {
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
void ListRemoveAt(CycleLinkList & list, int pos)
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
void ListRemoveVal(CycleLinkList & list, int val)
{
    Node * pre = list, * cur = list->next;
    while (cur != list) {
        Node * nxt = cur->next;
        if (cur->elem == val) {
            delete cur; list->elem -= 1;
            pre->next = nxt, cur = pre;
        }
        pre = cur, cur = nxt;
    }
}


// 反转链表
void ListReverse(CycleLinkList & list)
{
    Node * pre = list, * cur = list->next, * nxt = nullptr;
    while (cur != list) {
        nxt = cur->next;
        cur->next = pre;
        pre = cur, cur = nxt;
    }  // 离开循环时，pre指针指向反转前链表的末尾结点，即新链表的首元结点
    list->next = pre;
}


// 有序合并循环链表
CycleLinkList ListMerge(CycleLinkList list_a, CycleLinkList list_b)
{
    CycleLinkList list_c = new Node;  // 新链表的头节点

    list_c->elem = list_a->elem + list_b->elem;  // 合并链表后的结点个数为合并前两链表结点个数之和
    Node * cur_a = list_a->next, * cur_b = list_b->next;  // cur指向旧链表中表头结点的下一个结点
    Node * cur_c = list_c;  // 在后续循环中将在cur_c后插入新节点
    while (cur_a != list_a && cur_b != list_b)
    {
        Node *& less = cur_a->elem < cur_b->elem ? cur_a : cur_b;  // 选择两个结点中较小的一个
        Node * neo = new Node{less->elem, nullptr};  // 将较小结点的值复制到新节点中
        cur_c->next = neo, cur_c = neo;  // 将新节点插入新链表中
        less = less->next;
    }
    while (cur_a != list_a) {
        Node * neo = new Node{cur_a->elem, nullptr};
        cur_c->next = neo, cur_c = neo;
        cur_a = cur_a->next;
    }
    while (cur_b != list_b) {
        Node * neo = new Node{cur_b->elem, nullptr};
        cur_c->next = neo, cur_c = neo;
        cur_b = cur_b->next;
    }
    cur_c->next = list_c;
    return list_c;
}


// 输出链表
void ListDump(CycleLinkList & list)
{
    cout << "[" << list->elem << "] ";  // 输出头节点的存放的值，即链表中元素的个数
    
    Node * cur = list->next;
    while (cur != list) {
        cout << cur->elem;
        cout << (cur->next != list ? ' ' : '\n');
        cur = cur->next;
    }  // 输出数据结点中存放的值
}


// 向用户输出hint提示字符串，提示用户输入链表数据
void ListInput(CycleLinkList list, string hint)
{
    cout << hint << endl;
    int neo; while (cin >> neo) {
        ListInsert(list, neo);
    }
    ListDump(list);  // 在结束输入时输出链表的值
    cin.clear();
}


// 测试用例
void test()
{
    CycleLinkList a; InitList(a);
    
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
    cout << "循环链表定义及基本操作验证性实验" << endl << endl;
    cout << "链表的数据类型定义为INT，第一个数据结点的下标为1。" << endl;
    cout << "请使用Ctrl+Z[ENTER]标志输入结束。" << endl << endl;

    CycleLinkList list_a; InitList(list_a);
    CycleLinkList list_b; InitList(list_b);

    ListInput(list_a, "请输入链表A的值：");
    ListInput(list_b, "请输入链表B的值：");

    CycleLinkList list_c = ListMerge(list_a, list_b);
    cout << "将链表A、B合并为链表C：" << endl;
    ListDump(list_c);

    cout << "程序结束" << endl;
}

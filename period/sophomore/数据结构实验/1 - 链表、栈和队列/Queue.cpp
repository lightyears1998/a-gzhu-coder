#include <iostream>
using namespace std;


// 结点
struct Node
{
    char elem;
    Node * next;
};


// 链式循环队列
// 首元结点用于保存队列长度，队头结点是首元结点的后一个结点
// 末尾结点的下一个结点是首元结点
typedef Node *Queue;


// 构造队列
void InitQueue(Queue & que)
{
    que = new Node;
    que->elem = 0;
    que->next = que;  // 初始化为空队列
}


// 判断队列是否为空
bool QueueEmpty(Queue & que)
{
    return que->elem == 0;
}


// 获取队头结点的值
char QueueFront(Queue & que)
{
    return que->next->elem;
}


// 获取队列长度
int QueueLength(Queue & que)
{
    return que->elem;
}


// 向队尾添加值为val的结点
void QueuePush(Queue & que, char val)
{
    Node * rear = que;
    while (rear->next != que) {
        rear = rear->next;
    }
    rear->next = new Node{val, que};  // 向队尾添加结点
    que->elem += 1;
}


// 队头结点出队
void QueuePop(Queue & que)
{
    if (que->next != que) {  // 若队列不为空
        Node * head = que->next;
        que->next = head->next;
        delete head;
        que->elem -= 1;
    }
}


// 析构队列
void DestroyQueue(Queue & que)
{
    while (!QueueEmpty(que)) {
        QueuePop(que);
    }
    delete que; que = nullptr;
}


// 输出队列中的结点
void QueueDump(Queue & que)
{
    if (que->next == que) {
        cout << "队列为空" << endl;
        return;
    }

    cout << que << ' ' << que->next << endl;

    cout << que->next->elem;  // 输出队头结点的值
    for (Node * cur = que->next->next; cur != que; cur = cur->next) {
        cout << ' ' << cur->elem;  // 输出队头结点其后结点的值
    }
    cout << endl;
}


// 测试用例
void test()
{
    Queue que; InitQueue(que);
    QueueDump(que);

    QueuePush(que, '1'), QueuePush(que, '2'), QueuePush(que, '3'), QueuePush(que, '4'),
    QueuePush(que, '5'), QueuePush(que, '6'), QueuePush(que, '7'), QueuePush(que, '8');

    while (!QueueEmpty(que)) {
        QueuePop(que);
        QueueDump(que);
    }

    QueuePush(que, 'x');
    DestroyQueue(que);
}


int main()
{
    cout << "链式队列定义及基本操作实验" << endl;
    cout << "键盘缓冲区模拟：每读入10个字符向屏幕输出一行字符。" << endl;
    cout << "为了与用户输入区分，缓冲区的输出前附加有“>> ”记号。" << endl;
    cout << "按Ctrl+Z[ENTER]结束输入。" << endl;

    Queue que; InitQueue(que);  // 初始化用于模拟键盘缓冲区的链式队列
    char ch; while (cin.get(ch) && !cin.eof()) {
        QueuePush(que, ch);
        if (QueueLength(que) == 10) {  // 每读入10个字符输出一次
            cout << ">> ";
            while (!QueueEmpty(que)) {
                cout << QueueFront(que);
                QueuePop(que);
            }
            cout << endl;
        }
    }
    
    if (!QueueEmpty(que)) {  // 如果结束输入时队列中还有数据
        cout << ">> ";
        while (!QueueEmpty(que)) {
            cout << QueueFront(que);
            QueuePop(que);
        }  // 将队列中的数据输出
    }
}

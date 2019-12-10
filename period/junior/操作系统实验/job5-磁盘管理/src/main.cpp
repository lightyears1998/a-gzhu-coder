#include <cmath>
#include <ctime>
#include <climits>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;


int beginPos; // 磁头初始位置。
int numberOfSequence; // 磁盘请求个数。
vector<int> sequence; // 磁盘请求序列。


// 随机生成测试数据。
void init() {
    srand(time(nullptr));

    beginPos = rand() % 1000;
    numberOfSequence = rand() % 1000 + 1;
    for (int i = 0; i < numberOfSequence; ++i) {
        sequence.push_back(rand() % 1000);
    }

    cout << "磁头初始位置：" << beginPos << endl;
    cout << "磁盘请求个数：" << numberOfSequence << endl;
    cout << "磁盘访问序列：" << sequence[0];
    for (int i = 1; i < sequence.size(); ++i) {
        cout << ", " << sequence[i];
    }
    cout << endl;
}


// 打印磁头移动序列。
void printMoveSequence(const vector<int>& moveSequence) {
    // 计算磁头总的移动距离
    int totalMoveDistance = 0, headPos = beginPos;
    for (int nextMove : moveSequence) {
        totalMoveDistance += abs(nextMove - headPos);
        headPos = nextMove;
    }

    cout << "磁头移动轨迹：" << beginPos;
    for (int nextMove : moveSequence) {
        cout << " -> " << nextMove;
    }
    cout << endl << "磁头移动的总距离：" << totalMoveDistance << endl;
}


// 模拟先来先服务法。
void fcfs() {
    cout << "[先来先服务法]" << endl;

    // 磁头的移动序列就是请求序列。
    vector<int> moveSequence(::sequence);
    printMoveSequence(moveSequence);
}


// 模拟最短寻道时间法。
void sstf() {
    cout << "[最短寻道时间法]" << endl;

    // 将磁头初始位置加入请求序列中，并对请求序列进行排序。
    vector<int> sortedSequence(::sequence);
    sortedSequence.push_back(beginPos);
    sort(sortedSequence.begin(), sortedSequence.end());

    // 将排序后的请求序列压入队列。
    list<int> queue;
    for (int seq : sortedSequence) {
        queue.push_back(seq);
    }

    // 定位到与磁头起始位置。
    auto headPos = lower_bound(queue.begin(), queue.end(), beginPos);

    vector<int> moveSequence; // 磁头移动序列
    while (queue.size() > 1) {
        // 分别计算磁头向前向后移动到下一个被请求的磁道所需要的距离。
        int frontDistance = (next(headPos) != queue.end()) ? abs(*headPos - *(next(headPos))) : INT_MAX;
        int backDistance = (headPos != queue.begin()) ? abs(*headPos - *(prev(headPos))): INT_MAX;

        // 磁头往移动距离小的那个方向移动。
        list<int>::iterator nextHeadPos;
        if (frontDistance < backDistance) {
            nextHeadPos = next(headPos);
        } else {
            nextHeadPos = prev(headPos);
        }

        queue.erase(headPos);
        headPos = nextHeadPos;
        moveSequence.push_back(*nextHeadPos);
    }

    printMoveSequence(moveSequence);
}


// 电梯扫描法。
void scan() {
    cout << "[电梯扫描法]" << endl;

    // 将磁头初始位置加入请求序列中，并对请求序列进行排序。
    vector<int> sortedSequence(::sequence);
    sortedSequence.push_back(beginPos);
    sort(sortedSequence.begin(), sortedSequence.end());

    // 定位磁头初始位置。
    vector<int>::iterator headPos = lower_bound(sortedSequence.begin(), sortedSequence.end(), beginPos);

    vector<int> moveSequence; // 磁头的移动序列

    // 磁头先走磁道数增加方向。
    vector<int> front;
    copy(headPos + 1, sortedSequence.end(), back_inserter(front));
    copy(front.begin(), front.end(), back_inserter(moveSequence));

    // 磁头再走磁道数减少方向。
    vector<int> back;
    copy(sortedSequence.begin(), headPos, back_inserter(back));
    reverse(back.begin(), back.end());
    copy(back.begin(), back.end(), back_inserter(moveSequence));
    
    printMoveSequence(moveSequence);
}


// 随机生成磁盘请求序列，并依次运行FCFS、SSTF和SCAN算法。
int main() {
    init();
    fcfs();
    sstf();
    scan();
}

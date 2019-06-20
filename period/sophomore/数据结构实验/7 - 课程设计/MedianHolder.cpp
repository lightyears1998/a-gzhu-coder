#include "Heap.hpp"

#include <iostream>
#include <sstream>

using namespace std;


// 中位数寻找器
// 能在对数时间存入数据，并在常数时间内取出所存数据的中位数。
class MedianHodler {
private:
    Heap max_heap = GetMaximumHeap();
    Heap min_heap = GetMinimumHeap();
public:
    // 清空已保存的数字。
    void Clear() {
        max_heap.Clear();
        min_heap.Clear();
    }

    // 压入新的数字。
    void Push(double number) {
        if (max_heap.Size() == 0 || min_heap.Size() == 0) {
            max_heap.Push(number);
        } else {
            if (number > min_heap.Top()) {
                double top = min_heap.Top();
                min_heap.Pop();
                max_heap.Push(top);
                min_heap.Push(number);
            } else {
                max_heap.Push(number);
            }
        }

        // 确保左边的大顶堆元素数量始终不大于右边的小顶堆的元素数量加1，
        // 也就是左边的大顶堆最多比右边的小顶堆多一个元素。
        while (max_heap.Size() > min_heap.Size() + 1) {
            double top = max_heap.Top();
            max_heap.Pop();
            min_heap.Push(top);
        }
    }

    // 取中位数。
    double GetMedian() {
        assert(max_heap.Size() + min_heap.Size() >= 1);
        if ((max_heap.Size() + min_heap.Size()) % 2 == 0) {
            // 序列长度为偶数的情况下，取中间两位数字的算术平均数作为中位数。
            return double(max_heap.Top() + min_heap.Top()) / 2;
        }
        // 序列长度为奇数的情况下，取中间一位数字（大顶堆的堆顶）作为中位数。
        return max_heap.Top();
    }
};

int main()
{
    MedianHodler holder;
    
    cout << "请在一行之内输入待寻找中位数的整数序列，按Ctrl+Z结束输入。" << endl;
    string line;
    while (getline(cin, line)) {
        holder.Clear();

        stringstream ss(line);

        double input;
        while (ss >> input) {
            holder.Push(input);
        }
        cout << "中位数：" << holder.GetMedian() << endl;
    }
}

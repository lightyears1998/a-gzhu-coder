// HeapTest.cpp
// 最大堆和最小堆的实现的测试文件。

#include "Heap.hpp"

#include <iostream>
#include <vector>

using namespace std;


// 验证数列是非降序的。
void AssertAscend(const vector<double>& nums) {
    for (size_t i = 0; i + 1< nums.size(); ++i) {
        if (nums[i] <= nums[i+1]) continue;
        else cout << "Failed!";
    }
}


// 验证序列是非升序的。
void AssertDescend(const vector<double>& nums) {
    for (size_t i = 0; i + 1< nums.size(); ++i) {
        if (nums[i] >= nums[i+1]) continue;
        else cout << "Failed!";
    }
}


// 顺次取出堆顶并放入数组中。
vector<double> DumpHeap(Heap& heap) {
    vector<double> nums;
    while (heap.Size()) {
        nums.push_back(heap.Top());
        heap.Pop();
    }
    return nums;
}


// 测试堆的功能是否正常。
void HeapTest() {
    Heap max_heap = GetMaximumHeap();
    Heap min_heap = GetMinimumHeap();
    for (int i = 0; i < 1008611; ++i) {
        int random = rand();
        max_heap.Push(random);
        min_heap.Push(random);
    }
    AssertDescend(DumpHeap(max_heap));
    AssertAscend(DumpHeap(min_heap));
}


int main()
{
    HeapTest();
}

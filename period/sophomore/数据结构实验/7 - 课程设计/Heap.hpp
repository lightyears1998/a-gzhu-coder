// Heap.hpp
// 最大堆和最小堆的实现。

#include <functional>
#include <cassert>

// 用于生成大顶堆的比较函数。
const std::function<bool(double, double)> MAXIMUMHEAP_CMP = [](double lhs, double rhs) {
    return lhs > rhs;
};

// 用于生成小顶堆的比较函数。
const std::function<bool(double, double)> MINIMUMHEAP_CMP = [](double lhs, double rhs) {
    return lhs < rhs;
};

// 堆
// 自动维护堆的性质的数据结构。
class Heap {
private:
    double *heap;     // 指向保存堆中元素的数组
    int capacity;     // 保存堆中元素的数组的容量
    int size;         // 堆中元素的个数
    
    // 用于比较堆中元素大小的函数，重载此函数可以方便地生成大顶堆和小顶堆。
    std::function<bool(double , double)> compare;

private:
    // 交换索引位置idx1和idx2的元素值。
    void swapNodeAt(int idx1, int idx2) {
        double tmp = heap[idx1];
        heap[idx1] = heap[idx2];
        heap[idx2] = tmp;
    }

    // 返回idx处的结点是否为空。
    bool isEmpty(int idx) {
        return idx <= 0 || idx > size;
    } 

    // 返回idx处的结点是否为根节点。
    bool isRoot(int idx) {
        return idx == 1;
    }

    // 获取父亲结点的索引。
    int getParentIndex(int idx) {
        return idx / 2;
    }

    // 获取结点的左子结点的索引。
    int getLeftChildIndex(int idx) {
        return idx * 2;
    }

    // 获取结点的右子结点的索引。
    int getRightChildIndex(int idx) {
        return idx * 2 + 1;
    }

    // 使idx处的结点上浮。
    void shiftUp(int idx) {
        if (isRoot(idx)) {  // 如果当前结点已经是根节点，则不再上浮。
            return;
        }
        int parent_idx = getParentIndex(idx);
        if (compare(heap[idx], heap[parent_idx])) {  // 如果比较函数返回积极结果。
            swapNodeAt(idx, parent_idx);  // 将当前结点上浮到父亲结点。
            shiftUp(parent_idx);  // 递归上浮。
        }
    }

    // 使idx处的结点下沉。
    void shiftDown(int idx) {
        int left_child_idx = getLeftChildIndex(idx);
        int right_child_idx = getRightChildIndex(idx);
        if (isEmpty(left_child_idx)) {
            return;  // 左子树为空则不再下沉。
        }
        // 两个子树中更优先与idx结点比较的结点。在大顶堆中优先结点为左右结点中较大的一个。
        int prior_child_idx;
        if (isEmpty(right_child_idx)) {
            prior_child_idx = left_child_idx;  // 若右子节点为空，则当前结点只能与左子节点进行比较。
        } else {
            prior_child_idx = (compare(heap[left_child_idx], heap[right_child_idx]) ? 
                left_child_idx 
                : right_child_idx);  // 当前结点应该与左右结点中较大的一个进行比较。
        }
        if (!compare(heap[idx], heap[prior_child_idx])) {
            swapNodeAt(idx, prior_child_idx);  // 将idx结点下沉到prior_child_idx结点位置。
            shiftDown(prior_child_idx);  // 递归下沉。
        }
    }

    // 必要时将堆的容量扩大。
    void resize() {
        if (size + 8 > capacity) {
            int new_capacity = capacity * 2;
            double *new_heap = new double[new_capacity];
            memcpy(new_heap + 1, heap + 1, sizeof(double) * size);
            
            delete[] heap;
            heap = new_heap;
            capacity = new_capacity;
        }
    }


public:
    // 堆的构造函数
    // 需要传入一个比较函数，可以方便地根据比较函数的不同生成大顶堆或小顶堆。
    Heap(std::function<bool(double , double)> cmp) {
        capacity = 1024;
        heap = new double[capacity];
        size = 0;
        compare = cmp;
    }

    // 堆的复制构造函数
    Heap(const Heap& oth) {
        capacity = oth.capacity;
        heap = new double[capacity];
        size = oth.size;
        memcpy(heap + 1, oth.heap + 1, sizeof(double) * size);
        compare = oth.compare;
    }

    ~Heap() {
        delete[] heap;
    }

    // 向堆中插入值为val的结点。
    void Push(double val) {
        heap[++size] = val;  // 将新加入的结点放置在堆尾。
        shiftUp(size);       // 将新加入的结点上浮。
        resize();            // 必要时将堆的容量扩大。
    }

    // 返回堆中元素的个数。
    int Size() {
        return size;
    }

    // 清空堆。
    void Clear() {
        size = 0;
    }

    // 返回堆顶的元素。
    double Top() {
        assert(size >= 1);  // 求堆顶操作需要堆中至少存在一个元素。
        return heap[1];
    }

    // 将堆顶出堆。
    void Pop() {
        assert(size >= 1);  // 出堆操作要求堆中至少存在一个元素。
        swapNodeAt(1, size);
        --size;
        if (size > 0) shiftDown(1);  // 使新的堆顶下沉。
    }
};

// 返回一个大顶堆。
Heap GetMaximumHeap() {
    return Heap(MAXIMUMHEAP_CMP);
}

// 返回一个小顶堆。
Heap GetMinimumHeap() {
    return Heap(MINIMUMHEAP_CMP);
}

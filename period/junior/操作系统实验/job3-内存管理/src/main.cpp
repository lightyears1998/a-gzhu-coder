#include "program.hpp"
#include "manager.hpp"
#include "machine.hpp"
#include <ctime>
#include <iostream>

using namespace std;


int main() {
    srand(time(nullptr));

    Program p;
    cout << p.getPlainDescription();
    cout << p.getPageFlowDescription(10);

    // 使用平凡的页面置换算法运行程序。
    cout << endl;
    cout << "[平凡的页面置换算法Trivial]" << endl;
    DemandPagingMachine<TrivialManager> trivialMachine(12);
    trivialMachine.init();
    trivialMachine.load(p);
    trivialMachine.run();
    cout << trivialMachine.statistics() << endl;

    vector<unsigned> runMemorySizes;
    for (int i = 1; i <= 32; ++i) {
        runMemorySizes.push_back(i);
    }
    for (unsigned runMemorySize : runMemorySizes) {
        cout << endl;

        // 测试OPT算法。
        cout << "[最佳页面置换算法OPT] 运存大小：" << runMemorySize << endl;
        DemandPagingMachine<OPTManager> optMachine(runMemorySize);
        optMachine.init();
        optMachine.load(p);
        optMachine.run();
        cout << optMachine.statistics() << endl;

        // 测试FIFO算法。
        cout << "[先进先出算法FIFO] 运存大小：" << runMemorySize << endl;
        DemandPagingMachine<FIFOManager> fifoMachine(runMemorySize);
        fifoMachine.init();
        fifoMachine.load(p);
        fifoMachine.run();
        cout << fifoMachine.statistics() << endl;
        
        // 测试LRU算法。
        cout << "[最近最久未使用置换法LRU] 运存大小：" << runMemorySize << endl;
        DemandPagingMachine<LRUManager> lruMachine(runMemorySize);
        lruMachine.init();
        lruMachine.load(p);
        lruMachine.run();
        cout << lruMachine.statistics() << endl;
    }
}

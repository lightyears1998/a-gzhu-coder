// 银行家算法演示程序

#include "third-party/table_printer.h"

#include <cassert>
#include <ctime>
#include <vector>
#include <iostream>

using namespace std;
using TablePrinter = bprinter::TablePrinter;

const int NUMBER_OF_PROCESS = 5;  // 系统中进程的总量 P1, P2, P3, ..., Pn
const int TYPE_OF_RESOURCES = 3;  // 系统中资源的种类 R1, R2, R3, ..., Rn

const int RANDOM_RESOURCE_UPPER_BOUND = 20; // 随机生成的系统资源数量的上界
const int RANDOM_RESOURCE_LOWER_BOUND = 5;  // 随机生成的系统资源数量的下界


// 系统中各种资源的总量
// 
// eg. 系统中Ri资源的总量为TOTAL_RESOURCE[i-1]。
vector<int> TOTAL_RESOURCE(TYPE_OF_RESOURCES);


// 系统中进程对资源的最大需求量
// 
// eg. 系统中进程Pi对资源Rj的最大需求量为MAX_REQUEST[i-1][j-1]。
vector<vector<int>> MAX_REQUEST(NUMBER_OF_PROCESS);


// 随机生成系统资源数量以及进程对资源的最大需求量。
void init() {
    srand(time(nullptr));

    // 随机产生系统资源数量。
    for (int& res : TOTAL_RESOURCE) {
        res = rand() % (RANDOM_RESOURCE_UPPER_BOUND - RANDOM_RESOURCE_LOWER_BOUND + 1);
        res += RANDOM_RESOURCE_LOWER_BOUND;
    }

    // 随机产生进程对资源的最大需求量。
    for (vector<int>& request : MAX_REQUEST) {
        request = move(vector<int>(TYPE_OF_RESOURCES));  // 用一维数组保存进程对每种资源的需求量。
        for (int i = 0; i < TYPE_OF_RESOURCES; ++i) {
            request[i] = rand(); 
            request[i] %= TOTAL_RESOURCE[i] + 1; // 进程对Ri的最大需求量不得超过资源的总量。
        }
    }
}


// 打印系统中进程的数量。
void printNumberOfProcess() {
    cout << "系统中进程的数量：" << NUMBER_OF_PROCESS << endl;
}


// 打印系统中的资源总量。
void printTotalResoure() {
    cout << "系统中资源的种类：" << TYPE_OF_RESOURCES << endl;
    cout << "系统中资源的总量：" << endl;

    TablePrinter tp(&std::cout);
    for (int i = 1; i <= TYPE_OF_RESOURCES; ++i) {
        tp.AddColumn(string("R") + to_string(i), 4);
    }

    tp.PrintHeader();
    for (const int res : TOTAL_RESOURCE) {
        tp << res;
    }
    tp.PrintFooter();
}


// 打印进程对资源的最大需求量。
void printMaxRequest() {
    cout << "进程对资源的最大需求量：" << endl;

    TablePrinter tp(&std::cout);
    tp.AddColumn("Px", 4);
    for (int i = 1; i <= TYPE_OF_RESOURCES; ++i) {
        tp.AddColumn(string("R") + to_string(i), 4);
    }

    tp.PrintHeader();
    for (int i = 1; i <= NUMBER_OF_PROCESS; ++i) {
        tp << (string("P") + to_string(i));
        for (auto & resourceNumber : MAX_REQUEST[i-1]) {
            tp << resourceNumber;
        }
    }
    tp.PrintFooter();
}


// 当前系统中可供分配的资源
vector<int> availableResource(TYPE_OF_RESOURCES); 


// 当前系统中进程占用的资源
vector<vector<int>> accquiredResource(NUMBER_OF_PROCESS, vector<int>(TYPE_OF_RESOURCES));  


// isFinished[i]表示进程i+1是否运行完毕。
vector<bool> isFinished(NUMBER_OF_PROCESS);


// Request.first + 1 表示申请资源的进程编号
// Request.second 表示申请申请资源的数量
using Request = pair<int, vector<int>>;


// 随机挑选一个未完成的进程，并随机申请资源。
Request randomRequest() {
    int randProcess;
    do {
        randProcess = rand() % NUMBER_OF_PROCESS;
    } while (isFinished[randProcess]);  // 随机挑选一个未完成的进程

    vector<int> randResource(TYPE_OF_RESOURCES); // 进程对每类资源的需求数量。
    for (int i = 0; i < TYPE_OF_RESOURCES; ++i) { // 随机生成进程对每类资源的需求。
        // 进程申请的资源数量不得超过自己实际所需要的资源的数量。
        randResource[i] = rand() % (MAX_REQUEST[randProcess][i] - accquiredResource[randProcess][i] + 1);
    }
    
    bool allZero = true;  // 判断申请的每类资源是否均为0。
    for (int res : randResource) {
        if (res != 0) {
            allZero = false;
        }
    }

    return allZero ? randomRequest() : make_pair(randProcess, randResource);
}


// 打印申请资源的进程号以及申请资源的数量。
void printRequest(Request request) {
    cout << "进程" << to_string(request.first + 1) << "申请：";
    cout << "(" << request.second[0];
    for (int i = 1; i < request.second.size(); ++i) {
        cout << ", " << request.second[i];
    }
    cout << ")。" << endl;
}


// 获取系统的一个安全序列。
vector<int> getSafeSequence() {
    vector<int> safeSequence;

    // 将全局作用域中的变量复制到局部作用域中。
    vector<int> availableResource = ::availableResource;
    vector<vector<int>> accquiredResource = ::accquiredResource;
    vector<bool> isFinished = ::isFinished;

    // 遍历进程列表。
    for (int p = 0; p < NUMBER_OF_PROCESS; ++p) {
        if (!isFinished[p]) {
            bool meetRequirement = true;

            // 判断当前系统系统资源能否满足对应进程的需求。
            for (int i = 0; meetRequirement && i < TYPE_OF_RESOURCES; ++i) {
                if (availableResource[i] < MAX_REQUEST[p][i] - accquiredResource[p][i]) {
                    meetRequirement = false;    
                }
            }
            
            if (meetRequirement) { // 若系统能满足进程对资源的需求。
                safeSequence.push_back(p);
                isFinished[p] = true; // 置进程完成标志。
                for (int i = 0; i < TYPE_OF_RESOURCES; ++i) { // 回收进程占用的资源。
                    availableResource[i] += accquiredResource[p][i];
                }
                p = 0;  // 从进程列表头部重新开始搜索。
            }
        }
    }

    // 检查搜索完毕后是否所有进程都可以完成运行。
    bool allProcessIsFinished = true;
    for (auto finished : isFinished) {
        if (!finished) {
            allProcessIsFinished = false;
        }
    }

    return allProcessIsFinished ? safeSequence : vector<int>();
}


// 打印安全序列。
void printSafeSequence(vector<int> sequence) {
    if (sequence.empty()) {
        cout << "当前系统中没有安全序列。" << endl;
    } else {
        cout << "当前系统中的一个安全序列为：";
        for (auto id : sequence) {
            cout << " " << (id + 1);
        }
        cout << endl;
    }
}


// 判断系统内现有资源能否满足进程的申请。
bool meetRequirement(Request request) {
    bool ok = true;
    for (int i = 0; i < TYPE_OF_RESOURCES; ++i) {
        int resource = request.second[i];
        if (availableResource[i] - resource < 0) {
            ok = false;
        }
    }
    return ok;
}


// 尝试进行资源分配。
void tryAllocate(Request request) {
    int process = request.first;
    
    for (int i = 0; i < TYPE_OF_RESOURCES; ++i) {
        int resource = request.second[i];
        assert(accquiredResource[process][i] + resource <= MAX_REQUEST[process][i]);
    }

    for (int i = 0; i < TYPE_OF_RESOURCES; ++i) {
        int resource = request.second[i];
        availableResource[i] -= resource;
        accquiredResource[process][i] += resource;
    }
}


// 取消资源分配。
void undoAllocate(Request request) {
    cout << "拒绝进程" << to_string(request.first + 1) << "的资源申请以避免进入不安全状态。" << endl;

    // 回收tryAllocate中预分配的资源。
    for (int i = 0; i < TYPE_OF_RESOURCES; ++i) {
        int resource = request.second[i];
        availableResource[i] += resource;
        accquiredResource[request.first][i] -= resource;
    }
}


// 确认资源分配。
void commitAllocate(Request request) {
    cout << "允许进程" << to_string(request.first + 1) << "的资源申请。" << endl;

    // 如果进程已经取得了运行所需的所有资源，
    // 那么释放进程取得的所有资源，并标记进程为已完成状态。
    bool readyToRun = true;
    for (int i = 0; i < TYPE_OF_RESOURCES; ++i) {
        if (accquiredResource[request.first][i] < MAX_REQUEST[request.first][i]) {
            readyToRun = false;
        }
    }
    if (readyToRun) {
        for (int i = 0; i < TYPE_OF_RESOURCES; ++i) {
            availableResource[i] += accquiredResource[request.first][i];
            accquiredResource[request.first][i] = 0;
        }
        isFinished[request.first] = true;
        cout << "进程" << to_string(request.first + 1) << "取得全部运行所需的资源并运行完毕。" << endl;
        cout << "进程" << to_string(request.first + 1) << "释放了取得的资源。" << endl;
    }
}


// 判断是否所有进程都运行完毕。
bool allProcessIsFinised() {
    for (bool finished : isFinished) {
        if (!finished) return false;
    }
    return true;
}


// 打印系统中可供分配的资源、进程已经取得的资源、进程还需要的资源以及进程是否已经完成。
void printSysmtemStatus() {
    // 打印系统中可提供分配资源。
    cout << endl << "系统中可用分配的资源：(";
    cout << availableResource[0];
    for (int i = 1; i < availableResource.size(); ++i) {
        cout << ", " << availableResource[i];
    }
    cout << ")。" << endl;

    // 打印进程最大需求的资源、已经取得的资源和进程还需要的资源、以及进程的完成标志。
    TablePrinter tp(&std::cout);
    tp.AddColumn("Px", 4);
    tp.AddColumn("Max", 2 + 4 * TYPE_OF_RESOURCES);
    tp.AddColumn("Acquired", 2 + 4 * TYPE_OF_RESOURCES);
    tp.AddColumn("Need", 2 + 4 * TYPE_OF_RESOURCES);
    tp.AddColumn("Done?", 6);
    tp.PrintHeader();
    for (int p = 0; p < NUMBER_OF_PROCESS; ++p) {
        tp << (string("P") + to_string(p + 1));  // 进程名称
        
        string max, acquired, need;  // 进程最大需求的资源、已经取得的资源和还需要的资源
        for (int i = 0; i < TYPE_OF_RESOURCES; ++i) {
            if (!max.empty()) max += string(", ");
            max += to_string(MAX_REQUEST[p][i]);

            if (!isFinished[p]) {
                if (!acquired.empty()) acquired += string(", ");
                if (!need.empty()) need += string(", ");
                acquired += to_string(accquiredResource[p][i]);
                need += to_string(MAX_REQUEST[p][i] - accquiredResource[p][i]);
            }
        }

        string finishFlag = isFinished[p] ? "ok!" : "";  // 进程的完成标志
        tp << max << acquired << need << finishFlag;
    }
    tp.PrintFooter();

    // 打印安全序列。
    printSafeSequence(getSafeSequence());
}


// 运行银行家算法。
void runBankerAlgorithmSimulation() {
    availableResource = TOTAL_RESOURCE;
    printSysmtemStatus();

    while (!allProcessIsFinised()) { // 当系统中还有进程没有结束运行时运行算法。
        auto request = randomRequest();  // 模拟进程向操作系统提出资源分配请求。
        printRequest(request);

        if (meetRequirement(request)) {
            tryAllocate(request);  // 尝试满足进程的请求。
            auto safeSequence = getSafeSequence();  // 尝试获取一个安全序列。
            
            // 如果系统中存在一个安全序列，则满足进程的请求；
            // 如不存在安全序列，则否决进程的请求。
            if (!safeSequence.empty()) {
                commitAllocate(request);
                printSysmtemStatus();  // 打印修改后的系统状态。
            } else {
                undoAllocate(request);
            }
        } else {
            cout << "系统中可用资源暂不能满足进程的申请。" << endl;
        }
    }
    cout << "所有进程运行完毕。" << endl;
}


int main() {
    init(); // 随机生成系统资源数量和进程需求。

    // 打印系统初始状态。
    printNumberOfProcess();
    printTotalResoure();
    printMaxRequest();

    // 模拟运行银行家算法。
    cout << endl << ">>> 开始模拟 <<<" << endl;
    runBankerAlgorithmSimulation();
    cout << endl << ">>> 模拟完毕 <<<" << endl;
}

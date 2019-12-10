#ifndef MANAGER_HPP
#define MANAGER_HPP

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include "program.hpp"
#include "machine.hpp"
#include <vector>
#include <algorithm>


// 平凡的置换管理器
class TrivialManager : public PageReplacementManager {
public:
    TrivialManager(Memory& virtualMemory, Memory& runMemory, vector<unsigned>& pageTable)
        : PageReplacementManager(virtualMemory, runMemory, pageTable) {}

    void init(const Program&) override {};

    void loadPageOf(unsigned commandAddr) override {
        unsigned pageNumber = commandAddr / Page::pageSize;

        // 总是将新页装载在运存中第一个位置。
        this->runMemory[0].load(virtualMemory[pageNumber]);
        this->pageTable[0] = pageNumber;
    }
};


// 最佳置换法（最佳淘汰法、OPT）页面对换管理器 
class OPTManager : public PageReplacementManager {
    Program *program = nullptr;

public:
    OPTManager(Memory& virtualMemory, Memory& runMemory, vector<unsigned>& pageTable)
        : PageReplacementManager(virtualMemory, runMemory, pageTable) {}

    ~OPTManager() {
        delete program; program = nullptr;
    }

    void init(const Program& program) override {
        this->program = new Program(program);
    }

    void loadPageOf(unsigned commandAddr) override {
        unsigned newPageNumber = commandAddr / Page::pageSize;

        // 若运存中还有空位，则将新页放入空位中。
        for (int i = 0; i < pageTable.size(); ++i) {
            if (pageTable[i] == -1) {
                this->runMemory[i].load(virtualMemory[newPageNumber]);
                this->pageTable[i] = newPageNumber;
                return;
            }
        }

        // 否则，计算运存中的页在何时被下一次使用。
        vector<int> nextUsed(runMemory.getCapacity()); // 保存pageTable[i]经过多久会被再次访问；数值越大访问时间距离当前越远。
        vector<Command> commands = program->getCommands(); // 获取程序的所有指令。
        for (int i = 0; i < pageTable.size(); ++i) { // 获取运存中现有页面下次使用的时间。
            unsigned oldPageNumber = pageTable[i];
            unsigned distance = 0;
            for (unsigned addr = commandAddr; commands[addr].nextCommandAddr != addr; addr = commands[addr].nextCommandAddr) {
                if (addr / Page::pageSize != oldPageNumber) {
                    ++distance;
                } else {
                    break;
                }
            }
            nextUsed[i] = distance;
        }

#ifdef DEBUG
        cout << "Command Address: " << commandAddr << endl;
        for (int i = 0; i < pageTable.size(); ++i) {
            unsigned pageNubmer = pageTable[i];
            cout << pageNubmer << " [Next used: " << nextUsed[i] << "]" << endl;
        }
        cout << "-----------------" << endl;
#endif

        // 将最远使用或用不使用的页替换掉。
        unsigned oldPageIndex = max_element(nextUsed.begin(), nextUsed.end()) - nextUsed.begin(); // 获取最远使用的页面的索引。
        this->runMemory[oldPageIndex].load(virtualMemory[newPageNumber]);
        this->pageTable[oldPageIndex] = newPageNumber;
    }
};


// 先进先出法（FIFO）页面对换管理器
class FIFOManager : public PageReplacementManager {
    unsigned loadIndex; // 发生下一次替换时，运存中发生替换位置的索引。

public:
    FIFOManager(Memory& virtualMemory, Memory& runMemory, vector<unsigned>& pageTable)
        : PageReplacementManager(virtualMemory, runMemory, pageTable) {}

    void init(const Program&) override {
        loadIndex = 0;
    }

    void loadPageOf(unsigned commandAddr) override {
        unsigned newPageNumber = commandAddr / Page::pageSize;

        // 将新页装入运存中的LoadIndex位置。
        this->runMemory[loadIndex].load(virtualMemory[newPageNumber]);
        this->pageTable[loadIndex] = newPageNumber;
        loadIndex = (loadIndex + 1) % runMemory.getCapacity();
    }
};


// 最近最少使用法（LRU）页面对换管理器
class LRUManager : public PageReplacementManager {
    unsigned time; // 在notifiyPageUsed方法调用时自增1，用做lastUsed数组的值。
    vector<unsigned> lastUsed; // 保存页面上次使用时间，页面i上次使用的时间为lastUsed[i]。

public:
    LRUManager(Memory& virtualMemory, Memory& runMemory, vector<unsigned>& pageTable)
        : PageReplacementManager(virtualMemory, runMemory, pageTable) {}

    void init(const Program&) override {
        time = 0;
        lastUsed = vector<unsigned>(virtualMemory.getCapacity(), 0);
    }

    void loadPageOf(unsigned commandAddr) override {
        unsigned newPageNumber = commandAddr / Page::pageSize;

        // 若运存中还有空位，则将新页放入空位中。
        for (int i = 0; i < pageTable.size(); ++i) {
            if (pageTable[i] == -1) {
                this->runMemory[i].load(virtualMemory[newPageNumber]);
                this->pageTable[i] = newPageNumber;
                return;
            }
        }

        // 获取运存中的页面的上次使用时间。
        vector<unsigned> lastUsed(runMemory.getCapacity());
        for (int i = 0; i < runMemory.getCapacity(); ++i) {
            unsigned pageNumber = pageTable[i];
            lastUsed[i] = this->lastUsed[pageNumber];
        }

        // 替换掉上次使用时间最远的。（即替换掉time最小的页面）
        unsigned oldPageIndex = min_element(lastUsed.begin(), lastUsed.end()) - lastUsed.begin(); // 获取最远使用的页面的索引。
        this->runMemory[oldPageIndex].load(virtualMemory[newPageNumber]);
        this->pageTable[oldPageIndex] = newPageNumber;
    }

    void notifyPageUsed(unsigned pageNumber) override {
        ++time;
        lastUsed[pageNumber] = time;
    } 
};

#endif // MANAGER_HPP

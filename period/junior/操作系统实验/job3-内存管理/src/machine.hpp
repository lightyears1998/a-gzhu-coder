#ifndef MACHINE_HPP
#define MACHINE_HPP

#include "program.hpp"
#include "manager.hpp"
#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>


// 页面对换管理器的抽象基类
// 页面对换管理器负责在发生缺页时，从运行内存和虚拟内存对换所需的页。
class PageReplacementManager {
protected:
    Memory &virtualMemory;
    Memory &runMemory;
    vector<unsigned> &pageTable;

public:
    PageReplacementManager(Memory &virtualMemory, Memory &runMemory, vector<unsigned> &pageTable) 
        : virtualMemory(virtualMemory), runMemory(runMemory), pageTable(pageTable) {};

    // 初始化。
    virtual void init(const Program&) = 0;

    // 将包含commandAddr的页调入内存。
    virtual void loadPageOf(unsigned commandAddr) = 0;

    // 当Machine使用了pageNumber页面时调用此方法。
    // 此方法用于在Manager中记录历史页面使用情况。
    virtual void notifyPageUsed(unsigned pageNumber) {};
};


// 按需分页机器
// 机器包括虚拟内存VirutalMemory、运行内存runMemory和页面对换管理器manager。
template<typename PageReplacementManagerType = PageReplacementManager>
class DemandPagingMachine {
    Memory virutalMemory;
    Memory runMemeory;
    vector<unsigned> pageTable;
    unsigned programCounter;
    PageReplacementManagerType manager;

    unsigned hit, total;  // 命中次数，指令总数

#ifdef DEBUG
    vector<unsigned> pageFlow; // 页面流
#endif // DEBUG

public:
    DemandPagingMachine(unsigned runMemorySize) : 
        virutalMemory(Program::commandCount / 10 + (Program::commandCount % 10 != 0 ? 1 : 0)), 
        runMemeory(runMemorySize), pageTable(runMemorySize), 
        manager(virutalMemory, runMemeory, pageTable) {};

    // 初始化机器，清空内存中现有内容和统计数据。
    void init() {
        virutalMemory.clear();
        runMemeory.clear();
        for (unsigned &pageNumber : pageTable) {
            pageNumber = -1; // -1表示对应页为空。
        }
        programCounter = -1;
        hit = total = 0;

#ifdef DEBUG
        pageFlow.clear();
#endif // DEBUG
    }

    // 将程序p装入虚拟内存中，并等待运行。
    void load(const Program& p) {
        vector<Command> commands = p.getCommands();
        
        // 每十条指令为一页，装入虚拟内存中。
        assert(p.getCommands().size() > 0);
        for (unsigned i = 0; i < commands.size(); ) {
            Page page;
            for (unsigned addr = 0; addr < 10; ++i, ++addr) {
                page.load(addr, commands[i]);
            }
            virutalMemory.load((i-1) / 10, page);
        }

        // 将PC设置为程序的入口地址。
        programCounter = p.getEntryPoint();

        // 利用程序信息初始化页面置换管理器。
        manager.init(p);
    }

    // 运行程序。
    void run() {
        while (true) {
            // 获取PC所指向指令的页号。
            unsigned pageNumber = programCounter / 10;

#ifdef DEBUG
            pageFlow.push_back(pageNumber);
#endif // DEBUG

            // 判断该页是否在运行内存中。
            // 若页不在运行内存中，则要执行页面调度算法。
            // 最后获取对应页的索引。
            unsigned pageIndex;
            for (pageIndex = 0; pageIndex < pageTable.size(); ++pageIndex) {
                if (pageTable[pageIndex] == pageNumber) {
                    ++hit;
                    break;
                }
            }
            if (pageIndex >= pageTable.size()) {
                manager.loadPageOf(programCounter);
                for (pageIndex = 0; pageIndex < pageTable.size(); ++pageIndex) {
                    if (pageTable[pageIndex] == pageNumber) {
                        break;
                    }
                }
            }
            assert(pageIndex < pageTable.size());
            manager.notifyPageUsed(pageNumber);  // 通知manager，pageNumber页被使用了。

            // 获取指令。
            Command currentCommad = runMemeory[pageIndex][programCounter % 10];
            ++total;

            // 若该指令不是程序的最后一条指令，则设置PC为下一条指令地址；
            // 否则结束运行。
            if (programCounter == currentCommad.nextCommandAddr) {
                return;
            }
            programCounter = currentCommad.nextCommandAddr;
        }   
    }

    // 获取命中率等统计数据。
    string statistics() {
        stringstream ss;

#ifdef DEBUG 
        ss << "页面流：";
        for (unsigned pageNumber : pageFlow) {
            ss << " " << pageNumber;
        }
        ss << endl;
#endif // DEBUG

        ss <<  "指令总数：" << total
            << "，命中率：" <<  setprecision(4) << (double(hit) / total * 100) << "%"
            << "，缺页率：" <<  setprecision(4) << ((1 - (double(hit) / total)) * 100) << "%";
        return ss.str(); 
    }
};

#endif // MACHINE_HPP

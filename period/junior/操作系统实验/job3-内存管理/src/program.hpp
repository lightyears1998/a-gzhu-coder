#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


// 指令
// 每条指令包含当前指令的机器码code，以及下一条指令的逻辑地址nextCommandAddr。
class Command {
public:
    // 指令的机器码，有效范围[0, 7]。0表示空指令。
    unsigned code;
    unsigned nextCommandAddr;
};


// 程序
// 按《实验指导书》要求，一个程序包含320条指令。
// 程序的入口entryAddr。
// 程序中最后一条指令的nextAddr为自身的Addr。
class Program {
public:
    static const int commandCount = 320; // 程序中的指令总量
    
private:
    unsigned entryAddr; // 入口指令地址
    vector<Command> commands = vector<Command>(commandCount);

public:
    // 随机产生程序，随机生成的程序指令中不包含空指令。
    // 产生的程序满足约50%指令顺序执行，25%指令在前地址区，25%指令在后地址区。
    Program() {
        unsigned generatedCount = 0;
        unsigned currentAddr = rand() % commandCount;
        this->entryAddr = currentAddr;
        while (generatedCount < commandCount) {
            int nextAddr;
            switch (generatedCount % 3) {
                case 0: {
                    nextAddr = (currentAddr + 1) % commandCount;
                    while (commands[nextAddr].code != 0) {
                        nextAddr = (nextAddr + 1) % commandCount;
                    }
                    break;
                }
                case 1: {
                    nextAddr = (rand() % (currentAddr + 1) - 1 + commandCount) % commandCount;
                    while (commands[nextAddr].code != 0) {
                        nextAddr = (nextAddr - 1 + commandCount) % commandCount;
                    }
                    break;
                }
                case 2: {
                    nextAddr = (rand() % (commandCount - currentAddr) + 1 + currentAddr) % commandCount;
                    while (commands[nextAddr].code != 0) {
                        nextAddr = (nextAddr + 1) % commandCount;
                    }
                    break;
                }
            }

#ifdef DEBUG
            cout << "gen: " << generatedCount % 3 << " ";
            cout << "cur:" << currentAddr << " " << commands[currentAddr].code << " ";
            cout << "nxt:" << nextAddr << " " << commands[nextAddr].code << endl;
#endif // DEBUG

            commands[currentAddr] = Command { unsigned(rand() % 7 + 1), unsigned(nextAddr) };
            currentAddr = nextAddr;
            ++generatedCount;
        }
    }

    // 获取程序入口指令地址。
    unsigned getEntryPoint() const {
        return this->entryAddr;
    }

    // 获取程序的指令
    vector<Command> getCommands() const {
        return this->commands;
    }

    // 获取程序的哈希。
    size_t getHash() const {
        string commandSerial = "";
        for (const Command& command : commands) {
            commandSerial += to_string(command.code) + to_string(command.nextCommandAddr);
        }
        hash<string> hasher;
        return hasher(commandSerial);
    }

    // 获取程序的标识符。 
    string getIdentifier() const {
        stringstream ss;
        ss << "程序" << hex << this->getHash() << "";
        return ss.str();
    }

    // 获取程序的文本描述。
    string getPlainDescription() const {
        stringstream ss;
        ss << this->getIdentifier() << "：" << endl;

        ss << setfill('0');

        ss << setw(3) << "入口地址：" << this->getEntryPoint() << endl;
        ss << "地址：指令码（下一条指令的逻辑地址）" << endl;
        for (int i = 0; i < commands.size(); ++i) {    
            ss << setw(3) << i << ": ";
            ss << commands[i].code << "(" << setw(3) << dec << commands[i].nextCommandAddr << ")";
            (i + 1) % 10 == 0 ? ss << endl : ss << " ";
        }
        return ss.str();
    }

    // 获取程序按每页大小pageSize计算的的页面流。
    vector<unsigned> getPageFlow(unsigned pageSize) const {
        vector<unsigned> pageFlow;
        unsigned currentAddr = this->getEntryPoint();
        while (true) {
            pageFlow.push_back(currentAddr / pageSize);
            if (this->commands[currentAddr].nextCommandAddr == currentAddr) {
                break;
            }
            currentAddr = this->commands[currentAddr].nextCommandAddr;
        }
        return pageFlow;
    }

    // 获取程序按每页大小pageSize计算的的页面流。
    string getPageFlowDescription(unsigned pageSize) const {
        stringstream ss;
        ss << "页面流：";
        for (unsigned pageNumber : this->getPageFlow(pageSize)) {
            ss << " " << pageNumber;
        }
        ss << endl;
        return ss.str();
    }
};


// 页
// 按《实验指导书》要求，一个页可装入10条指令。
class Page {
public:
    static const int pageSize = 10;

private:
    vector<Command> content;

public:
    Page() {
        content.resize(pageSize);
    }

    // 获取页中的指令。
    Command operator[] (unsigned index) {
        return this->content[index];
    }

    // 将指令装入页中。
    void load(unsigned addr, Command command) {
        content[addr] = command;
    }

    // 将指令装入页中。
    void load(const Page& page) {
        content = page.content;
    }
};


// 内存
// 可装入一定数量的页。
class Memory {
    vector<Page> content;
    unsigned capacity;

public:
    // 使用可装入的页面的数量初始化内存。
    Memory(unsigned capacity) {
        this->capacity = capacity;
        content.resize(this->capacity);
    }

    // 获取内存的容量。
    unsigned getCapacity() {
        return this->capacity;
    }

    // 获取内存中的页。
    Page& operator [](unsigned index) {
        return this->content[index];
    }

    // 将页装入内存。
    void load(unsigned pageIndex, const Page& page) {
        content[pageIndex] = page;
    }

    // 清空内存中内容。
    void clear() {
        content.clear();
        content.resize(this->capacity);
    }
};

#endif // PROGRAM_HPP

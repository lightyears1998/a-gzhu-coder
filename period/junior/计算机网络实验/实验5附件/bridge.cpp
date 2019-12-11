/**
 * 模拟网桥程序 bridge.cpp
 * 
 * 模拟网桥有两个端口A、B。
 * 端口A连接了主机1、主机2；端口2连接了主机3、主机4。
 * 主机的MAC地址随机生成。
 * 发送的数据保存在bridge-test1.bin和bridge-test2.bin中，也是随机生成的。
 */
#include "third-party/table_printer.h"
#include <ctime>
#include <cassert>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;
using bprinter::TablePrinter;


// 模拟MAC地址。
class MacAddress {
public:
    string address; // 6字节MAC地址，使用长度为12的十六进制数字表示。

    MacAddress(string address = string("000000000000")) {
        assert(address.length() == 12);
        this->address = address;
    }

    bool operator == (const MacAddress& oth) const {
        return this->address == oth.address;
    }

    bool operator <(const MacAddress& oth) const {
        return this->address < oth.address;
    }

    // 随机产生6字节的MAC地址。
    MacAddress static getRandomAddress() {
        stringstream ss;
        for (int i = 0; i < 6; ++i) {
            ss << hex << setw(2) << setfill('0') << int(uint8_t(rand())); 
        }
        return MacAddress(ss.str());
    }

    friend ostream& operator<<(ostream& out, const MacAddress &mac) {
        out << mac.address;
        return out;
    }
};


// 模拟帧
// 这里省略了帧的数据部分，因为程序意在模拟网桥。
class Frame {
public:
    MacAddress dstMac; // 目的MAC地址
    MacAddress srcMac; // 源MAC地址

    // 初始化一个空的帧。
    Frame() {
        this->dstMac = MacAddress();
        this->srcMac = MacAddress();
    }

    // 初始化一个带有源主机地址和目的主机地址的帧。
    Frame(MacAddress dstMac, MacAddress srcMac) {
        this->dstMac = dstMac;
        this->srcMac = srcMac;
    }

    // 判断帧是否为空。
    bool isEmpty() {
        Frame emptyFrame;
        return *this == emptyFrame;
    }

    bool operator == (const Frame& oth) {
        return this->dstMac == oth.dstMac && this->srcMac == oth.srcMac;
    }

    friend ostream& operator << (ostream& out, const Frame& frame) {
        out << frame.dstMac.address << " " << frame.srcMac.address << endl;
        return out;
    }

    friend istream& operator >> (istream& in, Frame& frame) {
        in >> frame.dstMac.address;
        in >> frame.srcMac.address;
        return in;
    }
};


// 模拟网桥
class Bridge {
    // 网桥的端口
    enum Port {A, B};

    // 转发表
    map<MacAddress, Port> transferTable;

public:
    // 显示转发表
    void showTransferTable() {
        TablePrinter tp(&cout);
        
        tp.AddColumn("Mac Address", 16);
        tp.AddColumn("Port", 6);

        cout << "转发表：" << endl;
        tp.PrintHeader();

        for (auto it = transferTable.begin(); it != transferTable.end(); ++it) {
            tp << it->first << (it->second == Port::A ? "A" : "B");
        }
        tp.PrintFooter();
    }

    // 广播帧。
    void broadcast(Frame frame) {
        cout << "在所有端口上广播此帧。" << endl;
    }

    // 在某端口发送帧。
    void transfer(Frame frame, Port port) {
        cout << "在" << (port == Port::A ? "A" : "B") << "上发送此帧。" << endl;
    }

    // 不进行转发。
    void drop(Frame frame) {
        cout << "不进行转发，因为源主机与目的主机在网桥同一端口上。" << endl;
    }

    // 启动网桥，开始转发数据。
    void start() {
        cout << "模拟网桥开始运行。" << endl;

        ifstream aIn("bridge-test1.bin");
        ifstream bIn("bridge-test2.bin");

        // 读取数据，直到所有数据读取完毕。
        for (int count = 0; aIn && bIn; ++count) {
            // 交替从A和B两个文件中读取数据。
            Port port = (count & 1 ? Port::A : Port::B); // 当前接收帧的端口
            ifstream& in = (count & 1 ? aIn : bIn);

            // 从端口中读取数据。
            if (in) {
                // 读取一帧并跳过空帧。
                Frame frame; in >> frame;
                if (frame.isEmpty()) {
                    continue;
                }

                cout << "从" << (port == Port::A ? "A" : "B") << "端口收到来自" 
                    << frame.srcMac << "发往" << frame.dstMac << "的帧。" 
                    << endl;

                // 自学习源主机的端口。
                transferTable[frame.srcMac] = port;
            
                // 检查Mac地址。
                if (transferTable.find(frame.dstMac) != transferTable.end()) {
                    if (transferTable[frame.dstMac] == transferTable[frame.srcMac]) {
                        // 若源主机与目的主机所在端口相同，则丢弃该帧不进行转发。
                        drop(frame);
                    } else {
                        // 若源主机与目的主机所在端口不同，则向目的主机所在端口转发该帧。
                        transfer(frame, transferTable[frame.dstMac]);
                    }
                } else {
                    // 若转发表中没有目的主机的信息，则广播该帧。
                    broadcast(frame);
                }
                
                // 打印修改后的转发表。
                showTransferTable();
            }
        }

        cout << "模拟网桥运行完毕。" << endl;
    }
};


// 生成测试数据。
void generateTestData() {
    // 生成四台主机的MAC地址。
    MacAddress hosts[4];
    for (int i = 0; i < 4; ++i) {
        hosts[i] = MacAddress::getRandomAddress();
    }

    ofstream aOut("bridge-test1.bin");
    ofstream bOut("bridge-test2.bin");

    // 随机生成40个帧，分别写入bridge-test1.bin和bridge-test2.bin中。
    for (int i = 0; i < 40; ++i) {
        MacAddress srcMac, dstMac;
        if (i & 1) {
            do {
                srcMac = hosts[rand() % 2];
                dstMac = hosts[rand() % 4];
            } while (srcMac == dstMac);
            
            Frame frame(dstMac, srcMac);
            aOut << frame;
        } else {
            do {
                srcMac = hosts[rand() % 2 + 2]; 
                dstMac = hosts[rand() % 4];
            } while (srcMac == dstMac);
            
            Frame frame(dstMac, srcMac);
            bOut << frame;
        }
    }

    aOut.close();
    bOut.close();
}


int main() {
    // 输出程序概要。
    cout << "模拟网桥有两个端口A、B。" << endl;
    cout << "端口A连接了主机1、主机2；端口2连接了主机3、主机4。" << endl;
    cout << "主机的MAC地址随机生成。" << endl;
    cout << "发送的数据保存在bridge-test1.bin和bridge-test2.bin中，也是随机生成的。" << endl;
    cout << endl;

    generateTestData(); // 随机生成一些测试数据。

    Bridge().start(); // 启动网桥。
}

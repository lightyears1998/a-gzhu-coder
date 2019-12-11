/**
 * 校验和计算程序 checksum.cpp
 * 
 * 参考文献：Computing the Internet Checksum https://tools.ietf.org/html/rfc1071
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


int main(int argc, const char* argv[]) {
    // 检查参数。
    if (argc < 2) {
        cout << "参数不足，需要给出一个文件名。" << endl;
        return 1;
    } else if (argc > 2) {
        cout << "给出参数过多，只需要给出一个文件名即可。" << endl;
        return 1;
    }

    string filename(argv[1]); // 取得文件名。
    ifstream fin(filename, ios::binary); // 以二进制模式打开文件。

    // 检查文件是否可以打开。
    if (!fin.is_open()) {
        cout << "文件无法打开，请检查文件名是否正确。" << endl; 
        return 1;
    }
    
    uint32_t checksum = 0; // 待计算的校验和。

    // 从文件中读取数据，一次读入两个字节。
    uint8_t buffer[2]; // 若使用char类型，必须使用u_char，否则类型转换时按补码规则补1导致计算。
    for (int count = 0; count = fin.readsome((char *)buffer, 2); ) {
        uint16_t in = 0;

        // 若数据长度为奇数，则在数据末尾补充一个字节的0以凑成偶数。
        if (count == 1) {
            in = buffer[0];
            in <<= 8;
        } else {
            in = (uint16_t(buffer[0]) << 8) + buffer[1];
        }

        // 计算校验和。注意处理进位。
        checksum += in;
        while (checksum >= (1<<16)) {
            uint32_t carry = checksum >> 16;    
            checksum = checksum % (1<<16) + carry;
        }
    }

    // 输出16位校验和
    cout << hex << setw(4) << setfill('0') << checksum << endl;
}

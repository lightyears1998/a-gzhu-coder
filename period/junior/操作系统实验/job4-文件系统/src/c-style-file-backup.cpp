// 使用C风格的文件操作进行备份。
// fopen(), fread(), fwrite(), fclose().

#include "shared.hpp"
#include <cstdio>
#include <cstdlib>


void backupFile(string source, string destination) {
    // 打开源文件。
    FILE* fin = fopen(source.c_str(), "rb");
    if (fin == nullptr) {
        printf("源文件不存在，程序终止。\n");
        exit(1);
    }
    
    // 检查目标文件是否存在。
    FILE* fout = fopen(destination.c_str(), "rb");
    if (fout != nullptr) {
        printf("目标文件已存在，不能进行文件备份，程序终止。\n");
        fclose(fout);
        exit(1);
    }

    // 打开目标文件。
    fout = fopen(destination.c_str(), "wb");
    if (fout == nullptr) {
        printf("无法创建目标文件，可能是目标路径不存在或权限不足，程序终止。\n");
        exit(1);
    }

    // 建立缓冲区。
    const int bufferSize = 128;
    char buffer[bufferSize];

    // 复制数据。
    int readCount;
    while ((readCount = fread(buffer, sizeof(char), bufferSize, fin)) > 0) {
        fwrite(buffer, sizeof(char), readCount / sizeof(char), fout);
    }

    // 关闭文件。
    fclose(fin);
    fclose(fout);
}

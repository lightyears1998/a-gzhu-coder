// 利用POSIX风格的文件操作进行备份。
// open(), read(), write(), close().

#include "shared.hpp"
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


void backupFile(string source, string destination) {
    // 打开源文件。
    int fdSrc = open(source.c_str(), O_RDONLY);
    if (fdSrc < 0) {
        printf("源文件不存在，程序终止。\n");
        exit(1);
    }
    
    // 检查目标文件是否存在。
    int fdDst = open(destination.c_str(), O_RDONLY);
    if (fdDst > 0) {
        printf("目标文件已存在，不能进行文件备份，程序终止。\n");
        close(fdDst);
        exit(1);
    }

    // 打开目标文件。
    fdDst = open(destination.c_str(), O_WRONLY | O_CREAT);
    if (fdDst < 0) {
        printf("无法创建目标文件，可能是目标路径不存在或权限不足，程序终止。\n");
        exit(1);
    }

    // 建立缓冲区。
    char buffer[128];

    // 复制数据。
    int readCount;
    while ((readCount = read(fdSrc, buffer, sizeof(buffer))) > 0) {
        write(fdDst, buffer, readCount);
    }

    // 关闭文件。
    close(fdSrc);
    close(fdDst);
}

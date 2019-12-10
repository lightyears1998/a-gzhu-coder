#!/bin/bash
# 生成可执行文件。

# C-Style
g++ ./src/c-style-file-backup.cpp -o ./bin/c-style-file-backup.exe

# POSIX-Stye
g++ ./src/posix-style-file-backup.cpp -o ./bin/posix-style-file-backup.exe

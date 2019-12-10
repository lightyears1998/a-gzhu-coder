#!/bin/bash
# 测试运行结果。

./bin/c-style-file-backup.exe ./test/src.png ./test/c-backup.png
./bin/posix-style-file-backup.exe ./test/src.png ./test/posix-backup.png

sha1sum ./test/*

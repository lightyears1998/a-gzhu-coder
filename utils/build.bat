@echo off
goto start
====== 注释开始啦 ======
# 批量编译批处理

将此脚本放入源文件的文件夹中，运行，即可自动编译目录下的所有源文件
====== 注释结束啦 ======
:start

set COMPLIER="gcc.exe"
rem TODO 支持CL编译器
set OUTPUT_FOLDER="bin"
set EXTRA_ARGS="-Wall"

for %%i in (*.c) do (
echo 编译 %%i
%COMPLIER% %%i -o %OUTPUT_FOLDER%\%%i.exe %EXTRA_ARGS%
)

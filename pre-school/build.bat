@echo off
goto start
====== 注释开始啦 ======
批量编译批处理
====== 注释结束啦 ======
:start

set COMPLIER="gcc.exe"
set OUTPUT_FOLDER="bin"
set EXTRA_ARGS="-Wall"

for %%i in (*.c) do (
echo 编译 %%i
%COMPLIER% %%i -o %OUTPUT_FOLDER%\%%i.exe %EXTRA_ARGS%
)

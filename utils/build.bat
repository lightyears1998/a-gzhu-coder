@echo off
goto START
====== 注释开始啦 ======
# 批量编译批处理

配置你的编译器选项，
将批处理文件放入源代码文件夹中，
运行它，源代码将被编译。

[使用文档](/howto/make-use-of-build-batchfile.md)
====== 注释结束啦 ======
:START

% 调整代码页为UTF-8 %
chcp 65001

:SETTINGS_BEGIN
% 设置使用的编译器 %
set COMPLIER=""
rem 支持的编译器有"gcc", "cl"

% 设置GCC %
set GCC_PATH=C:\MinGW\bin
set GCC_EXTRA_ARGS="-Wall"

% 设置CL %
set CL_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.11.25503\bin\HostX86\x86
set CL_INCLUDE=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.11.25503\include;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.11.25503\atlmfc\include;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\VS\include;C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\ucrt;C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\um;C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\shared;C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\winrt;
set CL_LIB=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.11.25503\lib\x86;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.11.25503\atlmfc\lib\x86;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\VS\lib\x86;C:\Program Files (x86)\Windows Kits\10\lib\10.0.14393.0\ucrt\x86;C:\Program Files (x86)\Windows Kits\10\lib\10.0.14393.0\um\x86;
set CL_EXTRA_ARGS=""

% 设置输出文件夹位置 %
set OUTPUT_FOLDER="bin"
:SETTINGS_END

if %COMPLIER%=="" (
    echo 未设置编译器
    goto :ABORTING
)

if %COMPLIER%=="gcc" (
    goto GCC_SECTION
)

if %COMPLIER%=="cl" (
    goto CL_SECTION
)

:GCC_SECTION
set PATH=%GCC_PATH%;%PATH%
for %%i in (*.c) do (
    echo 编译 %%i
    gcc.exe %%i -o %OUTPUT_FOLDER%\%%i.exe %EXTRA_ARGS%
)
for %%i in (*.cpp) do (
    echo 编译 %%i
    g++.exe %%i -o %OUTPUT_FOLDER%\%%i.exe %EXTRA_ARGS%
)
echo.
echo 编译完成
echo.
goto :FINISHING

:CL_SECTION
:CL_ENV_INIT
set PATH=%CL_PATH%;%PATH%
set INCLUDE=%CL_INCLUDE%;%INCLUDE%
set LIB=%CL_LIB%;%LIB%

if exist %OUTPUT_FOLDER% (
    goto CL_COMPLIE
) else (
    mkdir %OUTPUT_FOLDER%
)

:CL_COMPLIE
for %%i in (*.c) do (
    echo 编译 %%i
    echo ================================================================
    cl.exe /Fe%OUTPUT_FOLDER%\%%i.exe %%i %CL_EXTRA_ARGS%
    echo ================================================================
    echo.
)
echo 编译完成
echo.

:CL_CLEAN
for %%i in (*.obj) do (
    del %%i 
)
echo 清理完成
echo.
goto :FINISHING

:ABORTING
set DOCUMENT=https://github.com/lightyears1998/gzhu-coder/blob/master/howto/make-use-of-build-batchfile.md
echo.
echo 批处理脚本意外中止，
echo 你可能需要调整脚本的参数。
echo.
echo 请参考使用指南： %DOCUMENT%
echo.
pause
goto :EOF

:FINISHING
pause
goto :EOF

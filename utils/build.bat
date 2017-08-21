@echo off
goto START
====== 注释开始啦 ======
# 批量编译批处理

在 SETTINGS 标签中配置你的编译器选项，
然后将批处理文件放入源代码文件夹中，
运行它，源代码将自动编译。
====== 注释结束啦 ======
:START

% 如有必要，调整代码页为UTF-8 %
chcp 65001

:SETTINGS_BEGIN
% 设置使用的编译器 %
set COMPLIER="cl"
rem set COMPLIER="gcc"

% 设置GCC %
set GCC_PATH=C:\MinGW\bin;
set GCC_EXTRA_ARGS="-Wall"

% 设置CL %
set CL_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.11.25503\bin\HostX64\x64;
set CL_INCLUDE=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.11.25503\include;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.11.25503\atlmfc\include;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\VS\include;C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\ucrt;C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\um;C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\shared;C:\Program Files (x86)\Windows Kits\10\Include\10.0.14393.0\winrt;
set CL_LIB=
set CL_EXTRA_ARGS=""

% 设置输出文件夹位置 %
set OUTPUT_FOLDER="bin"

:SETTINGS_END

if %COMPLIER%=="" (
    echo 请在使用前设置编译器
    goto :EOF
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
    echo %COMPLIER% %%i -o %OUTPUT_FOLDER%\%%i.exe %EXTRA_ARGS%
)
goto :EOF

:CL_SECTION
set PATH=%CL_PATH%;%PATH%
set INCLUDE=%CL_INCLUDE%;%INCLUDE%
echo %PATH%
for %%i in (*.c) do (
    echo 编译 %%i
    echo cl.exe %%i /Fe%OUTPUT_FOLDER%\%%i.exe %EXTRA_ARGS%
)
goto :EOF
